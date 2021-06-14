// Copyright © 2021 Giorgio Audrito. All Rights Reserved.

/**
 * @file server_discovery.hpp
 * @brief Implementation of the case study on drones recognition.
 */

#ifndef FCPP_SERVICE_DISCOVERY_H_
#define FCPP_SERVICE_DISCOVERY_H_

#include "lib/fcpp.hpp"
#include "lib/logic_samples.hpp"


/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {

//! @brief Number of edge, fog, cloud, and all nodes
//! @{
constexpr size_t edge_num = 50;
constexpr size_t fog_num = 20;
constexpr size_t cloud_num = 5;
constexpr size_t node_num = edge_num + fog_num + cloud_num;
//! @}

//! @brief Number of time instants before waiting response T/O
constexpr size_t resp_timeout = 5;

//! @brief Probability of issuing a request while computing.
constexpr real_t random_req = 0.2;

//! @brief Probability of sending a spurious second-in-a-row request
constexpr real_t random_err_req = 0.004;

//! @brief Probability of receiving a response not matching the previous request
constexpr real_t random_err_resp = 0.004;

//! @brief Probability of receiving a response while waiting (by req type)
constexpr real_t random_resp[] = {0.3, 0.45, 0.6, 0.75};

//! @brief Number of request types.
constexpr size_t ntypes_req = 4;

// //! @brief Dummy ordering between positions.
// bool operator<(vec<3> const&, vec<3> const&) {
//     return false;
// }

//! @brief Namespace containing the libraries of coordination routines.
namespace coordination {

namespace tags {
    //! @brief Parametric tag for formula failure.
    template <typename T>
    struct fail {};
    //! @brief Response time monitor formula for message type i.
    template <int i>
    struct response_time_monitor {};
    //! @brief Unwanted response monitor formula.
    struct unwanted_response_monitor {};
    //! @brief No double requests monitor formula.
    struct no_doublereq_monitor {};
    //! @brief Color representing the status a node (compute, wait response).
    struct status_c {};
    //! @brief Color representing the request type of a node (1-4).
    struct reqtype_c {};
    //! @brief Size of the current node (strong monitor true < globally false < locally false).
    struct size {};
}

//! @brief Status of devices.
enum class status {
    COMPUTE,   // computing
    WAITRESP   // waiting for a response
};

//! @brief Colors to represent status.
packed_color status_colors[] = {YELLOW, RED};
packed_color req_type_colors[] = {LIGHT_GREEN,FOREST_GREEN,GREEN,DARK_GREEN};

//! @brief Helper function to access storage.
template <template<int> class T, typename node_t>
bool& storage(node_t& node, size_t i) {
    using namespace tags;
    switch (i) {
    case 1:
        return node.storage(fail<T<1>>{});
    case 2:
        return node.storage(fail<T<2>>{});
    case 3:
        return node.storage(fail<T<3>>{});
    default:
        assert(i == 4);
        return node.storage(fail<T<4>>{});
    }
}

//! @brief Service discovery case study.
MAIN() {
    using namespace tags;
    using namespace component::tags;

    bool req=false, resp=false;

    size_t nsize=0;

    times_t start_time = 0;
    times_t exit_time = 0;

    bool edge = node.uid < edge_num;
    bool fog = node.uid >= edge_num and node.uid < edge_num + fog_num;
    bool cloud = node.uid >= edge_num + fog_num;

    nsize = 20;
    if (edge) nsize = 0;
    if (fog) nsize = 10;
    node.storage(size{}) = nsize;

    if (edge) {
        // if edge set random time to start (between 0 and 20)
        start_time = constant(CALL, node.next_real(0, 20));
        if (counter(CALL) == 1) {
            node.next_time(start_time);
            return;
        } else node.storage(size{}) = 5;

        // if edge, set random time to exit (between 20 and 200)
        exit_time = constant(CALL, node.next_real(100, 200));
        if (node.current_time() > exit_time) {
            node.storage(size{}) = 0;
            node.next_time(1000000);
            return;
        }
    }

    node.connector_data() = common::make_tagged_tuple<network_rank, power_ratio>(cloud ? 0 : fog ? 1 : 2, edge ? 0.8 : 1);

    status stat = status::COMPUTE;
    size_t req_type = 0;
    size_t resp_type = 0;
    size_t err_resp_type = 0;
    tie(stat, req_type) = old(CALL, make_tuple(stat, req_type), [&](tuple<status, int> o){
        status stat = get<0>(o);
        size_t req_type = get<1>(o);

        if (stat == status::COMPUTE) {
            if (node.next_real() < random_req) {
                stat = status::WAITRESP;
                req_type = node.next_real(1, ntypes_req+1);
                req = true;
            }
        } else if (stat == status::WAITRESP) {
            // the response probability depends on the type of request
            if (node.next_real() < random_resp[req_type-1]) {
                resp_type = req_type;
                stat = status::COMPUTE;
                req_type = 0;
                resp = true;
            } else if (node.next_real() < random_err_resp) {
                resp_type = 1 + req_type % ntypes_req;
                resp = true;
            } else if (node.next_real() < random_err_req)
                req = true;
        }

        return make_tuple(stat, req_type);
    });

    bool no_unwanted_response = true;
    bool no_double_request = true;
    FOR (i, 0, i<ntypes_req) {
        bool rq = req && (req_type == i+1);
        bool rs = resp && (resp_type == i+1);
        bool all_response_time = logic::all_response_time(CALL, rq, rs, resp_timeout);
        storage<response_time_monitor>(node, i+1) = !all_response_time;
        no_unwanted_response = no_unwanted_response && logic::no_unwanted_response(CALL, rq, rs);
        no_double_request = no_double_request && logic::no_double_request(CALL, rq, rs);
    }
    node.storage(fail<unwanted_response_monitor>{}) = !no_unwanted_response;
    node.storage(fail<no_doublereq_monitor>{}) = !no_double_request;

    node.storage(status_c{}) = color(status_colors[(int)stat]);
    node.storage(reqtype_c{}) = color(req_type_colors[req_type]);
}
FUN_EXPORT main_t = common::export_list<real_t, tuple<status, size_t>, logic_t, counter_t<>>;

}

}

#endif // FCPP_SERVICE_DISCOVERY_H_

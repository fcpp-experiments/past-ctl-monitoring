// Copyright © 2021 Giorgio Audrito. All Rights Reserved.

/**
 * @file service_discovery.hpp
 * @brief Implementation of the case study on service discovery.
 */

#ifndef FCPP_SERVICE_DISCOVERY_H_
#define FCPP_SERVICE_DISCOVERY_H_

#include "lib/fcpp.hpp"
#include "lib/logic_samples.hpp"


/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {

//! @brief Type of devices.
enum class devtype {
    EDGE,   // edge device
    FOG,    // fog device
    CLOUD   // cloud device
};

//! @brief Namespace containing the libraries of coordination routines.
namespace coordination {

namespace tags {
    //! @brief Parametric tag for formula failure.
    template <typename T>
    struct fail {};
    //! @brief Response time monitor formula for message type i.
    template <int i>
    struct timeout_monitor {};
    //! @brief Unwanted response monitor formula.
    struct spurious_monitor {};
    //! @brief No double requests monitor formula.
    struct double_req_monitor {};
    //! @brief Whether the node is edge, fog or cloud.
    struct node_type {};
    //! @brief Color representing the status a node (compute, wait response by type).
    struct status_c {};
    //! @brief Color representing the waiting time of a node.
    struct waiting_c {};
    //! @brief Size of the current node (strong monitor true < globally false < locally false).
    struct size {};
}

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

//! @brief Status of devices.
enum class status {
    COMPUTE,   // computing
    WAITRESP   // waiting for a response
};

//! @brief Colors to represent request type and status.
packed_color status_colors[] = {SILVER, YELLOW, LIME_GREEN, RED, FUCHSIA};

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

    if (node.storage(node_type{}) == devtype::EDGE) {
        // set random time to enter (between 0 and 20)
        times_t start_time = constant(CALL, node.next_real(0, 20));
        if (counter(CALL) == 1) {
            node.next_time(start_time);
            return;
        } else node.storage(size{}) = 15;

        // set random time to exit (between 100 and 150)
        times_t exit_time = constant(CALL, node.next_real(100, 150));
        if (node.current_time() > exit_time) {
            node.storage(size{}) = 0;
            return;
        }
    }

    bool req=false, resp=false;
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
    bool local_unwanted = false;
    bool local_duplicated = false;
    bool local_delay = false;
    FOR (i, 0, i<ntypes_req) {
        bool rq = req && (req_type == i+1);
        bool rs = resp && (resp_type == i+1);
        storage<timeout_monitor>(node, i+1) = !logic::all_response_time(CALL, rq, rs, resp_timeout);
        no_unwanted_response &= logic::no_unwanted_response(CALL, rq, rs);
        no_double_request &= logic::no_double_request(CALL, rq, rs);
        local_unwanted |= logic::my_unwanted_response(CALL, rq, rs);
        local_duplicated |= logic::my_double_request(CALL, rq, rs);
        local_delay |= logic::no_reply(CALL, rq, rs, resp_timeout);
    }
    node.storage(fail<spurious_monitor>{}) = !no_unwanted_response;
    node.storage(fail<double_req_monitor>{}) = !no_double_request;
    double waiting_time = req_type > 0 ? 1.0/counter(CALL) : 1;
    node.storage(status_c{}) = color(status_colors[req_type]);
    node.storage(waiting_c{}) = waiting_time * node.storage(status_c{}) + (1-waiting_time) * color(BLACK);
    if (local_unwanted)
        node.storage(shape{}) = shape::star;
    else if (local_duplicated)
        node.storage(shape{}) = shape::tetrahedron;
    else if (local_delay)
        node.storage(shape{}) = shape::cube;
    else
        node.storage(shape{}) = shape::sphere;
}
FUN_EXPORT main_t = common::export_list<real_t, tuple<status, size_t>, logic_t, counter_t<>>;

}

}

#endif // FCPP_SERVICE_DISCOVERY_H_

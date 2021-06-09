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

//! @brief Dummy ordering between positions.
bool operator<(vec<3> const&, vec<3> const&) {
    return false;
}

//! @brief Namespace containing the libraries of coordination routines.
namespace coordination {

namespace tags {
    //! @brief Parametric tag for formula failure.
    template <typename T>
    struct fail {};
    //! @brief Response time monitor formula for message type i.
    template <int i>
    struct response_time_monitor {};
    //! @brief Color representing the kind of a node (person, light off, light on).
    struct col {};
    //! @brief Size of the current node (strong monitor true < globally false < locally false).
    struct size {};
}

//! @brief Number of edge, fog, cloud, and all nodes
constexpr size_t edge_num = 50;
constexpr size_t fog_num = 20;
constexpr size_t cloud_num = 5;
constexpr size_t node_num = edge_num + fog_num + cloud_num;

//! @brief Which area monitor to display with sizes.
constexpr int area_display = 2;

//! @brief Probability of issuing a request while computing.
constexpr real_t random_req = 0.10;

//! @brief Probability of receiving a response while waiting
constexpr real_t random_resp = 0.20;

//! @brief Distance after which the target is taken for reached.
constexpr real_t epsilon_dist = 1;

//! @brief Distance after which the target is taken for reached.
constexpr size_t ntypes_req = 4;

//! @brief Status of devices.
enum class status {
    COMPUTE,   // computing
    WAITRESP   // waiting for a response
};

//! @brief Colors to represent status.
packed_color status_colors[] = {BLUE, RED};

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

    bool req=false, resp=false;

    size_t nsize=0;

    times_t start_time = 0;
    times_t exit_time = 0;

    // set a random job length (between 1 and 10)
    times_t random_job_length;

    bool edge = node.uid < edge_num;
    bool fog = (node.uid - edge_num >= 0) && (node.uid - edge_num < fog_num);
    bool cloud = (node.uid - edge_num - fog_num >= 0);

    nsize = 20;
    if (edge) nsize = 5;
    if (fog) nsize = 10;
    node.storage(size{}) = nsize;

    if (edge) {
        // if edge set random time to start (between 0 and 20)
        start_time = constant(CALL, node.next_real(0, 20));

        // if edge, set random time to exit (between 20 and 200)
        exit_time = constant(CALL, node.next_real(20, 200));

        if (node.current_time() < start_time) {
            node.storage(size{}) = 0;
        } else {
            node.storage(size{}) = nsize;
        }

        if (node.current_time() == exit_time) {
            node.terminate();
            return;
        }
    }

    common::get<fcpp::component::tags::power_ratio>(node.connector_data()) = cloud || fog ? 1 : 0.5;
    status stat = status::COMPUTE;
    size_t req_type = 0;
    tie(stat, req_type) = old(CALL, make_tuple(stat, req_type), [&](tuple<status, int> o){
        status stat = get<0>(o);
        size_t req_type = get<1>(o);

        if (stat == status::COMPUTE) {
            if (node.next_real() < random_req) {
                stat = status::WAITRESP;
                req_type = node.next_real(1, ntypes_req);
                req = true;
            }
        }
        if (stat == status::WAITRESP) {
            if (node.next_real() < random_resp) {
                stat = status::COMPUTE;
                req_type = 0;
                resp = true;
            }
        }

        return make_tuple(stat, req_type);
    });

    FOR (i, 0, i<ntypes_req) {
        bool all_response_time = logic::all_response_time(CALL, req, resp);
        storage<response_time_monitor>(node, i+1) = all_response_time;
    }

    node.storage(col{}) = color(status_colors[(int)stat]);
}

    FUN_EXPORT main_t = common::export_list<real_t, tuple<status, size_t>, coordination::logic_t>;
}

}

#endif // FCPP_SERVICE_DISCOVERY_H_

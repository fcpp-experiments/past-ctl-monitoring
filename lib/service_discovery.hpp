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
    //! @brief Liveness monitor formula for area i.
    template <int i>
    struct handling_monitor {};
    //! @brief Safety monitor formula for area i.
    template <int i>
    struct redundancy_monitor {};
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

//! @brief Top speed for an UAV.
constexpr real_t speed = 15;

//! @brief Top acceleration for an UAV.
constexpr real_t accel = 5;

//! @brief Probability of getting a random job while resting.
constexpr real_t random_job = 0.05;

//! @brief Minimum height while flying.
constexpr real_t flying_low = 20;

//! @brief Maximum height while flying.
constexpr real_t flying_high = 100;

//! @brief Distance after which the target is taken for reached.
constexpr real_t epsilon_dist = 1;

//! @brief Status of devices.
enum class status {
    QUIET,  // tower before asking service
    NEEDY,  // tower asking service now
    GOOD,   // tower after asking service
    WAIT,   // drone waiting for a job
    TIRED,  // drone recharging
    RISE,   // drone going towards a destination
    HANDLE, // drone handling a destination
    FALL    // drone going to rest after handling
};

//! @brief Colors to represent status.
packed_color status_colors[8] = {MAROON, RED, MAROON, BLUE, BLUE, GREEN, YELLOW, GREEN};

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

//! @brief Manages movement of drones towards targets.
FUN void drone_automaton(ARGS, status& stat, vec<3>& target) {
    switch (stat) {
        case status::RISE:
        {
            std::array<vec<3>, 2> path = {node.position(), target};
            path[0][2] = flying_low;
            path[1][2] = flying_high;
            auto d = follow_path(CALL, path, speed, 1);
            if (get<0>(d) == 1 and get<1>(d) < epsilon_dist)
                stat = status::HANDLE;
            break;
        }
        case status::HANDLE:
            stat = status::FALL;
            target = random_rectangle_target(CALL, make_vec(0,0,0), make_vec(1000,1000,0));
            break;
        case status::FALL:
        {
            std::array<vec<3>, 2> path = {target, target};
            path[0][2] = flying_low;
            auto d = follow_path(CALL, path, speed, 1);
            if (get<0>(d) == 1 and get<1>(d) < epsilon_dist)
                stat = status::TIRED;
            break;
        }
        case status::TIRED:
            follow_target(CALL, target, speed, 1);
            if (node.next_real() < random_job)
                stat = status::WAIT;
            break;
        default:
            break;
    }
}

//! @brief Service discovery case study.
MAIN() {
    using namespace tags;

    size_t nsize=0;

    // set random time to start (between 0 and 50)
    times_t start_time = constant(CALL, node.next_real(0, 10));

    // set random time to exit (between 0 and 300)
    times_t exit_time = constant(CALL, node.next_real(0, 300));

    // if (node.current_time() == exit_time) {
    //     node.terminate();
    //     return;
    // }

    bool edge = node.uid < edge_num;
    bool fog = (node.uid - edge_num >= 0) && (node.uid - edge_num < fog_num);
    bool cloud = (node.uid - edge_num - fog_num >= 0);


    nsize = 20;
    if (edge) nsize = 5;
    if (fog) nsize = 10;

    if (node.current_time() < start_time) {
        node.storage(size{}) = 0;
    } else if (node.current_time() >= start_time) {
        node.storage(size{}) = nsize;
    }

    common::get<fcpp::component::tags::power_ratio>(node.connector_data()) = cloud || fog ? 1 : 0.5;

    status stat = status::WAIT;
    vec<3> target = node.position();
    tie(stat, target) = old(CALL, make_tuple(stat, target), [&](tuple<status, vec<3>> o){
        status stat = get<0>(o);
        vec<3> target = get<1>(o);
        bool close_handling = any_hood(CALL, nbr(CALL, stat == status::HANDLE) and map_hood([&](vec<3> v){
            return distance(v, make_vec(0,0,flying_high)) < epsilon_dist;
        }, node.nbr_vec()));
        drone_automaton(CALL, stat, target);

        real_t req_dist = bis_distance(CALL, stat == status::NEEDY, 1, 80);
        vec<3> req_pos = broadcast(CALL, req_dist, node.position());
        req_pos[2] = flying_high;
        bool free = stat == status::WAIT or target == req_pos;
        real_t free_dist = free ? req_dist : INF;
        real_t closest_free = mp_collection(CALL, req_dist, free_dist, INF, [&](real_t x, real_t y){
            return min(x,y);
        }, [&](real_t x, size_t) {
            return x;
        });
        real_t req_radius = broadcast(CALL, req_dist, closest_free);
        if (stat == status::WAIT) {
            if (node.next_real() < random_job) {
                stat = status::WAIT;
            }
        }
        return make_tuple(stat, target);
    });

    for (internal::trace_cycle i{node.stack_trace, 0}; i<4; ++i) {
        int x = i % 2;
        int y = i / 2;
        bool handling = stat == status::HANDLE and target == make_vec(250+500*x,250+500*y,flying_high);
        bool area_handled = logic::area_handled(CALL, handling);
        bool no_redundancy = logic::no_redundancy(CALL, handling);
        storage<handling_monitor>(node, i+1) = not area_handled;
        storage<redundancy_monitor>(node, i+1) = not no_redundancy;
        // if (i+1 == area_display)
        //     node.storage(size{}) = 5 + (3 - no_redundancy - area_handled) * 5;
    }
    node.storage(col{}) = color(status_colors[(int)stat]);
}

}

}

#endif // FCPP_SERVICE_DISCOVERY_H_

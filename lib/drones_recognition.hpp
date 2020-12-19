// Copyright © 2020 Giorgio Audrito. All Rights Reserved.

/**
 * @file drones_recognition.hpp
 * @brief Implementation of the case study on drones recognition.
 */

#ifndef FCPP_DRONES_RECOGNITION_H_
#define FCPP_DRONES_RECOGNITION_H_

#include <cassert>
#include <limits>

#include "lib/coordination.hpp"
#include "lib/data.hpp"
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
    //! @brief Local value of the strong monitor formula.
    struct handling_monitor {};
    //! @brief Global value of the strong monitor formula.
    struct redundancy_monitor {};
    //! @brief Color representing the kind of a node (person, light off, light on).
    struct col {};
    //! @brief Size of the current node (strong monitor true < globally false < locally false).
    struct size {};
}

//! @brief Top speed for an UAV.
constexpr real_t speed = 15;

//! @brief Infinite distance.
constexpr hops_t infinity = std::numeric_limits<hops_t>::max();

//! @brief Probability of getting a random job.
constexpr real_t random_job = 0.05;

//! @brief Distance after which the target is taken for reached.
constexpr real_t epsilon_dist = 1;

//! @brief Drones recognition case study.
MAIN() {
    using namespace tags;

    bool tower = node.uid < 4;
    // TODO: controllare che torri si accorgano di essere state servite
    bool request = tower and node.current_time() > constant(CALL, node.next_real(0, 200));
    bool handling = false;
    bool resting = node.position()[2] < 1;
    node.connector_data() = tower ? 1 : 0.5;
    hops_t req_dist = bis_distance(CALL, request, 1, 80);

    vec<3> target = old(CALL, node.position(), [&](vec<3> target){
        bool free = distance(node.position(), target) < epsilon_dist and not tower;
        handling = free and target == make_vec(250,250,50);
        hops_t free_dist = free ? req_dist : infinity;
        hops_t closest_free = mp_collection(CALL, req_dist, free_dist, infinity, [&](hops_t x, hops_t y){
            return min(x,y);
        }, [&](hops_t x, size_t) {
            return x;
        });
        hops_t req_radius = broadcast(CALL, req_dist, closest_free);
        vec<3> req_pos = broadcast(CALL, req_dist, node.position());
        if (free) {
            if (free_dist <= req_radius) {
                target = req_pos;
                req_pos[2] = 50;
            } else if (node.next_real() < random_job)
                target = random_rectangle_target(CALL, make_vec(0,0,0), make_vec(1000,1000,100));
            else target[2] = 0;
        }
        return target;
    });

    if (tower) {
        int x = node.uid % 2;
        int y = node.uid / 2;
        node.position() = make_vec(250+500*x,250+500*y,0);
    } else  {
        follow_target(CALL, target, speed, 1);
    }

    bool area_handled = logic::area_handled(CALL, handling);
    bool no_redundancy = logic::no_redundancy(CALL, handling);
    bool handled_no_redundancy = logic::handled_no_redundancy(CALL, handling);
    assert(handled_no_redundancy == (no_redundancy and area_handled));

    node.storage(fail<handling_monitor>{}) = not area_handled;
    node.storage(fail<redundancy_monitor>{}) = not no_redundancy;
    if (tower) {
        node.storage(col{}) = request and not area_handled ? RED : MAROON;
    } else {
        node.storage(col{}) = resting ? DARK_OLIVE_GREEN : handling ? YELLOW : YELLOW_GREEN;
    }
    node.storage(size{}) = no_redundancy ? (area_handled ? 5 : 10) : 20;
}

}

}

#endif // FCPP_DRONES_RECOGNITION_H_

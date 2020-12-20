// Copyright © 2020 Gianluca Torta. All Rights Reserved.

/**
 * @file crowd_safety.hpp
 * @brief Implementation of the case study on crowd safety.
 */

#ifndef FCPP_CROWD_SAFETY_H_
#define FCPP_CROWD_SAFETY_H_

#include "lib/data.hpp"
#include "lib/logic_samples.hpp"
#include "lib/past_ctl.hpp"
#include "lib/data/vec.hpp"
#include "lib/coordination/time.hpp"

/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {

//! @brief Dummy ordering between positions.
bool operator<(vec<2> const&, vec<2> const&) {
    return false;
}

//! @brief Namespace containing the libraries of coordination routines.
namespace coordination {

namespace tags {
    //! @brief Parametric tag for formula failure.
    template <typename T>
    struct fail {};
    //! @brief Local value of the monitor formula.
    struct local_safety_monitor {};
    //! @brief Global value of the monitor formula.
    struct global_safety_monitor {};
    //! @brief Color representing the distance of the current node.
    struct col {};
    //! @brief Size of the current node.
    struct size {};
}


//! @brief number of areas
constexpr int nareas = 5;

//! @brief radius of the incident effects
constexpr double inc_radius = 50;

//! @brief radius of the alert effects
constexpr double alert_radius = 100;

//! @brief radius of the whole area
constexpr double world_radius = 500;

//! @brief speed of the people
constexpr double max_speed = 1.4;

//! @brief speed of message exchanges
constexpr double info_speed = 40;

//! @brief interval between rounds
constexpr double period = 1;

//! @brief Main function.
MAIN() {
    using namespace tags;

    bool isarea = (node.uid < nareas);
    node.connector_data() = isarea ? 1 : 0.5;

    times_t panic_time = constant(CALL, node.next_real(0, 300));
    times_t panic_length = constant(CALL, node.next_real(0, 100));
    bool area_panic = isarea and node.current_time() > panic_time and node.current_time() < panic_time+panic_length;

    vec<2> low = make_vec(0,0);
    vec<2> high = make_vec(500,500);

    double dist = bis_distance(CALL, area_panic, period, info_speed);

    bool safe = (dist > inc_radius); // people are safe beyond this radius
    bool alert = (dist < alert_radius); // people notice alerts within this radius
    bool runaway = (dist < inc_radius*1.2); // people escape within this radius

    if (!isarea) {
        if (alert && runaway) {
            auto f = make_tuple(nbr(CALL, dist), node.nbr_vec());
            vec<2> target = get<1>(max_hood(CALL, f));
            follow_target(CALL, target, max_speed, period);
        } else
            rectangle_walk(CALL, low, high, max_speed, period);
    }

    bool my_safety_preserved = logic::my_safety_preserved(CALL, safe, alert);
    bool all_safety_preserved = logic::all_safety_preserved(CALL, safe, alert);

    node.storage(fail<local_safety_monitor>{}) = not my_safety_preserved;
    node.storage(fail<global_safety_monitor>{}) = not all_safety_preserved;

    if (isarea)
        node.storage(tags::size{}) = area_panic ? 15 : 10;
    else
        node.storage(tags::size{}) = all_safety_preserved ? 5 : my_safety_preserved ? 10 : 15;

    if (isarea)
        node.storage(col{}) = area_panic ? FIRE_BRICK : BLACK;
    else {
        double hue;
        if (safe)
            hue = 120 + (min(dist,world_radius)-inc_radius)*120/(world_radius-inc_radius);
        else
            hue = dist*60/inc_radius;
        node.storage(col{}) = color::hsva(hue,1,1);
    }
}

}

}

#endif // FCPP_CROWD_SAFETY_H_

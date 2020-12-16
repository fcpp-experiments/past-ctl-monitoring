// Copyright © 2020 Giorgio Audrito. All Rights Reserved.

/**
 * @file smart_home.hpp
 * @brief Implementation of the case study on smart homes.
 */

#ifndef FCPP_SMART_HOME_H_
#define FCPP_SMART_HOME_H_

#include "lib/data.hpp"
#include "lib/logic_samples.hpp"


/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {

//! @brief Namespace containing the libraries of coordination routines.
namespace coordination {

namespace tags {
    //! @brief Whether the strong monitor formula is locally true.
    struct local_strong_monitor {};
    //! @brief Whether the weak monitor formula is locally true.
    struct local_weak_monitor {};
    //! @brief Whether the strong monitor formula is globally true.
    struct global_strong_monitor {};
    //! @brief Whether the weak monitor formula is globally true.
    struct global_weak_monitor {};
    //! @brief Color representing the kind of a node (person, light off, light on).
    struct col {};
    //! @brief Size of the current node (monitor ok, global no, local no).
    struct size {};
}

//! @brief Smart home case study.
MAIN() {
    using namespace tags;

    // TODO: 8x1 corridor + 8 adjacent 2x2 rooms
    rectangle_walk(CALL, make_vec(0,0), make_vec(500,500), 30.5, 1);

    // TODO: compute reasonable s,a,p
    bool s = node.uid % 7 == 0;
    bool a = s and (node.uid % 3 == 0);
    bool p = node.uid % 5 == 0;

    bool active_when_present = logic::active_when_present(CALL, s, a, p);
    bool active_when_present_twice = logic::active_when_present_twice(CALL, s, a, p);
    bool always_active_when_present = logic::always_active_when_present(CALL, s, a, p);
    bool always_active_when_present_twice = logic::always_active_when_present_twice(CALL, s, a, p);

    node.storage(local_strong_monitor{}) = active_when_present;
    node.storage(local_weak_monitor{}) = active_when_present_twice;
    node.storage(global_strong_monitor{}) = always_active_when_present;
    node.storage(global_weak_monitor{}) = always_active_when_present_twice;
    node.storage(col{}) = s ? (a ? color(1.0, 1.0, 0.0) : color(0.5, 0.5, 0.5)) : color(0.0, 0.0, 1.0);
    node.storage(size{}) = always_active_when_present_twice ? 3 : active_when_present_twice ? 6 : 10;
}

}

}

#endif // FCPP_SMART_HOME_H_

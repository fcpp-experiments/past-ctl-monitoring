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

/**
 * @brief The location of the door of each room (with an offset).
 *
 * Columns vary from 0 to 3.
 * Room rows are -1 and +1; row zero is the corridor.
 * The offset varies from -3 to +2.
 */
FUN vec<2> room_door(ARGS, int row, int column, int offset) { CODE
    return make_vec(6*column+3, (1.5 + 0.25*offset)*row);
}

//! @brief Get the room index from the position.
FUN tuple<int,int> get_room(ARGS, vec<2> pos) { CODE
    if (-1 < pos[1] and pos[1] < 1) return {0, 0}; // corridor
    return {pos[1] > 0 ? 1 : -1, int(pos[0] / 6)};
}

//! @brief Generates a target in a given row and column.
FUN vec<2> random_room_target(ARGS, int row, int column) { CODE
    if (row == 0) {
        column = node.next_int(0, 3);
        row = node.next_int(0, 1);
        if (row == 0) row = -1;
        return room_door(CALL, row, column, -1);
    }
    return random_rectangle_target(CALL, make_vec(6*column+1, 2.5*row), make_vec(6*column+5, 6.5*row));
}

//! @brief Random walking within a 24x3m central corridor with 8 adjacent 6x6m rooms.
FUN void building_walk(ARGS, real_t max_v, real_t period) { CODE
    if (node.uid < 12) {
        int row = node.uid / 4;
        int col = node.uid % 4;
        node.position() = make_vec(6*col+3, 5*row-5);
        return;
    }
    old(CALL, node.position(), [&](vec<2> t){
        real_t dist = follow_target(CALL, t, max_v, period);
        if (dist < max_v * period) { // maybe change target
            tuple<int,int> room = get_room(CALL, t);
            int row = get<0>(room);
            int col = get<1>(room);
            if (row == 0)
                t = random_room_target(CALL, row, col);
            else if (t == room_door(CALL, row, col, +1))
                t = room_door(CALL, row, col, -3);
            else if (t == room_door(CALL, row, col, -1))
                t = room_door(CALL, row, col, +2);
            else if (t == room_door(CALL, row, col, +2))
                t = random_room_target(CALL, row, col);
            else if (node.next_real() < 0.05) {
                if (node.next_real() < 0.5)
                    t = random_room_target(CALL, row, col);
                else
                    t = room_door(CALL, row, col, +1);
            }
        }
        return t;
    });
}


//! @brief Smart home case study.
MAIN() {
    using namespace tags;

    building_walk(CALL, 1.4, 1);

    constexpr real_t FALSE_POSITIVE = 0.003; // prob. of seeing something which is not there
    constexpr real_t FALSE_NEGATIVE = 0.003; // prob. of not seeing something which is there
    size_t c = count_hood(CALL) - 1;
    real_t prob = (1-FALSE_POSITIVE)*(1-pow(FALSE_NEGATIVE,c)) + FALSE_POSITIVE;
    bool s = node.uid < 12;
    bool p = c > 0;
    bool a = s and (node.next_real() < prob);

    bool active_when_present = logic::active_when_present(CALL, s, a, p);
    bool active_when_present_twice = logic::active_when_present_twice(CALL, s, a, p);
    bool always_active_when_present = logic::always_active_when_present(CALL, s, a, p);
    bool always_active_when_present_twice = logic::always_active_when_present_twice(CALL, s, a, p);

    node.storage(local_strong_monitor{}) = active_when_present;
    node.storage(local_weak_monitor{}) = active_when_present_twice;
    node.storage(global_strong_monitor{}) = always_active_when_present;
    node.storage(global_weak_monitor{}) = always_active_when_present_twice;
    node.storage(col{}) = s ? (a ? YELLOW : SILVER) : PURPLE;
    node.storage(size{}) = always_active_when_present_twice ? 0.3 : active_when_present_twice ? 0.5 : 0.8;
}

}

}

#endif // FCPP_SMART_HOME_H_

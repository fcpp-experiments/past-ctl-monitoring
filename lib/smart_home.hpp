// Copyright © 2021 Giorgio Audrito. All Rights Reserved.

/**
 * @file smart_home.hpp
 * @brief Implementation of the case study on smart homes.
 */

#ifndef FCPP_SMART_HOME_H_
#define FCPP_SMART_HOME_H_

#include "lib/fcpp.hpp"
#include "lib/logic_samples.hpp"


/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {

//! @brief Namespace containing the libraries of coordination routines.
namespace coordination {

namespace tags {
    //! @brief Parametric tag for formula failure.
    template <typename T>
    struct fail {};
    //! @brief Local value of the strong monitor formula.
    struct local_strong_monitor {};
    //! @brief Local value of the weak monitor formula.
    struct local_weak_monitor {};
    //! @brief Global value of the strong monitor formula.
    struct global_strong_monitor {};
    //! @brief Global value of the weak monitor formula.
    struct global_weak_monitor {};
    //! @brief Color representing the kind of a node (person, light off, light on).
    struct col {};
    //! @brief Size of the current node (strong monitor true < globally false < locally false).
    struct size {};
}

/**
 * @brief The location of the door of each room (with an offset).
 *
 * Columns vary from 0 to 3.
 * Room rows are -1 and +1; row zero is the corridor.
 * The offset varies from -3 to +2.
 */
FUN vec<3> room_door(ARGS, int row, int column, int offset) { CODE
    return make_vec(6*column+3, (1.5 + 0.25*offset)*row + 7.5, 0);
}

//! @brief Get the room index from the position.
FUN tuple<int,int> get_room(ARGS, vec<3> pos) { CODE
    pos[1] -= 7.5;
    if (-1 < pos[1] and pos[1] < 1) return {0, 0}; // corridor
    return {pos[1] > 0 ? 1 : -1, int(pos[0] / 6)};
}

//! @brief Generates a target in a given row and column.
FUN vec<3> random_room_target(ARGS, int row, int column) { CODE
    if (row == 0) {
        column = node.next_int(0, 3);
        row = node.next_int(0, 1);
        if (row == 0) row = -1;
        return room_door(CALL, row, column, -1);
    }
    return random_rectangle_target(CALL, make_vec(6*column+1, 2.5*row+7.5, 0), make_vec(6*column+5, 6.5*row+7.5, 0));
}

//! @brief Random walking within a 24x3m central corridor with 8 adjacent 6x6m rooms.
FUN void building_walk(ARGS, real_t max_v, real_t period) { CODE
    if (node.uid < 12) {
        int row = node.uid / 4;
        int col = node.uid % 4;
        node.position() = make_vec(6*col+3, 4.5*row+3, 2);
        return;
    } else if (node.uid < 14 and old(CALL, true, false)) {
        if (node.uid == 12) node.position() = make_vec(0.9, 0.9, 0);
        if (node.uid == 13) node.position() = make_vec(23.1, 14.1, 0);
    }
    old(CALL, node.position(), [&](vec<3> t){
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

    constexpr real_t STILL_FAIL = 0.003; // prob. of failure in still situation
    constexpr real_t SWITCH_FAIL = 0.05; // prob. of failure in changing situation
    size_t c = count_hood(CALL) - 1;
    bool s = node.uid < 12;
    bool p = c > 0;
    real_t prob = p == old(CALL, p) ? STILL_FAIL : SWITCH_FAIL;
    bool a = s and ((node.next_real() < prob) != p);

    bool active_when_present = logic::active_when_present(CALL, s, a, p);
    bool active_when_present_twice = logic::active_when_present_twice(CALL, s, a, p);
    bool always_active_when_present = logic::always_active_when_present(CALL, s, a, p);
    bool always_active_when_present_twice = logic::always_active_when_present_twice(CALL, s, a, p);
    assert(active_when_present <= active_when_present_twice);
    assert(always_active_when_present <= active_when_present);
    assert(always_active_when_present <= always_active_when_present_twice);
    assert(always_active_when_present_twice <= active_when_present_twice);

    node.storage(fail<local_strong_monitor>{}) = not active_when_present;
    node.storage(fail<local_weak_monitor>{}) = not active_when_present_twice;
    node.storage(fail<global_strong_monitor>{}) = not always_active_when_present;
    node.storage(fail<global_weak_monitor>{}) = not always_active_when_present_twice;
    node.storage(col{}) = color(s ? (a ? YELLOW : SILVER) : TAN);
    node.storage(size{}) = always_active_when_present_twice ? 0.3 : active_when_present_twice ? 0.5 : 0.8;
}

}

}

#endif // FCPP_SMART_HOME_H_

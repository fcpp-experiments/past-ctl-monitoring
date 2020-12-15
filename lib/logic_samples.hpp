// Copyright © 2020 Giorgio Audrito. All Rights Reserved.

/**
 * @file past_ctl.hpp
 * @brief Implementation of the case study comparing collection algorithms.
 */

#ifndef FCPP_LOGIC_SAMPLES_H_
#define FCPP_LOGIC_SAMPLES_H_

#include "lib/beautify.hpp"
#include "lib/coordination/utils.hpp"


/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {

//! @brief Namespace containing the libraries of coordination routines.
namespace coordination {

//! @brief Namespace containing logical operators and formulas.
namespace logic {

//! @brief During alert, once safe stays safe.
FUN bool my_safety_preserved(ARGS, bool safe, bool alert) { CODE
    return H(CALL, Y(CALL, safe && alert) <= (safe || !alert));
}

//! @brief During alert, once safe stays safe.
FUN bool all_safety_preserved(ARGS, bool safe, bool alert) { CODE
    return AH(CALL, Y(CALL, safe && alert) <= (safe || !alert));
}


//! @brief Area is eventually handled.
FUN bool area_handled(ARGS, bool handling) { CODE
    return EP(CALL, handling);
}

//! @brief Area is eventually handled by drone heading there since then.
FUN bool handled_heading(ARGS, bool handling, bool heading) { CODE
    return EP(CALL, handling && H(CALL, heading));
}

//! @brief Drones don't handle if area handled (first form).
FUN bool no_redundancy1(ARGS, bool handling) { CODE
    return AH(CALL, !(handling && EY(CALL, EP(CALL, handling))));
}

//! @brief Drones don't handle if area handled (second form).
FUN bool no_redundancy2(ARGS, bool handling) { CODE
    return AS(CALL, !handling, handling && AY(CALL, AH(CALL, !handling)));
}

//! @brief Drones don't handle if area handled (checks both forms match).
FUN bool no_redundancy(ARGS, bool handling) { CODE
    bool b1 = no_redundancy1(CALL, handling);
    bool b2 = no_redundancy2(CALL, handling);
    assert(b1 == b2);
    return b1;
}


//! @brief System is active whenever proximity.
FUN bool active_when_present(ARGS, bool s, bool a, bool p) { CODE
    return AH(CALL, s <= (p == a));
}

//! @brief System is active whenever proximity consistent for two rounds.
FUN bool active_when_present_twice(ARGS, bool s, bool a, bool p) { CODE
    return AH(CALL, s <= ((p && Y(CALL, p)) <= a && (!p && Y(CALL, !p)) <= !a));
}

}

//! @brief Crowd safety case study.
FUN void crowd_safety(ARGS) { CODE
//    logic::my_safety_preserved(CALL, safe, alert);
//    logic::all_safety_preserved(CALL, safe, alert);
    // TODO: people randomly walking in area; then a sub-area becomes dangerous and they evacuate through gradients
}

//! @brief Drones recognition case study.
FUN void drones_recognition(ARGS) { CODE
//    logic::area_handled(CALL, handling);
//    logic::handled_heading(CALL, handling, heading);
//    logic::no_redundancy(CALL, handling);
    // TODO: how many areas? Are they just point that need to be reached? Some drones busy with random walking, other steady and available do rush to handle areas
}

//! @brief Smart home case study.
FUN void smart_home(ARGS) { CODE
//    logic::active_when_present(CALL, s, a, p);
//    logic::active_when_present_twice(CALL, s, a, p);
    // TODO: just a corridor, or corridor + adjacent rooms?
}


}

}

#endif // FCPP_LOGIC_SAMPLES_H_

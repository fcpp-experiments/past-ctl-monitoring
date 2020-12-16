// Copyright © 2020 Giorgio Audrito. All Rights Reserved.

/**
 * @file crowd_safety.hpp
 * @brief Implementation of the case study on crowd safety.
 */

#ifndef FCPP_CROWD_SAFETY_H_
#define FCPP_CROWD_SAFETY_H_

#include "lib/logic_samples.hpp"


/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {

//! @brief Namespace containing the libraries of coordination routines.
namespace coordination {

//! @brief Crowd safety case study.
FUN void crowd_safety(ARGS) { CODE
    bool safe = true;
    bool alert = false;
    bool my_safety_preserved = logic::my_safety_preserved(CALL, safe, alert);
    bool all_safety_preserved = logic::all_safety_preserved(CALL, safe, alert);
    // TODO: people randomly walking in area; then a sub-area becomes dangerous and they evacuate through gradients
}

}

}

#endif // FCPP_CROWD_SAFETY_H_

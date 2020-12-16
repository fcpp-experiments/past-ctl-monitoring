// Copyright © 2020 Giorgio Audrito. All Rights Reserved.

/**
 * @file drones_recognition.hpp
 * @brief Implementation of the case study on drones recognition.
 */

#ifndef FCPP_DRONES_RECOGNITION_H_
#define FCPP_DRONES_RECOGNITION_H_

#include <cassert>

#include "lib/logic_samples.hpp"


/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {

//! @brief Namespace containing the libraries of coordination routines.
namespace coordination {

//! @brief Drones recognition case study.
FUN void drones_recognition(ARGS) { CODE
    bool handling = false;
    bool heading = false;
    bool area_handled = logic::area_handled(CALL, handling);
    bool handled_heading = logic::handled_heading(CALL, handling, heading);
    bool no_redundancy = logic::no_redundancy(CALL, handling);
    bool handled_no_redundancy = logic::handled_no_redundancy(CALL, handling);
    assert(handled_no_redundancy == (no_redundancy and area_handled));
    // TODO: 4 square areas in a 2x2 grid. Handling an area means reaching its center. Some drones busy with random walking, other steady and available to rush to handle areas.
}

}

}

#endif // FCPP_DRONES_RECOGNITION_H_

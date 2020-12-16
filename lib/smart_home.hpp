// Copyright © 2020 Giorgio Audrito. All Rights Reserved.

/**
 * @file smart_home.hpp
 * @brief Implementation of the case study on smart homes.
 */

#ifndef FCPP_SMART_HOME_H_
#define FCPP_SMART_HOME_H_

#include "lib/logic_samples.hpp"


/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {

//! @brief Namespace containing the libraries of coordination routines.
namespace coordination {

//! @brief Smart home case study.
FUN void smart_home(ARGS) { CODE
    bool s = false;
    bool a = false;
    bool p = false;
    bool active_when_present = logic::active_when_present(CALL, s, a, p);
    bool active_when_present_twice = logic::active_when_present_twice(CALL, s, a, p);
    // TODO: 8x1 corridor + 8 adjacent 2x2 rooms
}

}

}

#endif // FCPP_SMART_HOME_H_

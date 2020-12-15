// Copyright © 2020 Giorgio Audrito. All Rights Reserved.

/**
 * @file past_ctl.hpp
 * @brief Implementation of the case study comparing collection algorithms.
 */

#ifndef FCPP_PAST_CTL_H_
#define FCPP_PAST_CTL_H_

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

//! @brief Yesterday in the same device.
FUN bool Y(ARGS, bool F) { CODE
    return old(CALL, F);
}

//! @brief Yesterday in all devices.
FUN bool AY(ARGS, bool F) { CODE
    return nbr(CALL, true, [&](field<bool> n){
        return make_tuple(all_hood(CALL, n), F);
    });
}

//! @brief Yesterday in some device.
FUN bool EY(ARGS, bool F) { CODE
    return nbr(CALL, true, [&](field<bool> n){
        return make_tuple(any_hood(CALL, n), F);
    });
}

//! @brief F1 holds since F2 held in the same device.
FUN bool S(ARGS, bool F1, bool F2) { CODE
    return old(CALL, false, [&](bool o){
        return F2 || (F1 && o);
    });
}

//! @brief F1 holds since F2 held in all devices.
FUN bool AS(ARGS, bool F1, bool F2) { CODE
    return nbr(CALL, false, [&](field<bool> n){
        return F2 || (F1 && all_hood(CALL, n));
    });
}

//! @brief F1 holds since F2 held in any device.
FUN bool ES(ARGS, bool F1, bool F2) { CODE
    return nbr(CALL, false, [&](field<bool> n){
        return F2 || (F1 && all_hood(CALL, n));
    });
}

//! @brief Previously in the same device.
FUN bool P(ARGS, bool F) { CODE
    return old(CALL, false, [&](bool o){
        return F || o;
    });
}

//! @brief Previously in all devices.
FUN bool AP(ARGS, bool F) { CODE
    return nbr(CALL, false, [&](field<bool> n){
        return F || all_hood(CALL, n);
    });
}

//! @brief Previously in any device.
FUN bool EP(ARGS, bool F) { CODE
    return nbr(CALL, false, [&](field<bool> n){
        return F || any_hood(CALL, n);
    });
}

//! @brief Historically in the same device.
FUN bool H(ARGS, bool F) { CODE
    return old(CALL, true, [&](bool o){
        return F && o;
    });
}

//! @brief Historically in all devices.
FUN bool AH(ARGS, bool F) { CODE
    return nbr(CALL, true, [&](field<bool> n){
        return F && all_hood(CALL, n);
    });
}

//! @brief Historically in any device.
FUN bool EH(ARGS, bool F) { CODE
    return nbr(CALL, true, [&](field<bool> n){
        return F && any_hood(CALL, n);
    });
}

}

}

}

#endif // FCPP_PAST_CTL_H_

// Copyright © 2021 Giorgio Audrito. All Rights Reserved.

/**
 * @file logic_samples.hpp
 * @brief Implementation of the Past-CTL logical formulas used in case studies.
 */

#ifndef FCPP_LOGIC_SAMPLES_H_
#define FCPP_LOGIC_SAMPLES_H_

#include "lib/past_ctl.hpp"


/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {

//! @brief Namespace containing the libraries of coordination routines.
namespace coordination {

//! @brief The types used in export in the logic namespace.
FUN_EXPORT logic_t = common::export_list<bool>;

//! @brief Namespace containing logical operators and formulas.
namespace logic {

//! @brief Response without corresponding request in the current round.
FUN bool my_unwanted_response(ARGS, bool req, bool resp) { CODE
    return !(resp <= Y(CALL, S(CALL, !resp, req)));
}

//! @brief No response without corresponding request.
FUN bool no_unwanted_response(ARGS, bool req, bool resp) { CODE
    return AH(CALL, resp <= S(CALL, !resp, req));
}

//! @brief Making a second request before receiving a response in the current round.
FUN bool my_double_request(ARGS, bool req, bool resp) { CODE
    return Y(CALL, S(CALL, !resp, req)) & req;
}

//! @brief No second request before receiving a response.
FUN bool no_double_request(ARGS, bool req, bool resp) { CODE
    return !EP(CALL, Y(CALL, S(CALL, !resp, req)) & req);
}

//! @brief No reply for n round after a request.
FUN bool no_reply(ARGS, bool req, bool resp, size_t n) { CODE
    if (n==0)
        return req;
    else
        return (!resp & Y(CALL, no_reply(CALL, req, resp, n-1)));
}

//! @brief Response comes always within n rounds.
FUN bool all_response_time(ARGS, bool req, bool resp, size_t n) { CODE
    return !EP(CALL, no_reply(CALL, req, resp, n));
}


//! @brief During alert, once safe stays safe.
FUN bool my_safety_preserved(ARGS, bool safe, bool alert) { CODE
    return H(CALL, Y(CALL, safe & alert) <= (safe | !alert));
}

//! @brief During alert, once safe stays safe.
FUN bool all_safety_preserved(ARGS, bool safe, bool alert) { CODE
    return AH(CALL, Y(CALL, safe & alert) <= (safe | !alert));
}


//! @brief Area is eventually handled.
FUN bool area_handled(ARGS, bool handling) { CODE
    return EP(CALL, handling);
}

//! @brief Drones don't handle if area handled (first form).
FUN bool no_redundancy(ARGS, bool handling) { CODE
    return AH(CALL, !(handling & EY(CALL, EP(CALL, handling))));
}


//! @brief System is active whenever proximity.
FUN bool active_when_present(ARGS, bool s, bool a, bool p) { CODE
    return s <= (p == a);
}

//! @brief System is active whenever proximity.
FUN bool always_active_when_present(ARGS, bool s, bool a, bool p) { CODE
    return AH(CALL, active_when_present(CALL, s, a, p));
}

//! @brief System is active whenever proximity consistent for two rounds.
FUN bool active_when_present_twice(ARGS, bool s, bool a, bool p) { CODE
    return s <= ((p & Y(CALL, p)) <= a & (!p & Y(CALL, !p)) <= !a);
}

//! @brief System is active whenever proximity consistent for two rounds.
FUN bool always_active_when_present_twice(ARGS, bool s, bool a, bool p) { CODE
    return AH(CALL, active_when_present_twice(CALL, s, a, p));
}

}

}

}

#endif // FCPP_LOGIC_SAMPLES_H_

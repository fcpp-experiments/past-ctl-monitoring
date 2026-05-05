// Copyright © 2026 Giordano Scarso, Giorgio Audrito. All Rights Reserved.

/**
 * @file smart_grid.hpp
 * @brief Implementation of the case study on smart grid.
 */

#ifndef FCPP_SMART_GRID_H_
#define FCPP_SMART_GRID_H_

#include <stdlib.h>
#include <time.h>
#include "lib/fcpp.hpp"
#include "lib/logic_samples.hpp"

constexpr int SOURCE		= 0;
constexpr int USER		= 99;
constexpr int FAIL_CHANCE	= 10;
constexpr int REPAIR_CHANCE	= 40;
constexpr int UPDATE_TIME	= 100;
constexpr int COMM_RANGE	= 75;


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
    //! @brief Response time monitor formula for message type i.
    template <int i>
    struct timeout_monitor {};
    //! @brief Unwanted response monitor formula.
    struct spurious_monitor {};
    //! @brief No double requests monitor formula.
    struct double_req_monitor {};
    //! @brief Color representing the status a node (compute, wait response by type).
    struct status_c {};
    //! @brief Size of the current node (strong monitor true < globally false < locally false).
    struct size {};
    struct curr_status {};
}

//! @brief Status of devices.
enum sim_status { UP, CONNECT, DOWN };

//! @brief Colors to represent request type and status.
packed_color status_colors[] = {GREEN, BLUE, BLACK};

//! @brief Helper function to access storage.
template <template<int> class T, typename node_t>
bool& storage(node_t& node, size_t i) {
    using namespace tags;
    switch (i) {
    case 1:
        return node.storage(fail<T<1>>{});
    case 2:
        return node.storage(fail<T<2>>{});
    case 3:
        return node.storage(fail<T<3>>{});
    default:
        assert(i == 4);
        return node.storage(fail<T<4>>{});
    }
}

//! @brief Service discovery case study.
MAIN() {
    using namespace tags;
    using namespace component::tags;

    if (counter(CALL) == 1) {
	    node.storage(size{}) = 15;
	    node.storage(status_c{}) == color(GREEN);
	    node.storage(shape{}) = shape::cube;
	    node.storage(curr_status{}) = sim_status::UP;
	    srand(time(NULL));
	    return;
    }

    if (node.uid != SOURCE && node.uid != USER) {
	    int toggle_chance = 100;
	    if (counter(CALL) % UPDATE_TIME == 0) {
		    toggle_chance = rand() % 100;
		    if(node.storage(curr_status{}) == sim_status::UP && toggle_chance < FAIL_CHANCE) {
			    node.storage(curr_status{}) = sim_status::DOWN;
		    } else if(node.storage(curr_status{}) == sim_status::CONNECT && toggle_chance < FAIL_CHANCE) {
			    node.storage(curr_status{}) = sim_status::DOWN;
		    } else if(node.storage(curr_status{}) == sim_status::DOWN && toggle_chance < REPAIR_CHANCE) {
			    node.storage(curr_status{}) = sim_status::UP;
		    }
		    sim_status current_state = node.storage(curr_status{});
		    node.storage(status_c{}) = color(status_colors[current_state]);
		    return;
	    }
    }

    bool no_unwanted_response = true;
    bool no_double_request = true;
    bool local_unwanted = false;
    bool local_duplicated = false;
    bool local_delay = false;
    int from_source = 50*50;
    int from_user   = 50*50;
    node.storage(fail<spurious_monitor>{}) = !no_unwanted_response;
    node.storage(fail<double_req_monitor>{}) = !no_double_request;
    if (node.storage(curr_status{}) == sim_status::UP ||
	node.storage(curr_status{}) == sim_status::CONNECT) {
	    from_source = abf_hops(CALL, node.uid == SOURCE);
	    from_user   = abf_hops(CALL, node.uid == USER);
    }
    if (node.uid == SOURCE) {
        node.storage(shape{}) = shape::star;
	node.storage(curr_status{}) = sim_status::UP;
    } else if (node.uid == USER) {
        node.storage(shape{}) = shape::tetrahedron;
	node.storage(curr_status{}) = sim_status::UP;
    } else {
        if (from_source < 50 && from_user < 50) {
		node.storage(curr_status{}) = sim_status::CONNECT;
        } else {
		if(node.storage(curr_status{}) == sim_status::CONNECT)
			node.storage(curr_status{}) = sim_status::UP;
        }
    }
    sim_status current_state = node.storage(curr_status{});
    node.storage(status_c{}) = color(status_colors[current_state]);
}
FUN_EXPORT main_t = common::export_list<
	real_t,
	sim_status,
	tuple<status, size_t>,
	logic_t,
	counter_t<>,
	abf_hops_t>;
}

}

#endif // FCPP_SMART_GRID_H_

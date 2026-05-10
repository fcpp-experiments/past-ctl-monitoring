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

// SIMULATION PARAMETER - EDIT TO UPDATE SCENARIO

// UID of the source node
constexpr int SOURCE		= 0;
// UID of the user node
constexpr int USER		= 99;
// Probability of failure for the intermediate nodes (default: 10%)
constexpr int FAIL_CHANCE	= 10;
// Probability of repairment for the intermediate nodes (default: 40%)
constexpr int REPAIR_CHANCE	= 40;
// How often nodes can change state, since nodes have a 10Hz frequency 100
// corresponds to 10s (default: 100 equivalent to 10s)
constexpr int UPDATE_TIME	= 100;
// Maximum distance for communication between nodes (default: 75)
constexpr int COMM_RANGE	= 75;


/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {

//! @brief Namespace containing the libraries of coordination routines.
namespace coordination {

namespace tags {
    //! @brief Parametric tag for formula.
    template <typename T>
    struct flag {};
    //! @brief Tag for monitor formula.
    struct device_up_monitor {};
    struct global_up_monitor {};
    struct device_biconnection_monitor {};
    //! @brief Color representing the status a node (online, connected, offline).
    struct status_c {};
    //! @brief Color representing the property of a node (to be used for
    // displaying verified property on the single node while running the
    // simulation).
    struct property_c {};
    //! @brief Enum representing the status a node (online, connected, offline).
    struct curr_status {};
    //! @brief Size of the current node.
    struct size {};
}

//! @brief Status of devices.
enum sim_status { UP, CONNECT, DOWN };

//! @brief Colors to represent node status.
// Green nodes are online.
// Blue nodes are online and connected to the source and user node.
// Black nodes are offline.
packed_color status_colors[] = {GREEN, BLUE, BLACK};

FUN bool always_up(ARGS, bool up) { CODE
    using namespace coordination::logic;
    return true;
}

FUN bool nearby_up(ARGS, bool up) { CODE
    using namespace coordination::logic;
    return true;
}

FUN bool always_connected(ARGS, bool user, bool source) { CODE
    using namespace coordination::logic;
    return true;
}

//! @brief Smart grid case study.
MAIN() {
    using namespace tags;
    using namespace component::tags;

    // Node initialization
    if (counter(CALL) == 1) {
	    node.storage(size{}) = 15;
	    node.storage(status_c{}) = color(GREEN);
	    node.storage(property_c{}) = color(GRAY);
	    node.storage(shape{}) = shape::cube;
	    node.storage(curr_status{}) = sim_status::UP;
	    srand(time(NULL));
	    return;
    }

    // Update intermediate node
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
	    }
    }

    bool device_up = node.storage(curr_status{}) != sim_status::DOWN;
    bool source_conn = false;
    bool user_conn = false;
    int from_source = 50*50;
    int from_user   = 50*50;
    if (node.storage(curr_status{}) == sim_status::UP ||
	node.storage(curr_status{}) == sim_status::CONNECT) {
	    from_source = abf_hops(CALL, node.uid == SOURCE);
	    from_user   = abf_hops(CALL, node.uid == USER);
    }
    source_conn = from_source < 50;
    user_conn = from_user < 50;
    node.storage(flag<device_up_monitor>{}) = always_up(CALL, device_up);
    node.storage(flag<global_up_monitor>{}) = nearby_up(CALL, device_up);
    node.storage(flag<device_biconnection_monitor>{}) = always_connected(CALL, user_conn, source_conn);
    if (node.uid == SOURCE) {
        node.storage(shape{}) = shape::star;
	node.storage(curr_status{}) = sim_status::UP;
    } else if (node.uid == USER) {
        node.storage(shape{}) = shape::tetrahedron;
	node.storage(curr_status{}) = sim_status::UP;
    } else {
        if (source_conn && user_conn) {
		node.storage(curr_status{}) = sim_status::CONNECT;
        } else {
		if(node.storage(curr_status{}) == sim_status::CONNECT)
			node.storage(curr_status{}) = sim_status::UP;
        }
    }
    sim_status current_state = node.storage(curr_status{});
    node.storage(status_c{}) = color(status_colors[current_state]);

    // Change color based on specified property value
    if ( node.storage(flag<device_up_monitor>{}) ) {
	    node.storage(property_c{}) = color(GREEN);
    } else {
	    node.storage(property_c{}) = color(RED);
    }
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

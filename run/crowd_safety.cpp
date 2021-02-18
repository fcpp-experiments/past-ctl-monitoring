// Copyright © 2020 Gianluca Torta. All Rights Reserved.

#include "lib/fcpp.hpp"
#include "lib/simulation/displayer.hpp"
#include "lib/crowd_safety.hpp"

/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {

//! @brief Namespace for all FCPP components.
namespace component {

/**
 * @brief Combination of components for interactive simulations.
 *
 * It can be instantiated as `interactive_simulator<options...>::net`.
 */
DECLARE_COMBINE(interactive_simulator, displayer, calculus, simulated_connector, simulated_positioner, timer, scheduler, logger, storage, spawner, identifier, randomizer);

}

}


using namespace fcpp;
using namespace component::tags;
using namespace coordination::tags;


//! @brief Number of people in the area.
constexpr int node_num = 100;

//! @brief Dimensionality of the space.
constexpr size_t dim = 2;


//! @brief Description of the round schedule.
using round_s = sequence::periodic<
    distribution::interval_n<times_t, 0, 1>,
    distribution::weibull_n<times_t, 10, 1, 10>
>;

//! @brief Description of the export schedule.
using export_s = sequence::periodic_n<1, 0, 1>;

//! @brief Description of the sequence of node creation events.
using spawn_s = sequence::multiple_n<node_num, 0>;

//! @brief Description of the initial position distribution.
using rectangle_d = distribution::rect_n<1, 0, 0, 500, 500>;

//! @brief Storage tags and types.
using storage_t = tuple_store<
    fail<local_safety_monitor>,     bool,
    fail<global_safety_monitor>,    bool,
    col,                            color,
    size,                           double
>;

//! @brief Storage tags to be logged with aggregators.
using aggregator_t = aggregators<
    fail<local_safety_monitor>,     aggregator::mean<double>,
    fail<global_safety_monitor>,    aggregator::mean<double>
>;

//! @brief Plot description.
using plotter_t = plot::plotter<aggregator_t, plot::time, fail>;

//! @brief Options list.
DECLARE_OPTIONS(opt,
    parallel<false>,
    synchronised<false>,
    dimension<dim>,
    program<coordination::main>,
    exports<vec<dim>, double, bool, tuple<double,double>>,
    retain<metric::retain<2,1>>,
    connector<connect::powered<200>>,
    round_schedule<round_s>,
    log_schedule<export_s>,
    spawn_schedule<spawn_s>,
    init<x, rectangle_d>,
    storage_t,
    aggregator_t,
    plot_type<plotter_t>,
    size_tag<size>,
    color_tag<col>
);

int main() {
  plotter_t p;
  std::cout << "/*\n";
  {
    component::interactive_simulator<opt>::net network{common::make_tagged_tuple<plotter,texture>(&p,"park.jpg")};
    network.run();
  }
  std::cout << "*/\n";
  std::cout << plot::file("crowd_safety", p.build());
  return 0;
}

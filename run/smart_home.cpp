// Copyright © 2020 Giorgio Audrito. All Rights Reserved.

#include "lib/fcpp.hpp"
#include "lib/simulation/displayer.hpp"
#include "lib/smart_home.hpp"

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


//! @brief Number of lights in the building.
constexpr size_t lights_num = 12;

//! @brief Number of walking people in the building.
constexpr size_t people_num = 12;

//! @brief Dimensionality of the space.
constexpr size_t dim = 3;


//! @brief Description of the round schedule.
using round_s = sequence::periodic<
    distribution::interval_n<times_t, 0, 1>,
    distribution::weibull_n<times_t, 10, 1, 10>
>;

//! @brief Description of the export schedule.
using export_s = sequence::periodic_n<1, 0, 1>;

//! @brief Description of the sequence of node creation events.
using spawn_s = sequence::multiple_n<lights_num + people_num, 0>;

//! @brief Description of the initial position distribution.
using rectangle_d = distribution::rect_n<1, 0, -7, 0, 24, 7, 0>;

//! @brief Storage tags and types.
using storage_t = tuple_store<
    fail<local_strong_monitor>,     bool,
    fail<local_weak_monitor>,       bool,
    fail<global_strong_monitor>,    bool,
    fail<global_weak_monitor>,      bool,
    col,                            color,
    size,                           double
>;

//! @brief Storage tags to be logged with aggregators.
using aggregator_t = aggregators<
    fail<local_strong_monitor>,     aggregator::mean<double>,
    fail<local_weak_monitor>,       aggregator::mean<double>,
    fail<global_strong_monitor>,    aggregator::mean<double>,
    fail<global_weak_monitor>,      aggregator::mean<double>
>;

//! @brief Plot description.
using plotter_t = plot::plotter<aggregator_t, plot::time, fail>;

//! @brief Options list.
DECLARE_OPTIONS(opt,
    parallel<false>,
    synchronised<false>,
    dimension<dim>,
    program<coordination::main>,
    exports<vec<dim>, bool>,
    retain<metric::retain<2,1>>,
    connector<connect::fixed<3, 1, dim>>,
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
        component::interactive_simulator<opt>::net network{common::make_tagged_tuple<plotter>(&p)};
        network.run();
    }
    std::cout << "*/\n";
    std::cout << plot::file("smart_home", p.build());
    return 0;
}

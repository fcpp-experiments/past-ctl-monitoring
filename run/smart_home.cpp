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

#define LIGHTS_NUM  12
#define PEOPLE_NUM  16

using round_s = sequence::periodic<
    distribution::interval_n<times_t, 0, 1>,
    distribution::weibull_n<times_t, 10, 1, 10>
>;

using rectangle_d = distribution::rect_n<1, 0, -1, 24, 1>;
constexpr size_t dim = 2;

DECLARE_OPTIONS(opt,
    parallel<false>,
    synchronised<false>,
    program<coordination::main>,
    round_schedule<round_s>,
    dimension<dim>,
    exports<vec<dim>, bool>,
    retain<metric::retain<2,1>>,
    log_schedule<sequence::periodic_n<1, 0, 1>>,
    tuple_store<
        local_strong_monitor,   bool,
        local_weak_monitor,     bool,
        global_strong_monitor,  bool,
        global_weak_monitor,    bool,
        col,                    color,
        size,                   double
    >,
    aggregators<
        local_strong_monitor,   aggregator::mean<double>,
        local_weak_monitor,     aggregator::mean<int>,
        global_strong_monitor,  aggregator::mean<double>,
        global_weak_monitor,    aggregator::mean<int>
    >,
    spawn_schedule<sequence::multiple_n<LIGHTS_NUM+PEOPLE_NUM, 0>>,
    init<x, rectangle_d>,
    connector<connect::fixed<3>>,
    size_tag<size>,
    color_tag<col>
);

int main() {
    component::interactive_simulator<opt>::net network{common::make_tagged_tuple<epsilon>(0.1)};
    network.run();
    return 0;
}

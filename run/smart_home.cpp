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

#define DEV_NUM 300
#define FREQ    1

using round_s = sequence::periodic<
    distribution::interval_n<times_t, 0, FREQ>,
    distribution::weibull_n<times_t, FREQ*10, FREQ, 10>
>;

using rectangle_d = distribution::rect_n<1, 0, 0, 500, 500>;
constexpr size_t dim = 2;

DECLARE_OPTIONS(opt,
    parallel<true>,
    synchronised<false>,
    program<coordination::main>,
    round_schedule<round_s>,
    dimension<dim>,
    exports<vec<dim>, bool>,
    log_schedule<sequence::periodic_n<1, 0, 10>>,
    tuple_store<
        local_strong_monitor,   bool,
        local_weak_monitor,     bool,
        global_strong_monitor,  bool,
        global_weak_monitor,    bool,
        col,                    color,
        size,                   double
    >,
    spawn_schedule<sequence::multiple_n<DEV_NUM, 0>>,
    init<x, rectangle_d>,
    connector<connect::fixed<100>>,
    size_tag<size>,
    color_tag<col>
);

int main() {
    component::interactive_simulator<opt>::net network{common::make_tagged_tuple<epsilon>(0.1)};
    network.run();
    return 0;
}
// Copyright © 2020 Giorgio Audrito. All Rights Reserved.

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

constexpr int DEV_NUM=200;
constexpr int FREQ=1;

using round_s = sequence::periodic<
  distribution::interval_n<times_t, 0, FREQ>,
  distribution::weibull_n<times_t, FREQ*10, FREQ, 10>
  >;

using rectangle_d = distribution::rect_n<1, 0, 0, 500, 500>;
constexpr size_t dim = 2;

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

DECLARE_OPTIONS(opt,
		parallel<true>,
		synchronised<false>,
		program<coordination::main>,
		round_schedule<round_s>,
		dimension<dim>,
		exports<vec<dim>, double, bool, tuple<double,double>>,
		log_schedule<sequence::periodic_n<1, 0, 10>>,
		storage_t,
		aggregator_t,
		spawn_schedule<sequence::multiple_n<DEV_NUM, 0>>,
		init<x, rectangle_d>,
		connector<connect::fixed<100>>,
		size_tag<size>,
		color_tag<col>,
		plot_type<plotter_t>
		);

int main() {
  plotter_t p;
  std::cout << "/*\n";
  {
    component::interactive_simulator<opt>::net network{common::make_tagged_tuple<plotter>(&p)};
    network.run();
  }
  std::cout << "*/\n";
  std::cout << plot::file("crowd_safety", p.build());
  return 0;
}

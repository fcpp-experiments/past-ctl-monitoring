// Copyright © 2021 Giorgio Audrito. All Rights Reserved.

#include "lib/drones_recognition.hpp"


using namespace fcpp;
using namespace component::tags;
using namespace coordination::tags;


//! @brief Number of drones in the area.
constexpr size_t drones_num = 50;

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
using spawn_s = sequence::multiple_n<drones_num, 0>;

//! @brief Description of the initial position distribution.
using rectangle_d = distribution::rect_n<1, 0, 0, 0, 1000, 1000, 0>;

//! @brief Storage tags and types.
using storage_t = tuple_store<
    fail<handling_monitor<1>>,      bool,
    fail<redundancy_monitor<1>>,    bool,
    fail<handling_monitor<2>>,      bool,
    fail<redundancy_monitor<2>>,    bool,
    fail<handling_monitor<3>>,      bool,
    fail<redundancy_monitor<3>>,    bool,
    fail<handling_monitor<4>>,      bool,
    fail<redundancy_monitor<4>>,    bool,
    col,                            color,
    size,                           double
>;

//! @brief Storage tags to be logged with aggregators.
using aggregator_t = aggregators<
    fail<handling_monitor<1>>,      aggregator::mean<double>,
    fail<redundancy_monitor<1>>,    aggregator::mean<double>,
    fail<handling_monitor<2>>,      aggregator::mean<double>,
    fail<redundancy_monitor<2>>,    aggregator::mean<double>,
    fail<handling_monitor<3>>,      aggregator::mean<double>,
    fail<redundancy_monitor<3>>,    aggregator::mean<double>,
    fail<handling_monitor<4>>,      aggregator::mean<double>,
    fail<redundancy_monitor<4>>,    aggregator::mean<double>
>;

//! @brief Plot description.
using plotter_t = plot::plotter<aggregator_t, plot::time, fail>;

//! @brief Options list.
DECLARE_OPTIONS(opt,
    parallel<false>,
    synchronised<false>,
    dimension<dim>,
    program<coordination::main>,
    exports<coordination::main_t>,
    retain<metric::retain<2,1>>,
    connector<connect::hierarchical<connect::powered<750, 1, dim>>>,
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
        component::interactive_simulator<opt>::net network{common::make_tagged_tuple<plotter,name,texture>(&p,"Drones Recognition","land.jpg")};
        network.run();
    }
    std::cout << "*/\n";
    std::cout << plot::file("drones_recognition", p.build());
    return 0;
}

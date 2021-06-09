// Copyright © 2021 Giorgio Audrito. All Rights Reserved.

#include "lib/service_discovery.hpp"


using namespace fcpp;
using namespace component::tags;
using namespace coordination::tags;


//! @brief Number of edge, fog, cloud, and all nodes
constexpr size_t edge_num = 50;
constexpr size_t fog_num = 20;
constexpr size_t cloud_num = 5;
constexpr size_t node_num = edge_num + fog_num + cloud_num;

//! @brief Dimensionality of the space.
constexpr size_t dim = 3;

//! @brief Description of the round schedule.
using round_s = sequence::periodic<
    distribution::interval_n<times_t, 0, 1>,
    distribution::weibull_n<times_t, 10, 1, 10>
>;

//! @brief Description of the export schedule.
using export_s = sequence::periodic_n<1, 0, 1>;

//! @brief Description of the sequences of node creation events.
using edge_spawn_s = sequence::multiple_n<edge_num, 0>;
using fog_spawn_s = sequence::multiple_n<fog_num, 0>;
using cloud_spawn_s = sequence::multiple_n<cloud_num, 0>;

//! @brief Description of the initial position distribution (edge, fog, and cloud nodes).
using edge_circle_d = sequence::circle_n<1, 500, 500, 0, 0, 0, 300, edge_num>;
using fog_circle_d = sequence::circle_n<1, 500, 500, 0, 0, 0, 150, fog_num>;
using cloud_circle_d = sequence::circle_n<1, 500, 500, 0, 0, 0, 20, cloud_num>;


//! @brief Storage tags and types.
using storage_t = tuple_store<
    fail<response_time_monitor<1>>,      bool,
    fail<response_time_monitor<2>>,      bool,
    fail<response_time_monitor<3>>,      bool,
    fail<response_time_monitor<4>>,      bool,
    col,                            color,
    size,                           double
>;

//! @brief Storage tags to be logged with aggregators.
using aggregator_t = aggregators<
    fail<response_time_monitor<1>>,      aggregator::mean<double>,
    fail<response_time_monitor<2>>,      aggregator::mean<double>,
    fail<response_time_monitor<3>>,      aggregator::mean<double>,
    fail<response_time_monitor<4>>,      aggregator::mean<double>
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
    connector<connect::hierarchical<connect::powered<500, 1, 3>>>,
    round_schedule<round_s>,
    log_schedule<export_s>,
    spawn_schedule<edge_spawn_s>,
    init<x, edge_circle_d>,
    spawn_schedule<fog_spawn_s>,
    init<x,fog_circle_d>,
    spawn_schedule<cloud_spawn_s>,
    init<x,cloud_circle_d>,
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
        component::interactive_simulator<opt>::net network{common::make_tagged_tuple<plotter,name,texture>(&p,"Service discovery","land.jpg")};
        network.run();
    }
    std::cout << "*/\n";
    std::cout << plot::file("service_discovery", p.build());
    return 0;
}

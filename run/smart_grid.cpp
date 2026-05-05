// Copyright © 2026 Giordano Scarso, Giorgio Audrito. All Rights Reserved.

#include "lib/smart_grid.hpp"


using namespace fcpp;
using namespace component::tags;
using namespace coordination::tags;


//! @brief Number of edge nodes
constexpr size_t edge_num = 100;

//! @brief Dimensionality of the space.
constexpr size_t dim = 2;

//! @brief Final time for the plots.
constexpr size_t end_time = 150;


//! @brief Description of the round schedule.
using round_s = sequence::periodic<
    distribution::interval_n<times_t, 0, 1>,
    distribution::weibull_n<times_t, 10, 1, 100>,
    distribution::constant_n<times_t, 2*end_time>
>;

//! @brief Description of the export schedule.
using export_s = sequence::periodic_n<1, 0, 1, end_time>;

//! @brief Description of the sequences of node creation events.
//! @{
using edge_spawn_s  = sequence::multiple_n<edge_num,  0>;
//! @}

//! @brief Description of the initial position distributions.
//! @{
//using edge_circle_d  = sequence::circle_n<1, 500, 500, 0, 0, 0, 300, edge_num>;
using edge_circle_d  = sequence::grid_n<1, 0, 0, 500, 500, 10, 10>;
//! @}

//! @brief Description of the node shape distribution.
CONSTANT_DISTRIBUTION(shape_d, shape, shape::sphere);

//! @brief Storage tags and types.
using storage_t = tuple_store<
    fail<timeout_monitor<1>>,      bool,
    fail<timeout_monitor<2>>,      bool,
    fail<timeout_monitor<3>>,      bool,
    fail<timeout_monitor<4>>,      bool,
    fail<spurious_monitor>,        bool,
    fail<double_req_monitor>,      bool,
    status_c,                      color,
    shape,                         shape,
    size,                          double,
    curr_status,		   fcpp::coordination::sim_status
>;

//! @brief Storage tags to be logged with aggregators.
using aggregator_t = aggregators<
    fail<timeout_monitor<1>>,      aggregator::mean<double>,
    fail<timeout_monitor<2>>,      aggregator::mean<double>,
    fail<timeout_monitor<3>>,      aggregator::mean<double>,
    fail<timeout_monitor<4>>,      aggregator::mean<double>,
    fail<spurious_monitor>,        aggregator::mean<double>,
    fail<double_req_monitor>,      aggregator::mean<double>
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
    retain<metric::retain<1,1>>,
    connector<connect::fixed<COMM_RANGE, 1, dim>>,
    round_schedule<round_s>,
    log_schedule<export_s>,
    spawn_schedule<edge_spawn_s>,
    init<
	shape, shape_d, x, edge_circle_d,
	size, distribution::constant_n<double, 0>,
	network_rank, distribution::constant_n<int, 2>,
	send_power_ratio, distribution::constant_n<double, 8, 10>,
	recv_power_ratio, distribution::constant_n<double, 1>>,
    storage_t,
    aggregator_t,
    plot_type<plotter_t>,
    size_tag<size>,
    color_tag<status_c>,
    shape_tag<shape>
);

int main() {
    plotter_t p;
    std::cout << "/*\n";
    {
        component::interactive_simulator<opt>::net network{
		common::make_tagged_tuple<plotter,name>(&p,"Smart Grid")};
        network.run();
    }
    std::cout << "*/\n";
    std::cout << plot::file("smart_grid", p.build());
    return 0;
}

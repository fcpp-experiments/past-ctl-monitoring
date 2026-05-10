# minimum required version of CMake
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
# avoid building internal tests of the FCPP library
option(FCPP_INTERNAL_TESTS "Build internal tests for FCPP." OFF)
# load the FCPP sub-module
add_subdirectory(./fcpp/src)
# CMake macro setting up the FCPP library
fcpp_setup()

# project description
project(
    past_ctl_monitoring
    VERSION 0.0.0
    DESCRIPTION "Aggregate monitoring of Past-CTL properties."
)

# target declaration
fcpp_target(./run/crowd_safety.cpp        ON)
fcpp_target(./run/drones_recognition.cpp  ON)
fcpp_target(./run/service_discovery.cpp   ON)
fcpp_target(./run/smart_home.cpp          ON)
fcpp_target(./run/smart_grid.cpp          ON)

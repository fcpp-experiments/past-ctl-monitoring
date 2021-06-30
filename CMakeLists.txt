cmake_minimum_required(VERSION 3.9)
add_subdirectory(./fcpp/src)
fcpp_setup()

project(
    past_ctl_monitoring
    VERSION 0.0.0
    DESCRIPTION "Aggregate monitoring of Past-CTL properties."
)

fcpp_target(crowd_safety        ./run/crowd_safety.cpp        ON)
fcpp_target(drones_recognition  ./run/drones_recognition.cpp  ON)
fcpp_target(service_discovery   ./run/service_discovery.cpp   ON)
fcpp_target(smart_home          ./run/smart_home.cpp          ON)

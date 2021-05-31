cmake_minimum_required(VERSION 3.9)
add_subdirectory(./fcpp/src)
fcpp_setup()


project(crowd_safety
    VERSION 0.0.0
    DESCRIPTION "Crowd Safety Case Study."
)
fcpp_project(crowd_safety ./run/crowd_safety.cpp)


project(drones_recognition
    VERSION 0.0.0
    DESCRIPTION "Drones Recognition Case Study."
)
fcpp_project(drones_recognition ./run/drones_recognition.cpp)


project(service_discovery
    VERSION 0.0.0
    DESCRIPTION "Service Discovery Case Study."
)
fcpp_project(service_discovery ./run/service_discovery.cpp)


project(smart_home
    VERSION 0.0.0
    DESCRIPTION "Smart Home Case Study."
)
fcpp_project(smart_home ./run/smart_home.cpp)

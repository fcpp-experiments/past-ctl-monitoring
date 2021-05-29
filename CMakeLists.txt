# CMake 3.9 or newer
cmake_minimum_required(VERSION 3.9)

# Compiling options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
if(WIN32)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")
endif(WIN32)

# Adding fcpp
option(FCPP_BUILD_GL "Build OpenGL features." ON) # this tells CMake to compile fcpp's OpenGL features
add_subdirectory(./fcpp/src/)
target_compile_options(fcpp PUBLIC "-DFCPP_CONFIGURATION=FCPP_CONFIGURATION_DEPENDENT")

# CROWD SAFETY
project(service_discovery
  VERSION 0.1.0
  DESCRIPTION "Service Discovery Case Study."
  )
add_executable(service_discovery ./run/service_discovery.cpp)
set_target_properties(service_discovery PROPERTIES VERSION &{PROJECT_VERSION})
target_link_libraries(service_discovery PRIVATE fcpp)
target_include_directories(service_discovery PRIVATE ./)
copyGraphicsFolders(service_discovery $<TARGET_FILE_DIR:fcpp> $<TARGET_FILE_DIR:service_discovery>)
copyTextureFolder(service_discovery ${PROJECT_SOURCE_DIR} $<TARGET_FILE_DIR:service_discovery>)

# CROWD SAFETY
project(crowd_safety
    VERSION 0.1.0
    DESCRIPTION "Crowd Safety Case Study."
)
add_executable(crowd_safety ./run/crowd_safety.cpp)
set_target_properties(crowd_safety PROPERTIES VERSION &{PROJECT_VERSION})
target_link_libraries(crowd_safety PRIVATE fcpp)
target_include_directories(crowd_safety PRIVATE ./)
copyGraphicsFolders(crowd_safety $<TARGET_FILE_DIR:fcpp> $<TARGET_FILE_DIR:crowd_safety>)
copyTextureFolder(crowd_safety ${PROJECT_SOURCE_DIR} $<TARGET_FILE_DIR:crowd_safety>)


# DRONES RECOGNITION
project(drones_recognition
    VERSION 0.1.0
    DESCRIPTION "Drones Recognition Case Study."
)
add_executable(drones_recognition ./run/drones_recognition.cpp)
set_target_properties(drones_recognition PROPERTIES VERSION &{PROJECT_VERSION})
target_link_libraries(drones_recognition PRIVATE fcpp)
target_include_directories(drones_recognition PRIVATE ./)
copyGraphicsFolders(drones_recognition $<TARGET_FILE_DIR:fcpp> $<TARGET_FILE_DIR:drones_recognition>)
copyTextureFolder(drones_recognition ${PROJECT_SOURCE_DIR} $<TARGET_FILE_DIR:drones_recognition>)


# SMART HOME
project(smart_home
    VERSION 0.1.0
    DESCRIPTION "Smart Home Case Study."
)
add_executable(smart_home ./run/smart_home.cpp)
set_target_properties(smart_home PROPERTIES VERSION &{PROJECT_VERSION})
target_link_libraries(smart_home PRIVATE fcpp)
target_include_directories(smart_home PRIVATE ./)
copyGraphicsFolders(smart_home $<TARGET_FILE_DIR:fcpp> $<TARGET_FILE_DIR:smart_home>)
copyTextureFolder(smart_home ${PROJECT_SOURCE_DIR} $<TARGET_FILE_DIR:smart_home>)

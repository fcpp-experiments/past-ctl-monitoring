# CMake 3.9 or newer
cmake_minimum_required(VERSION 3.9)

# C++14 or higher
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# adding fcpp
if(MINGW)
    option(MINGW_STDTHREADS_GENERATE_STDHEADERS "" ON)
endif(MINGW)
add_subdirectory(./fcpp/src/)

include(GNUInstallDirs)


# project name, version and description
project(crowd_safety
    VERSION 0.1.0
    DESCRIPTION "Crowd Safety Case Study."
)

# executable target
add_executable(crowd_safety ./run/crowd_safety.cpp)

# VERSION property
set_target_properties(crowd_safety PROPERTIES VERSION &{PROJECT_VERSION})

# include directories
target_include_directories(crowd_safety PRIVATE ./
                                                ./fcpp/src/
                                                ./fcpp/src/external/
                                                ./fcpp/src/external/glad-core-3.3/include/
                                                ./fcpp/src/external/glm-0.9.9.8/glm
                                                ./fcpp/src/external/glfw-3.3.2/include/
                                                ./fcpp/src/external/freetype-2.10.4/devel/)

# link libraries
target_link_libraries(crowd_safety PRIVATE fcpp
                                           glm
                                           glfw
                                           stb_image
                                           freetype)

#copying shaders into build
add_custom_command(TARGET crowd_safety PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/fcpp/src/lib/graphics/shaders/ $<TARGET_FILE_DIR:crowd_safety>/shaders/)

#copying fonts into build
add_custom_command(TARGET crowd_safety PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/fcpp/src/lib/graphics/fonts/ $<TARGET_FILE_DIR:crowd_safety>/fonts/)

#target compile options
target_compile_options(crowd_safety PUBLIC "-DFCPP_CONFIGURATION=FCPP_CONFIGURATION_DEPENDENT")

# defining install rules
install(TARGETS crowd_safety
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)


# project name, version and description
project(drones_recognition
    VERSION 0.1.0
    DESCRIPTION "Drones Recognition Case Study."
)

# executable target
add_executable(drones_recognition ./run/drones_recognition.cpp)

# VERSION property
set_target_properties(drones_recognition PROPERTIES VERSION &{PROJECT_VERSION})

# include directories
target_include_directories(drones_recognition PRIVATE ./
                                                      ./fcpp/src/
                                                      ./fcpp/src/external/
                                                      ./fcpp/src/external/glad-core-3.3/include/
                                                      ./fcpp/src/external/glm-0.9.9.8/glm
                                                      ./fcpp/src/external/glfw-3.3.2/include/
                                                      ./fcpp/src/external/freetype-2.10.4/devel/)

# link libraries
target_link_libraries(drones_recognition PRIVATE fcpp
                                                 glm
                                                 glfw
                                                 stb_image
                                                 freetype)

#copying shaders into build
add_custom_command(TARGET drones_recognition PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/fcpp/src/lib/graphics/shaders/ $<TARGET_FILE_DIR:drones_recognition>/shaders/)

#copying fonts into build
add_custom_command(TARGET drones_recognition PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/fcpp/src/lib/graphics/fonts/ $<TARGET_FILE_DIR:drones_recognition>/fonts/)

#target compile options
target_compile_options(drones_recognition PUBLIC "-DFCPP_CONFIGURATION=FCPP_CONFIGURATION_DEPENDENT")

# defining install rules
install(TARGETS drones_recognition
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)


# project name, version and description
project(smart_home
    VERSION 0.1.0
    DESCRIPTION "Smart Home Case Study."
)

# executable target
add_executable(smart_home ./run/smart_home.cpp)

# VERSION property
set_target_properties(smart_home PROPERTIES VERSION &{PROJECT_VERSION})

# include directories
target_include_directories(smart_home PRIVATE ./
                                          ./fcpp/src/
                                          ./fcpp/src/external/
                                          ./fcpp/src/external/glad-core-3.3/include/
                                          ./fcpp/src/external/glm-0.9.9.8/glm
                                          ./fcpp/src/external/glfw-3.3.2/include/
                                          ./fcpp/src/external/freetype-2.10.4/devel/)

# link libraries
target_link_libraries(smart_home PRIVATE fcpp
                                         glm
                                         glfw
                                         stb_image
                                         freetype)

#copying shaders into build
add_custom_command(TARGET smart_home PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/fcpp/src/lib/graphics/shaders/ $<TARGET_FILE_DIR:smart_home>/shaders/)

#copying fonts into build
add_custom_command(TARGET smart_home PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/fcpp/src/lib/graphics/fonts/ $<TARGET_FILE_DIR:smart_home>/fonts/)

#target compile options
target_compile_options(smart_home PUBLIC "-DFCPP_CONFIGURATION=FCPP_CONFIGURATION_DEPENDENT")

# defining install rules
install(TARGETS smart_home
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

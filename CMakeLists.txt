# CMake 3.9 or newer
cmake_minimum_required(VERSION 3.9)

# C++14 or higher
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs)

# adding fcpp
add_subdirectory(./fcpp/src/)

# adding headers
add_library(past_ctl SHARED
    lib/crowd_safety.cpp
    lib/drones_recognition.cpp
    lib/logic_samples.cpp
    lib/past_ctl.cpp
    lib/smart_home.cpp
)
target_include_directories(past_ctl PRIVATE ./ ./fcpp/src/)

# project name, version and description
project(fcppGL
	VERSION 0.1.0
	DESCRIPTION "FieldCalc++ OpenGL simulator."
)

# executable target
add_executable(fcppGL ./run/displayer.cpp)

# VERSION property
set_target_properties(fcppGL PROPERTIES VERSION &{PROJECT_VERSION})

# include directories
target_include_directories(fcppGL PRIVATE ./
                                          ./fcpp/src/
                                          ./fcpp/src/external/
                                          ./fcpp/src/external/glad-core-3.3/include/
                                          ./fcpp/src/external/glm-0.9.9.8/glm
                                          ./fcpp/src/external/glfw-3.3.2/include/
                                          ./fcpp/src/external/freetype-2.10.4/devel/)

# link libraries
target_link_libraries(fcppGL PRIVATE fcpp
                                     past_ctl
                                     glm
									 glfw
									 stb_image
									 freetype)

#copying shaders into build
add_custom_command(TARGET fcppGL PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/fcpp/src/lib/graphics/shaders/ $<TARGET_FILE_DIR:fcppGL>/shaders/)

#copying fonts into build
add_custom_command(TARGET fcppGL PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/fcpp/src/lib/graphics/fonts/ $<TARGET_FILE_DIR:fcppGL>/fonts/)

#target compile options
target_compile_options(fcppGL PUBLIC "-DFCPP_CONFIGURATION=FCPP_CONFIGURATION_DEPENDENT")

# MinGW support to C++ threads
if(MINGW)
    target_include_directories(fcppGL PRIVATE ./fcpp/src/external/mingw-std-threads-master/)
    target_link_libraries(fcppGL PRIVATE mingw_stdthreads)
    option(MINGW_STDTHREADS_GENERATE_STDHEADERS "" ON)
endif(MINGW)

# defining install rules
install(TARGETS fcppGL
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
                                     past_ctl
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

# MinGW support to C++ threads
if(MINGW)
    target_include_directories(smart_home PRIVATE ./fcpp/src/external/mingw-std-threads-master/)
    target_link_libraries(smart_home PRIVATE mingw_stdthreads)
    option(MINGW_STDTHREADS_GENERATE_STDHEADERS "" ON)
endif(MINGW)

# defining install rules
install(TARGETS smart_home
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

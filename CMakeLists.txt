cmake_minimum_required(VERSION 3.10.2)

project(simulation_quadruped)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(required_components utils-urdf gui-osg)
set(required_libraries dart dart-utils-urdf dart-gui-osg)

include_directories(include)

find_package(quadruped_control_library REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(DART 6.12.2 REQUIRED COMPONENTS ${required_components} CONFIG)

file(GLOB_RECURSE source_files "src/*.cpp")
add_executable(dart_simulation ${source_files})
target_link_libraries(dart_simulation PUBLIC ${required_libraries} Eigen3::Eigen)
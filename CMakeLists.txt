cmake_minimum_required(VERSION 3.10.2)

project(simulation_quadruped)


set(required_components utils-urdf gui)
set(required_libraries dart dart-utils-urdf dart-gui)

include_directories(include)

find_package(Eigen3 REQUIRED)
find_package(DART 6.12.2 REQUIRED COMPONENTS ${required_components} CONFIG)


add_executable(dart_simulation src/dart_simulation.cpp)
target_link_libraries(dart_simulation PUBLIC ${required_libraries} Eigen3::Eigen)
project(HabiRobot)
cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_STANDARD 14)

include_directories(./include)

# only support linux
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

aux_source_directory(./source SRC_LIST)

add_executable(HabiRobot ${SRC_LIST})
target_link_libraries(HabiRobot wt)
target_link_libraries(HabiRobot wthttp)
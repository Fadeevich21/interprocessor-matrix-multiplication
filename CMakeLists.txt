cmake_minimum_required(VERSION 3.10)
project(master C)
project(worker C)

set(CMAKE_C_STANDART 11)

add_executable(master master.c)
add_executable(worker worker.c)

add_subdirectory(libs)
target_link_libraries(master array)
target_link_libraries(master matrix)
target_link_libraries(master color_print)
target_link_libraries(master messages_to_console)
target_link_libraries(master message)

target_link_libraries(worker array)
target_link_libraries(worker matrix)
target_link_libraries(worker color_print)
target_link_libraries(worker messages_to_console)
target_link_libraries(worker message)
cmake_minimum_required(VERSION 3.25)
project(RX_control)

set(CMAKE_CXX_STANDARD 17)

add_executable(RX_control main.cpp Commands/Broadcast_packet_structure.h Commands/Commands.h Commands/Comands.cpp TCP/TCP.h TCP/TCP.cpp UDP/UDP.cpp UDP/UDP.h)

target_link_libraries(RX_control wsock32 ws2_32)


# Set the name and the supported language of the project
project(pixel_pusher)

# Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11" )

include_directories(
  .
)

add_library(pixel_pusher 
 device_header.cpp pixel_pusher.cpp strip.cpp pixel.cpp)

add_executable(pixel_pusher_listener pixel_pusher_listener.cpp)

target_link_libraries(pixel_pusher_listener pixel_pusher )

add_executable(pixel_pusher_sender pixel_pusher_sender.cpp)

target_link_libraries(pixel_pusher_sender pixel_pusher )
cmake_minimum_required(VERSION 3.10)
project(mini_gimp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} include)

file(GLOB SRC
  src/*.cpp
  src/filters/*.cpp
)

add_executable(mini-gimp ${SRC})
target_link_libraries(mini-gimp ${OpenCV_LIBS})

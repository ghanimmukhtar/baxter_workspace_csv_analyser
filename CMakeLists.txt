cmake_minimum_required(VERSION 2.8.3)
project(csv_custom_reader)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES csv_custom_reader
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

# EIGEN
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

find_package(Boost REQUIRED COMPONENTS system )

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(csv_custom_reader src/csv_custom_reader.cpp)
target_link_libraries(csv_custom_reader ${catkin_LIBRARIES})

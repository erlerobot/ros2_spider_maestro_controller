cmake_minimum_required(VERSION 2.8.3)
project(spider_maestro_controller)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
endif()

#anita
set(ROS_BUILD_TYPE Debug)
#anita

##############
## Packages ##
##############
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
#find_package(ament REQUIRED COMPONENTS
#  roscpp
#  rospy 
#  std_msgs
#)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rmw REQUIRED)#ROS Middleware (rmw) Interface
find_package(rmw_implementation REQUIRED)#CMake infrastructure and dependencies for rmw implementations


## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


###################################
## ament specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
#catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES maestro_controller
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
#)

if(AMENT_ENABLE_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

set(target_dependencies
  "rclcpp"
  "std_msgs"
  )

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
#include_directories(
#  ${catkin_INCLUDE_DIRS}
#)

#add_library(polstro src/PolstroSerialInterface.cpp src/PolstroSerialInterfacePOSIX.cpp)
#target_link_libraries(polstro ${catkin_LIBRARIES})

#add_executable(controller_sub src/controller_sub.cpp)
#target_link_libraries(controller_sub polstro ${catkin_LIBRARIES})

#install(
#	TARGETS controller_sub
#	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#	RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#)

#add_library(polstro 
#	src/PolstroSerialInterface.cpp 
#	src/PolstroSerialInterfacePOSIX.cpp	 
#	TARGET_DEPENDENCIES ${target_dependencies} INSTALL)

add_library(polstro src/PolstroSerialInterface.cpp src/PolstroSerialInterfacePOSIX.cpp)
target_link_libraries(polstro ${ament_LIBRARIES})

add_executable_for_each_rmw_implementations(controller_sub 
	src/controller_sub.cpp
	TARGET_DEPENDENCIES ${target_dependencies} INSTALL)


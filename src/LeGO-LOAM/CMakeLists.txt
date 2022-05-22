cmake_minimum_required(VERSION 2.8.3)
project(lego_loam)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

include(${PROJECT_SOURCE_DIR}/cmake/find_dependencies.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/sys_arch.cmake)

find_package(catkin REQUIRED COMPONENTS
  tf
  roscpp
  rospy
  cv_bridge
  image_transport
  pcl_ros
  pcl_conversions
  std_msgs
  sensor_msgs
  geometry_msgs
  nav_msgs
  cloud_msgs
)

find_package(GTSAM REQUIRED QUIET)
find_package(PCL REQUIRED QUIET)
find_package(OpenCV REQUIRED QUIET)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS cloud_msgs
  DEPENDS PCL
)

set_dependencies_dir(${CMAKE_CURRENT_LIST_DIR}/3rdparty)
find_dependency_package(log)

include_directories(
	include
	${catkin_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
	${GTSAM_INCLUDE_DIR}
)

link_directories(
	include
	${OpenCV_LIBRARY_DIRS}
	${PCL_LIBRARY_DIRS}
	${GTSAM_LIBRARY_DIRS}
)

# 将源码编译成库
# set(UTILS_SRC ${CMAKE_CURRENT_LIST_DIR}/src/log.cpp)
# add_library(log SHARED ${UTILS_SRC})
# target_link_libraries(log)

add_executable(imageProjection src/imageProjection.cpp)
add_dependencies(imageProjection ${catkin_EXPORTED_TARGETS} cloud_msgs_gencpp)
target_link_libraries(imageProjection ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} log)

add_executable(featureAssociation src/featureAssociation.cpp )
add_dependencies(featureAssociation ${catkin_EXPORTED_TARGETS} cloud_msgs_gencpp)
target_link_libraries(featureAssociation ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} log)

add_executable(mapOptmization src/mapOptmization.cpp)
target_link_libraries(mapOptmization ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} gtsam log)

add_executable(transformFusion src/transformFusion.cpp ${UTILS_SRC})
target_link_libraries(transformFusion ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} log)
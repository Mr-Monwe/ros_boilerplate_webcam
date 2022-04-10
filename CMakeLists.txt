cmake_minimum_required(VERSION 3.0.2)
add_compile_options(-std=c++11)
project(ros_boilerplate_webcam)
find_package(catkin REQUIRED COMPONENTS
  rospy
  roscpp
  std_msgs
  cv_bridge
  sensor_msgs 
  image_transport 
)

find_package(OpenCV REQUIRED)
  
catkin_package(
  LIBRARIES ros_boilerplate_webcam
  CATKIN_DEPENDS 
  rospy 
  roscpp 
  std_msgs
  cv_bridge 
  sensor_msgs 
  image_transport
) 

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(camera_publisher src/camera_publisher.cpp)
target_link_libraries(
  camera_publisher 
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
)

add_executable(camera_subscriber src/camera_subscriber.cpp)
target_link_libraries(
  camera_subscriber 
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
)
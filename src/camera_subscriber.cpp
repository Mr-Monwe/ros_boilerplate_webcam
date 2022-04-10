#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <opencv2/highgui/highgui.hpp>

void imgCallback(const sensor_msgs::Image::ConstPtr &msg) {
  try {
    cv::imshow("Image", cv_bridge::toCvShare(msg, "bgr8")->image);
    cv::waitKey(1);
  } catch (cv_bridge::Exception &e) {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "camera_subscriber");  // Node initialization
  ros::NodeHandle n;                           // Nodehandler
  ros::Subscriber subLeftImg =
      n.subscribe("camera/image", 10, imgCallback);  // Subscriber
  ros::spin();                                       // Node execution
  return 0;
}
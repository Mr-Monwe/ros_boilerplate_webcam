#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <ros/ros.h>

#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv) {
  ros::init(argc, argv, "camera_publisher");  // Node initialization
  ros::NodeHandle nh;                         // Nodehandler
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub =
      it.advertise("camera/image", 10);  // Publisher
  int video_source = 0;                 // Camera index
  cv::VideoCapture cap(video_source);   // Video Capture object
  if (!cap.isOpened()) {  // Check if video can be opened with the index
    return 1;
  }
  cv::Mat frame;
  sensor_msgs::ImagePtr msg;
  ros::Rate loop_rate(1);
  while (nh.ok()) {
    cap >> frame;
    // Check if grabbed frame is actually full with some content
    if (!frame.empty()) {
      msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
      pub.publish(msg);
      cv::waitKey(1);
    }
    ros::spinOnce();
    loop_rate.sleep();
  }
}
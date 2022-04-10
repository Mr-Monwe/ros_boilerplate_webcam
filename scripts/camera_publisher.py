#!/usr/bin/env python
"""
Simple Camera publisher
"""
import cv2
import rospy
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import Image
bridge = CvBridge()


def pub():
    rospy.init_node('image_listener')
    image_pub = rospy.Publisher("camera/image", Image, queue_size=10)
    cam_obj = cv2.VideoCapture(0)

    while(True):
        ret, frame = cam_obj.read()
        try:
            image_pub.publish(bridge.cv2_to_imgmsg(frame, "bgr8"))
        except CvBridgeError as e:
            print(e)
        cv2.waitKey(1)


def main():
    try:
        while not rospy.is_shutdown():
            pub()
    except rospy.ROSInterruptException:
        pass


if __name__ == "__main__":
    main()

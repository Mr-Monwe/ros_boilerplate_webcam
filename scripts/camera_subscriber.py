#!/usr/bin/env python
"""
Simple Camera subscriber
"""
import cv2
import rospy
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import Image
bridge = CvBridge()


def imgCallback(img):
    try:
        img = bridge.imgmsg_to_cv2(img, "bgr8")
    except CvBridgeError as e:
        print(e)
    else:
        cv2.imshow('Image', img)
        cv2.waitKey(1)


def main():
    rospy.init_node('image_listener')
    rospy.Subscriber("camera/image", Image, imgCallback)
    rospy.spin()


if __name__ == "__main__":
    main()

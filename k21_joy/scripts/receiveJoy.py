#!/usr/bin/env python3
from numpy import rate
import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy

def callback(data):
	twist = Twist()
	# kiri kanan
	twist.linear.x = -(data.axes[0])
	# depan belakang
	twist.linear.y = data.axes[1]
	# angular kiri
	twist.angular.x = data.buttons[7]
	# angular kanan
	twist.angular.y = data.buttons[6]
	pub.publish(twist)

def start():
	global pub, rate
	pub = rospy.Publisher('/cmd_vel', Twist, queue_size=5)
	rospy.Subscriber("/joy", Joy, callback)
	rospy.init_node('k21_recieve_joy', anonymous = False)
	rospy.spin()

if __name__ == '__main__':
	try:
		start()
	except rospy.ROSInterruptException:
		pass
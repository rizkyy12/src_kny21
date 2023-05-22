#!/usr/bin/env python3

import rospy

from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy

from std_msgs.msg import Int64
from std_srvs.srv import SetBool

BASE_MAX_LIN_VEL = 140
BASE_MAX_ANG_VEL = 120
LIN_VEL_STEP_SIZE = 0.1
ANG_VEL_STEP_SIZE = 0.1

class K21_Teleop_Joy:
    
    def __init__(self):
        # self.counter = 0
        self.pub = rospy.Publisher("/cmd_vel", Twist, queue_size=10)
        self.joy_sub = rospy.Subscriber("/joy", Joy, self.joy_Cb)
        # self.reset_service = rospy.Service("/reset_counter", SetBool, self.callback_reset_counter)

    # def vels(target_linear_vel, target_angular_vel):
    #     return "currently:\tlinear vel %s\t angular vel %s " % (target_linear_vel,target_angular_vel)
    
    # def makeSimpleProfile(output, input, slop):
    #     if input > output:
    #         output = min(input, output + slop )
    #     elif input < output:
    #         output = max(input, output - slop )
    #     else:
    #         output = input

    #     return output

    # def constrain(input, low, high):
    #     if input < low:
    #         input = low
    #     elif input > high:
    #         input = high
    #     else:
    #         input = input

    #     return input

    # def checkLinearLimitVelocity(vel):
    #     vel = constrain(vel, -BASE_MAX_LIN_VEL, BASE_MAX_LIN_VEL)

    #     return vel

    # def checkAngularLimitVelocity(vel):
    #     vel = constrain(vel, -BASE_MAX_ANG_VEL, BASE_MAX_ANG_VEL)

    #     return vel

    def joy_Cb(self, msg):
        print ("New message received")

        twist = Twist()

        # self.axis_7 = msg.axes[7]
        
        # if self.axis_7 == 1:
        #     twist.linear.y == 1
        # elif self.axis_7 == -1:
        #     twist.linear.y == -1
        twist.linear.y == msg.axes[7]
        twist.linear.x == -(msg.axes[6])
        
        self.pub.publish(twist)
        # self.counter += msg.data
        # new_msg = Int64()
        # new_msg.data = self.counter
        # self.pub.publish(new_msg)


if __name__ == '__main__':
    rospy.init_node('k21_teleop_joy')
    K21_Teleop_Joy()
    rospy.spin()
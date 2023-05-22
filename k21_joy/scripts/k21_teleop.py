#!/usr/bin/env python3

from logging.handlers import BufferingHandler
import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy
import sys, select, os
if os.name == 'nt':
  import msvcrt, time
else:
  import tty, termios

BASE_MAX_LIN_VEL = 140
BASE_MAX_ANG_VEL = 120

# WAFFLE_MAX_LIN_VEL = 0.26
# WAFFLE_MAX_ANG_VEL = 1.82

LIN_VEL_STEP_SIZE = 0.1
ANG_VEL_STEP_SIZE = 0.1

pub = rospy.Publisher('cmd_vel', Twist, queue_size=10)

def vels(target_linear_vel, target_angular_vel):
    return "currently:\tlinear vel %s\t angular vel %s " % (target_linear_vel,target_angular_vel)

def makeSimpleProfile(output, input, slop):
    if input > output:
        output = min(input, output + slop )
    elif input < output:
        output = max(input, output - slop )
    else:
        output = input

    return output

def constrain(input, low, high):
    if input < low:
      input = low
    elif input > high:
      input = high
    else:
      input = input

    return input

def checkLinearLimitVelocity(vel):
    # if turtlebot3_model == "burger":
    #   vel = constrain(vel, -BURGER_MAX_LIN_VEL, BURGER_MAX_LIN_VEL)
    # elif turtlebot3_model == "waffle" or turtlebot3_model == "waffle_pi":
    #   vel = constrain(vel, -WAFFLE_MAX_LIN_VEL, WAFFLE_MAX_LIN_VEL)
    # else:
    #   vel = constrain(vel, -BURGER_MAX_LIN_VEL, BURGER_MAX_LIN_VEL)
    vel = constrain(vel, -BASE_MAX_LIN_VEL, BASE_MAX_LIN_VEL)

    return vel

def checkAngularLimitVelocity(vel):
    vel = constrain(vel, -BASE_MAX_ANG_VEL, BASE_MAX_ANG_VEL)
    return vel

def joy_Cb(msg):
    print ("New message received")
    global started, last_data
    last_data = msg
    if (not started):
        started = True
    # status = 0
    # target_linear_vel   = 0.0
    # target_angular_vel  = 0.0
    # control_linear_vel  = 0.0
    # control_angular_vel = 0.0

    # try:
    #   while not rospy.is_shutdown():

    #     if msg.axes[6]  == 1:
    #       target_linear_vel = checkLinearLimitVelocity(target_linear_vel + LIN_VEL_STEP_SIZE)
    #       status = status + 1
    #       print(vels(target_linear_vel,target_angular_vel))
        
    #     else:
    #       print("error")
        
    #     twist = Twist()

    #     control_linear_vel = makeSimpleProfile(control_linear_vel, target_linear_vel, (LIN_VEL_STEP_SIZE/2.0))
    #     twist.linear.x = control_linear_vel; twist.linear.y = 0.0; twist.linear.z = 0.0

    #     control_angular_vel = makeSimpleProfile(control_angular_vel, target_angular_vel, (ANG_VEL_STEP_SIZE/2.0))
    #     twist.angular.x = 0.0; twist.angular.y = 0.0; twist.angular.z = control_angular_vel

    #     pub.publish(twist)
    
    # except:
    #   print("error")
    
    # finally:
    #   twist = Twist()
    #   twist.linear.x = 0.0; twist.linear.y = 0.0; twist.linear.z = 0.0
    #   twist.angular.x = 0.0; twist.angular.y = 0.0; twist.angular.z = 0.0
    #   pub.publish(twist)

def teleop_control():
  rospy.init_node('k21_teleop_joy')
  rospy.Subscriber('joy', Joy, joy_Cb, queue_size=1)

if __name__ == '__main__':
    try:
        teleop_control()
    except rospy.ROSInterruptException:
        pass

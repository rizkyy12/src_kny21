#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

class K21JoyNode{
    private:
        ros::Subscriber joy;
        ros::Publisher vel_pub;
    public:
        K21JoyNode(ros::NodeHandle *nh){
            vel_pub = nh->advertise<geometry_msgs::Twist>("/k21/cmd_vel", 10);
            joy = nh->subscribe("/joy", 10, &K21JoyNode::joyCb, this);
        }
        void joyCb(const sensor_msgs::Joy::ConstPtr& joy){
            geometry_msgs::Twist twist;
            
            twist.linear.x = -1*joy->axes[0];
            twist.linear.y = 1*joy->axes[1];
            twist.angular.z = -1*joy->axes[2];
            vel_pub.publish(twist);
        }
};

int main(int argc, char** argv){
    ros::init(argc, argv, "k21_joy");
    ros::NodeHandle nh;
    K21JoyNode k21_joynode = K21JoyNode(&nh);
    ros::spin();
    return 0;
}
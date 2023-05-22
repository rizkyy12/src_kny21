#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Pose2D.h"
#include "std_msgs/Int32.h"

class K21Lifter{
    private:
        ros::Subscriber joy_lifter;
        ros::Publisher lifter_pub;

    public:
        
        K21Lifter(ros::NodeHandle *nh){
            lifter_pub = nh->advertise<std_msgs::Int32>("/lifter", 10);
            joy_lifter = nh->subscribe("/joy", 10, &K21Lifter::lifterCb, this);
        }

    void lifterCb(const sensor_msgs::Joy& msg){
        std_msgs::Int32 lifter;
        
        if (msg.buttons[5] == 1){
            lifter.data = 1;
        }
        else if (msg.buttons[4] == 1){
            lifter.data = 2;
        }
        else{
            lifter.data = 0;
        }
        lifter_pub.publish(lifter);
    }

};



int main(int argc, char **argv)
{
    // ROS_INFO("init Node");
    ros::init(argc, argv, "k21_lifter");
    ros::NodeHandle nh;
    K21Lifter K21_Lifter = K21Lifter(&nh);
    ros::spin();
}

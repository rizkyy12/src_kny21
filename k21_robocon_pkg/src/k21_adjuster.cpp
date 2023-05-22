#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/Int32.h"

class K21Adjust{
    private:
        ros::Subscriber joy;
        ros::Publisher adjuster_pub;

    public:
        int i = 0;
        K21Adjust(ros::NodeHandle *nh){
            adjuster_pub = nh->advertise<std_msgs::Int32>("/adjuster_pelontar", 10);
            joy = nh->subscribe("/joy", 10, &K21Adjust::adjustCb, this);
        }

    void adjustCb(const sensor_msgs::Joy& msg){
        ros::Rate rate(10);
        std_msgs::Int32 degree;
        
        if (msg.buttons[11] == 1){
            degree.data = 1;

        }
        else if (msg.buttons[10] == 1){
            degree.data = -1;
        }
        adjuster_pub.publish(degree);
        rate.sleep();
    }
};



int main(int argc, char **argv)
{
    // ROS_INFO("init Node");
    ros::init(argc, argv, "k21_adjuster");
    ros::NodeHandle nh;
    K21Adjust K21_Adjust = K21Adjust(&nh);
    ros::spin();
}

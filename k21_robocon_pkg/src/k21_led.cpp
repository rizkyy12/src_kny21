#include "ros/ros.h"
#include "std_msgs/Int32.h"

int main(int argc, char **argv){
    ros::init(argc, argv, "k21_led");

    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::Int32>("/led1", 1000);
    ros::Rate loop_rate(0.5);

     while(ros::ok()){
        std_msgs::Int32 msg;
        

        if (ros::isShuttingDown){
            msg.data = 1;
            ROS_INFO("Raspberry ON");
        }
        else {
            msg.data = 0;
            ROS_INFO("Raspberry OFF");
        }

        pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();    
    }
}


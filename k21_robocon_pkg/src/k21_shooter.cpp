#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Pose2D.h"
#include "std_msgs/Int32.h"

class K21Shooter{
    private:
        ros::Subscriber joy_shooter;
        ros::Subscriber joy_feeder;
        ros::Publisher shooter_pub;
        ros::Publisher feeder_pub;

    public:
        
        K21Shooter(ros::NodeHandle *nh){
            shooter_pub = nh->advertise<std_msgs::Int32>("/shooter", 10);
            feeder_pub = nh->advertise<std_msgs::Int32>("/feeder", 10);
            joy_shooter = nh->subscribe("/joy", 10, &K21Shooter::lifterCb, this);
            joy_feeder = nh->subscribe("/joy", 10, &K21Shooter::feederCb, this);
        }

    void lifterCb(const sensor_msgs::Joy& msg){
        std_msgs::Int32 shooter;
        
        if (msg.buttons[2] == 1){
            shooter.data = 1;
        }
        else{
            shooter.data = 0;
        }
        shooter_pub.publish(shooter);

    
    }
    void feederCb(const sensor_msgs::Joy& msg){
        std_msgs::Int32 feeder;

        if (msg.buttons[3] == 1){
            feeder.data = 1;
        }
        else{
            feeder.data = 0;
        }
        feeder_pub.publish(feeder);
    }

};



int main(int argc, char **argv)
{
    // ROS_INFO("init Node");
    ros::init(argc, argv, "k21_shooter");
    ros::NodeHandle nh;
    K21Shooter K21_Shooter = K21Shooter(&nh);
    ros::spin();
}

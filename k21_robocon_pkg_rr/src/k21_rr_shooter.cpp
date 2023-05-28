#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Pose2D.h"
#include "std_msgs/Int32.h"

class K21Shooter{
    private:
        ros::Subscriber joy_shooter;
        ros::Publisher shooter_pub;

    public:
        
        K21Shooter(ros::NodeHandle *nh){
            shooter_pub = nh->advertise<std_msgs::Int32>("/shooter_rr", 10);
            joy_shooter = nh->subscribe("/joy", 10, &K21Shooter::shooterCb, this);
        }

    void shooterCb(const sensor_msgs::Joy& msg){
        std_msgs::Int32 shooter;
        
        if (msg.buttons[2] == 1){
            shooter.data = 1;
        }
        else{
            shooter.data = 0;
        }
        shooter_pub.publish(shooter);
    }

};



int main(int argc, char **argv)
{
    // ROS_INFO("init Node");
    ros::init(argc, argv, "k21_rr_shooter");
    ros::NodeHandle nh;
    K21Shooter K21_Shooter = K21Shooter(&nh);
    ros::spin();
}

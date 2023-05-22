#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int64.h>

double Vx, Vy, w;

class K21BaseNode{
    private:
        ros::Subscriber cmd_vel;
        ros::Publisher vel_m1;
        ros::Publisher vel_m2;
        ros::Publisher vel_m3;
        ros::Publisher vel_m4;
    public:
        K21BaseNode(ros::NodeHandle *nh){
            cmd_vel = nh->subscribe("/k21/cmd_vel", 10, &K21BaseNode::BaseCb, this);
            vel_m1 = nh->advertise<std_msgs::Int64>("/k21/vel_m1", 10);
            vel_m2 = nh->advertise<std_msgs::Int64>("/k21/vel_m2", 10);
            vel_m3 = nh->advertise<std_msgs::Int64>("/k21/vel_m3", 10);
            vel_m4 = nh->advertise<std_msgs::Int64>("/k21/vel_m4", 10);
        }
        void BaseCb(const geometry_msgs::Twist::ConstPtr& vel){
            std_msgs::Int64 m1;
            std_msgs::Int64 m2;
            std_msgs::Int64 m3;
            std_msgs::Int64 m4;
            
            Vy = vel->linear.y;
            Vx = vel->linear.x;
            w = vel->angular.z;

            if (Vy == 1){
                // for (int i = 0; i < Vy; i++){
                //     m1.data = -i;
                //     m2.data = i;
                //     m3.data = i;
                //     m4.data = -i;
                //     vel_m1.publish(m1);
                // }
                m1.data = 10;
                m2.data = 10;
                m3.data = 10;
                m4.data = -10;
            }
            else{
                m1.data = 0;
                m2.data = 0;
                m3.data = 0;
                m4.data = 0;
            }

            vel_m1.publish(m1);
            vel_m2.publish(m2);
            vel_m3.publish(m3);
            vel_m4.publish(m4);

            
            // twist.linear.x = -1*joy->axes[6];
            // twist.linear.y = 1*joy->axes[7];
            // twist.angular.z = -1*joy->axes[3];
            // vel_pub.publish(twist);
        }
};

int main(int argc, char** argv){
    ros::init(argc, argv, "k21_base");
    ros::NodeHandle nh;
    K21BaseNode k21_basenode = K21BaseNode(&nh);
    ros::spin();
    return 0;
}
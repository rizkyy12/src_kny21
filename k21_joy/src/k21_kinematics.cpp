#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>

class K21Kinematics{
    private:
        ros::Subscriber cmd_vel;
        ros::Publisher vel_m1;
        ros::Publisher vel_m2;
        ros::Publisher vel_m3;
        ros::Publisher vel_m4;
    public:
        int Vx_joy, Vy_joy, w_joy;
        int Vx, Vy, w;
        float m1, m2, m3, m4;
        float rpm_m1, rpm_m2, rpm_m3, rpm_m4; 
        int dir1, dir2, dir3, dir4;
        
        K21Kinematics(ros::NodeHandle *nh){
            vel_m1 = nh->advertise<geometry_msgs::Pose2D>("/k21/vel_m1", 10);
            vel_m2 = nh->advertise<geometry_msgs::Pose2D>("/k21/vel_m2", 10);
            vel_m3 = nh->advertise<geometry_msgs::Pose2D>("/k21/vel_m3", 10);
            vel_m4 = nh->advertise<geometry_msgs::Pose2D>("/k21/vel_m4", 10);
            cmd_vel = nh->subscribe("/k21/cmd_vel", 10, &K21Kinematics::speedCB, this);
        }
        void speedCB(const geometry_msgs::Twist::ConstPtr& msg){
            // geometry_msgs::Twist twist;

            Vx_joy = msg->linear.x;
            Vy_joy = msg->linear.y;
            w_joy = msg->angular.z;

            geometry_msgs::Pose2D m_1;
            geometry_msgs::Pose2D m_2;
            geometry_msgs::Pose2D m_3;
            geometry_msgs::Pose2D m_4;
            
            // Rotate W
            if (w_joy == -1){
                Vx = 0;
                Vy = 0;
                w = 20;
            }
            else if (w_joy == 1){
                Vx = 0;
                Vy = 0;
                w = -20;
            }

            //Gerak Y
            else if (Vy_joy == 1){
                Vx = 0;
                Vy = 20;
                w = 0;
            }
            else if (Vy_joy == -1){
                Vx = 0;
                Vy = -20;
                w = 0;
            }

            //Gerak X
            else if (Vx_joy == 1){
                Vx = -20;
                Vy = 0;
                w = 0;
            }
            else if (Vx_joy == -1){
                Vx = 20;
                Vy = 0;
                w = 0;
            }

            else{
                Vx = 0.0;
                Vy = 0.0;
                w = 0.0;
            }

            m1 = 0.7071 * (Vy - Vx) + (w * 0.471);
            rpm_m1 = m1 * 1.504050;
            // if (rpm_m1 > 0){
            //     dir1 = 1;
            // }
            // else if (rpm_m1 < 0){
            //     dir1 = -1;
            // }
            // else{
            //     dir1 = 0;
            // }
            m2 = 0.7071 * -(Vy + Vx) + (w * 0.471);
            rpm_m2 = m2 * 1.504050;
            // if (rpm_m2 > 0){
            //     dir2 = 1;
            // }
            // else if (rpm_m2 < 0){
            //     dir2 = -1;
            // }
            // else{
            //     dir2 = 0;
            // }
            m3 = 0.7071 * (Vx - Vy) + (w * 0.471);
            rpm_m3 = m3 * 1.504050;
            // if (rpm_m3 > 0){
            //     dir3 = 1;
            // }
            // else if (rpm_m3 < 0){
            //     dir3 = -1;
            // }
            // else{
            //     dir3 = 0;
            // }
            m4 = 0.7071 * (Vx + Vy) + (w * 0.471);
            rpm_m4 = m4 * 1.504050;
            // if (rpm_m4 > 0){
            //     dir4 = 1;
            // }
            // else if (rpm_m4 < 0){
            //     dir4 = -1;
            // }
            // else{
            //     dir4 = 0;
            // }
                       
            // geometry_msgs::Pose2D m_1;
            // geometry_msgs::Pose2D m_2;
            // geometry_msgs::Pose2D m_3;
            // geometry_msgs::Pose2D m_4;

            // Motor 1
            m_1.x = rpm_m1;
            // m_1.y = dir1;

            // Motor 2
            m_2.x = rpm_m2;
            // m_2.y = dir2;

            // Motor 3
            m_3.x = rpm_m3;
            // m_3.y = dir3;

            // Motor 4
            m_4.x = rpm_m4;
            // m_4.y = dir4;

            vel_m1.publish(m_1);
            vel_m2.publish(m_2);
            vel_m3.publish(m_3);
            vel_m4.publish(m_4);
        }
};

int main(int argc, char** argv){
    ros::init(argc, argv, "k21_kinematics");
    ros::NodeHandle nh;
    K21Kinematics k21_kinematics = K21Kinematics(&nh);
    ros::spin();
    return 0;
}
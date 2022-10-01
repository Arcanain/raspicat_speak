#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"
#include "geometry_msgs/Twist.h"

#include <sstream>

ros::Subscriber state_sub;
ros::Subscriber cmd_vel_joystick_sub;
ros::Subscriber cmd_vel_keyboard_sub;
ros::Subscriber cmd_vel_automatic_sub;

ros::Publisher hoge1_pub;
ros::Publisher hoge2_pub;
ros::Publisher hoge3_pub;
ros::Publisher hoge4_pub;
ros::Publisher hoge5_pub;

geometry_msgs::Twist cmd_vel_joystick;
geometry_msgs::Twist cmd_vel_keyboard;
geometry_msgs::Twist cmd_vel_automatic;

/*
void state_callback(const std_msgs::Int8::ConstPtr &state_msg)
{
    std_msgs::String msg;
    std::stringstream ss;

    if (state_msg->data == 1) {
        ss << "hoge" << 1;
        msg.data = ss.str();
        hoge1_pub.publish(msg);
    } else if (state_msg->data == 2) {
        ss << "hoge" << 2;
        msg.data = ss.str();
        hoge2_pub.publish(msg);
    } else if (state_msg->data == 3) {
        ss << "hoge" << 3;
        msg.data = ss.str();
        hoge3_pub.publish(msg);
    } else if (state_msg->data == 4) {
        ss << "hoge" << 4;
        msg.data = ss.str();
        hoge4_pub.publish(msg);
    } 
}
*/

void cmd_vel_joystick_callback(const geometry_msgs::Twist::ConstPtr &cmd_vel)
{
    cmd_vel_joystick = *cmd_vel;
}

void cmd_vel_keyboard_callback(const geometry_msgs::Twist::ConstPtr &cmd_vel)
{
    cmd_vel_keyboard = *cmd_vel;
}

void cmd_vel_automatic_callback(const geometry_msgs::Twist::ConstPtr &cmd_vel)
{
    cmd_vel_automatic = *cmd_vel;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "navigation_voice_playback");
    ros::NodeHandle nh;

    //state_sub = nh.subscribe("/state", 10, state_callback);
    cmd_vel_joystick_sub = nh.subscribe("/cmd_vel_joystick", 10, cmd_vel_joystick_callback);
    cmd_vel_keyboard_sub = nh.subscribe("/cmd_vel_keyboard", 10, cmd_vel_keyboard_callback);
    cmd_vel_automatic_sub = nh.subscribe("/cmd_vel_automatic", 10, cmd_vel_automatic_callback);

    hoge1_pub = nh.advertise<std_msgs::String>("/hoge1", 10);
    hoge2_pub = nh.advertise<std_msgs::String>("/hoge2", 10);
    hoge3_pub = nh.advertise<std_msgs::String>("/hoge3", 10);
    hoge4_pub = nh.advertise<std_msgs::String>("/hoge4", 10);
    hoge5_pub = nh.advertise<std_msgs::String>("/hoge5", 10);

    ros::Rate loop_rate(0.1);

    while (ros::ok())
    {        
        std_msgs::String msg;
        std::stringstream ss;

        int state_data;
        if (cmd_vel_joystick.linear.x != 0 || cmd_vel_joystick.angular.z != 0) {
            state_data = 1;
        } else if (cmd_vel_keyboard.linear.x != 0 || cmd_vel_keyboard.angular.z != 0) {
            state_data = 2;
        } else if (cmd_vel_automatic.linear.x != 0 || cmd_vel_automatic.angular.z != 0) {
            state_data = 3;
        } else {
            state_data = 4;
        }

        if (state_data == 1) {
            ss << "hoge" << 5;
            msg.data = ss.str();
            hoge5_pub.publish(msg);
        } else if (state_data == 2) {
            ss << "hoge" << 5;
            msg.data = ss.str();
            hoge5_pub.publish(msg);
        } else if (state_data == 3) {
            ss << "hoge" << 4;
            msg.data = ss.str();
            hoge4_pub.publish(msg);
        } else if (state_data == 4) {
            ss << "hoge" << 1;
            msg.data = ss.str();
            hoge1_pub.publish(msg);
        }

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}
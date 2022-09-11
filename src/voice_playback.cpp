#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main(int argc, char **argv) {
  ros::init(argc, argv, "voice_playback");
  ros::NodeHandle nh;

  ros::Publisher hoge1_pub = nh.advertise<std_msgs::String>("/hoge1", 10);
  ros::Publisher hoge2_pub = nh.advertise<std_msgs::String>("/hoge2", 10);
  ros::Publisher hoge3_pub = nh.advertise<std_msgs::String>("/hoge3", 10);
  ros::Publisher hoge4_pub = nh.advertise<std_msgs::String>("/hoge4", 10);
  ros::Publisher hoge5_pub = nh.advertise<std_msgs::String>("/hoge5", 10);

  ros::Rate loop_rate(0.2);

  int count = 1;
  while (ros::ok())
  {
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hoge" << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    if (count == 1) {
        hoge1_pub.publish(msg);
    } else if (count == 2) {
        hoge2_pub.publish(msg);
    } else if (count == 3) {
        hoge3_pub.publish(msg);
    } else if (count == 4) {
        hoge4_pub.publish(msg);
    } else if (count == 5) {
        hoge5_pub.publish(msg);
        count = 0;
    }

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  return 0;
}
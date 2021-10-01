#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "ros/ros.h"
#include "tf/transform_datatypes.h"

double x_actual;
double theta_actual;

void odometryCallback(const nav_msgs::Odometry::ConstPtr &msg) {

  x_actual = msg->pose.pose.position.x;
  tf::Quaternion quat;
  tf::quaternionMsgToTF(msg->pose.pose.orientation, quat);
  double roll, pitch, yaw;
  tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);
  theta_actual = yaw;
  // ROS_INFO("X: [%f]", msg->pose.pose.position.x);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "pub_odom");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/odom", 1000, odometryCallback);
  ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  double dt = 1. / 10;
  ros::Rate loop_rate(1 / dt);

  double x_deseado = 2.0;
  double kp = 0.2;
  double ki = 0;
  double kd = 0;
  double integral = 0;
  double derivativa = 0;
  double error_previo = 0;

  while (ros::ok()) {

    geometry_msgs::Twist vel;

    // Put your code here
    //
    //
    //
    // Your code ends here

    // vel.linear.x = u;
    cmd_vel_pub.publish(vel);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
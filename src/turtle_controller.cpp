#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>

double x_d, y_d;

double forward_control=0.0;
double orientation_control=0.0;
double k_pf , k_po;

void posecallback(const turtlesim::Pose::ConstPtr& pose_msg)
{
 double x_error = x_d - pose_msg->x;
 double y_error = y_d - pose_msg->y;
 //to do:
 // compute orientation_control= ....
 // Hint : use atan2(y_error, x_error)

 forward_control= k_pf* x_error;
}



int main(int argc, char** argv)
{
  ros::init(argc, argv, "turtle_controller");
  ros::NodeHandle nh;

  ros::Publisher control_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
  ros::Subscriber pose_sub = nh.subscribe("/turtle1/pose", 10, &posecallback);
  nh.param("goal_x", x_d, 7.0);
  nh.param("goal_y", y_d, 7.0);
  nh.param("Surge_gain", k_pf, 1.0);
  nh.param("Orientiation_gain", k_po, 1.0);

  ros::Rate rate(100.0);

  while (ros::ok())
  {
    ros::spinOnce();

    geometry_msgs::Twist controls;
    controls.linear.x = forward_control;
    controls.angular.z = orientation_control;

    control_pub.publish(controls);

    rate.sleep();
  }

  return 0;
}

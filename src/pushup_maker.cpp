#include<ros/ros.h>

bool i_am_tired= false;
ros::Timer timer;

void timerCallback(const ros::TimerEvent&) {
  static int counter=0;
  counter++;

  if(counter>10){

    ROS_INFO_STREAM("I am continuing");
    timer.stop();
  }
   else
  ROS_INFO_STREAM("I did a pushup!:"<<counter);

}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "timer");
  ros::NodeHandle nh;

  timer = nh.createTimer(ros::Duration(1.0), timerCallback);

  ros::spin();
  return 0;
}

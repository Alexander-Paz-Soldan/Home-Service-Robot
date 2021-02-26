#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <math.h>

float goalPosX = 0.0;
float goalPosY = 0.0;
bool isNearGoal = false;          
float range = 0.2; 
// callback method determine nearness.
void odom_callback(const nav_msgs::Odometry::ConstPtr& odom_msg)
{
   
  float deltaX = goalPosX - odom_msg->pose.pose.position.x;
  float deltaY = goalPosY - odom_msg->pose.pose.position.y;
  float distance = sqrt(pow(deltaX,2) + pow(deltaY,2));
  if(distance < range){
    isNearGoal = true;
  } else {
    isNearGoal = false;
  }
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odometry_sub = n.subscribe("/odom", 1000, odometry_callback);
  // Set our shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "shape";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 1.0f;
    marker.color.g = 1.0f;
    marker.color.b = 2.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();
      
    // Publish the marker     
    marker_pub.publish(marker);
    ROS_INFO("Showing marker at source.");
    // end first publishing
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
   goalPosX = marker.pose.position.x;
   goalPosY = marker.pose.position.y;
   while (ros::ok() && !isNearGoal) {
    ros::spinOnce();
    // some sleep here
   }
   ROS_INFO("Object picked up");
   marker.action = visualization_msgs::Marker::DELETE;
   marker_pub.publish(marker);
   // send object somewhere
   near_goal = false;
   goalPosX = -3.0;
   goalPosY = 4.0;
 
   while (ros::ok() && !isNearGoal) {
    ros::spinOnce();
    // sleep here.
   }

  ROS_INFO("Object dropped off");
  marker.action = visualization_msgs::Marker::ADD;
  marker_pub.publish(marker);
  sleep(5);

}

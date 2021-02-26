#!/bin/bash
echo "setting workspace.."
cd /home/workspace/catkin_ws && source devel/setup.bash
echo "launching world..."
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/world/world.world" &
sleep 5
echo "launch map server"
xterm -e "rosrun map_server map_saver -f /home/workspace/catkin_ws/src/map/map" &
sleep 5
echo "launching gmapping demo..."
xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 5
echo "launching view..."
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
echo "launching teleop..."
xterm -e "roslaunch turtlebot_teleop keyboard_teleop.launch" &

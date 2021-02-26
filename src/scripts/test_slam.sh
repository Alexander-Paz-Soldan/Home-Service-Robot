#!/bin/bash
srcFolder=$(rospack find add_markers)/../
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=${srcFolder}/world/world.world" &
sleep 5
echo "launch map server"
xterm -e "rosrun map_server map_saver -f ${srcFolder}/map/map" &
sleep 5
echo "launching gmapping demo..."
xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 5
echo "launching view..."
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
echo "launching teleop..."
xterm -e "roslaunch turtlebot_teleop keyboard_teleop.launch" &

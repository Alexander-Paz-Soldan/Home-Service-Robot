#!/bin/bash
srcFolder=$(rospack find add_markers)/../
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=${srcFolder}/world/world.world" &
sleep 5
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=${srcFolder}/map/map.yaml" &
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
echo "running add markers"
xterm -e "rosrun add_markers add_markers" &
sleep 3
xterm -e "rosrun pick_objects pick_objects" &

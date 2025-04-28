#!/bin/bash
#Script to start the ros simulations 
#xterm -hold -e ". ~/catkin_ws/devel/setup.bash && roscd svg_ros/src/data/ && rosrun svg_ros inputs" &
#xterm -hold -e ". ~/catkin_ws/devel/setup.bash && roscd svg_ros/src/data/ && rosrun svg_ros light_node" & 
#xterm -hold -e ". ~/catkin_ws/devel/setup.bash && roscd svg_ros/src/data/ && rosrun svg_ros sensor_node -selection 1 " & 
#xterm -hold -e ". ~/catkin_ws/devel/setup.bash && roscd svg_ros/src/data/ && rosrun svg_ros base_node " &
#xterm -hold -e ". ~/catkin_ws/devel/setup.bash && roscd svg_ros/src/data/ && rosrun svg_ros motion_planner_ROS -selection 1 -laser 1 -light 1" &

#xterm -hold -e ". ~/catkin_ws/devel/setup.bash && roscd svg_ros/src/data/ && rosrun svg_ros mv_turtle.py"  &

#xterm -hold -e ". ~/catkin_ws/devel/setup.bash && roscd svg_ros/src/data/ && rosrun svg_ros GUI_ROS.py" & 

xterm -hold -e ". ~/catkin_ws/devel/setup.bash && roscd svg_ros/src/data/ && rosrun planning_rm ros_pyclips_node.py" & 

xterm -hold -e ". ~/catkin_ws/devel/setup.bash && roscd svg_ros/src/data/ && rosrun planning_rm ros_pyclips_services.py" & 

xterm -hold -e ". ~/catkin_ws/devel/setup.bash && roscd svg_ros/src/data/ && rosrun planner robot_movil_test" & 

xterm -hold -e ". ~/catkin_ws/devel/setup.bash && roscd svg_ros/src/data/ && rosrun planner speech_recog" & 



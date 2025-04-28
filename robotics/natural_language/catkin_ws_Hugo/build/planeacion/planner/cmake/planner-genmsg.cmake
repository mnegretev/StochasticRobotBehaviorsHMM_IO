# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(WARNING "Invoking generate_messages() without having added any message or service file before.
You should either add add_message_files() and/or add_service_files() calls or remove the invocation of generate_messages().")
message(STATUS "planner: 0 messages, 0 services")

set(MSG_I_FLAGS "-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Iplanner_msgs:/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg")

# Find all generators

add_custom_target(planner_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



#
#  langs = 
#



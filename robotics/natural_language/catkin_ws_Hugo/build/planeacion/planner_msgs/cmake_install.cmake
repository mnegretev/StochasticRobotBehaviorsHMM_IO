# Install script for directory: /home/biorobotica/catkin_ws/src/planeacion/planner_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/biorobotica/catkin_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/planner_msgs/msg" TYPE FILE FILES
    "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RecognizedSpeech.msg"
    "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdClips.msg"
    "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RepeatedSentence.msg"
    "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg"
    "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdSend.msg"
    "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCFR.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/planner_msgs/srv" TYPE FILE FILES "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/srv/planning_cmd.srv")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/planner_msgs/cmake" TYPE FILE FILES "/home/biorobotica/catkin_ws/build/planeacion/planner_msgs/catkin_generated/installspace/planner_msgs-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/biorobotica/catkin_ws/devel/include/planner_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/biorobotica/catkin_ws/devel/share/roseus/ros/planner_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/biorobotica/catkin_ws/devel/share/common-lisp/ros/planner_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/biorobotica/catkin_ws/devel/share/gennodejs/ros/planner_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/biorobotica/catkin_ws/devel/lib/python2.7/dist-packages/planner_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/biorobotica/catkin_ws/devel/lib/python2.7/dist-packages/planner_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/biorobotica/catkin_ws/build/planeacion/planner_msgs/catkin_generated/installspace/planner_msgs.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/planner_msgs/cmake" TYPE FILE FILES "/home/biorobotica/catkin_ws/build/planeacion/planner_msgs/catkin_generated/installspace/planner_msgs-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/planner_msgs/cmake" TYPE FILE FILES
    "/home/biorobotica/catkin_ws/build/planeacion/planner_msgs/catkin_generated/installspace/planner_msgsConfig.cmake"
    "/home/biorobotica/catkin_ws/build/planeacion/planner_msgs/catkin_generated/installspace/planner_msgsConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/planner_msgs" TYPE FILE FILES "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/package.xml")
endif()


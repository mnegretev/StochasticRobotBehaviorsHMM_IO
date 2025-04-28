# Install script for directory: /home/biorobotica/catkin_ws/src/svg_ros

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/svg_ros/srv" TYPE FILE FILES
    "/home/biorobotica/catkin_ws/src/svg_ros/srv/GetLaserServ.srv"
    "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsSrv.srv"
    "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsPlannerSrv.srv"
    "/home/biorobotica/catkin_ws/src/svg_ros/srv/MVServ.srv"
    "/home/biorobotica/catkin_ws/src/svg_ros/srv/SensorSrv.srv"
    "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightRealSrv.srv"
    "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightSrv.srv"
    "/home/biorobotica/catkin_ws/src/svg_ros/srv/OverSrv.srv"
    "/home/biorobotica/catkin_ws/src/svg_ros/srv/ReadySrv.srv"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/svg_ros/cmake" TYPE FILE FILES "/home/biorobotica/catkin_ws/build/svg_ros/catkin_generated/installspace/svg_ros-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/biorobotica/catkin_ws/devel/include/svg_ros")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/biorobotica/catkin_ws/devel/share/roseus/ros/svg_ros")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/biorobotica/catkin_ws/devel/share/common-lisp/ros/svg_ros")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/biorobotica/catkin_ws/devel/share/gennodejs/ros/svg_ros")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/biorobotica/catkin_ws/devel/lib/python2.7/dist-packages/svg_ros")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/biorobotica/catkin_ws/devel/lib/python2.7/dist-packages/svg_ros")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/biorobotica/catkin_ws/build/svg_ros/catkin_generated/installspace/svg_ros.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/svg_ros/cmake" TYPE FILE FILES "/home/biorobotica/catkin_ws/build/svg_ros/catkin_generated/installspace/svg_ros-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/svg_ros/cmake" TYPE FILE FILES
    "/home/biorobotica/catkin_ws/build/svg_ros/catkin_generated/installspace/svg_rosConfig.cmake"
    "/home/biorobotica/catkin_ws/build/svg_ros/catkin_generated/installspace/svg_rosConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/svg_ros" TYPE FILE FILES "/home/biorobotica/catkin_ws/src/svg_ros/package.xml")
endif()


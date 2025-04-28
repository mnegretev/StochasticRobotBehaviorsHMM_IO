# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "svg_ros: 0 messages, 9 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(svg_ros_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsPlannerSrv.srv" NAME_WE)
add_custom_target(_svg_ros_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "svg_ros" "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsPlannerSrv.srv" ""
)

get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightRealSrv.srv" NAME_WE)
add_custom_target(_svg_ros_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "svg_ros" "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightRealSrv.srv" ""
)

get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/MVServ.srv" NAME_WE)
add_custom_target(_svg_ros_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "svg_ros" "/home/biorobotica/catkin_ws/src/svg_ros/srv/MVServ.srv" ""
)

get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/GetLaserServ.srv" NAME_WE)
add_custom_target(_svg_ros_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "svg_ros" "/home/biorobotica/catkin_ws/src/svg_ros/srv/GetLaserServ.srv" ""
)

get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightSrv.srv" NAME_WE)
add_custom_target(_svg_ros_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "svg_ros" "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightSrv.srv" ""
)

get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/ReadySrv.srv" NAME_WE)
add_custom_target(_svg_ros_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "svg_ros" "/home/biorobotica/catkin_ws/src/svg_ros/srv/ReadySrv.srv" ""
)

get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/OverSrv.srv" NAME_WE)
add_custom_target(_svg_ros_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "svg_ros" "/home/biorobotica/catkin_ws/src/svg_ros/srv/OverSrv.srv" ""
)

get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsSrv.srv" NAME_WE)
add_custom_target(_svg_ros_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "svg_ros" "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsSrv.srv" ""
)

get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/SensorSrv.srv" NAME_WE)
add_custom_target(_svg_ros_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "svg_ros" "/home/biorobotica/catkin_ws/src/svg_ros/srv/SensorSrv.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsPlannerSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/svg_ros
)
_generate_srv_cpp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightRealSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/svg_ros
)
_generate_srv_cpp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/MVServ.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/svg_ros
)
_generate_srv_cpp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/GetLaserServ.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/svg_ros
)
_generate_srv_cpp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/svg_ros
)
_generate_srv_cpp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/ReadySrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/svg_ros
)
_generate_srv_cpp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/OverSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/svg_ros
)
_generate_srv_cpp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/svg_ros
)
_generate_srv_cpp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/SensorSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/svg_ros
)

### Generating Module File
_generate_module_cpp(svg_ros
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/svg_ros
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(svg_ros_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(svg_ros_generate_messages svg_ros_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsPlannerSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_cpp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightRealSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_cpp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/MVServ.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_cpp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/GetLaserServ.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_cpp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_cpp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/ReadySrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_cpp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/OverSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_cpp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_cpp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/SensorSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_cpp _svg_ros_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(svg_ros_gencpp)
add_dependencies(svg_ros_gencpp svg_ros_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS svg_ros_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services
_generate_srv_eus(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsPlannerSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/svg_ros
)
_generate_srv_eus(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightRealSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/svg_ros
)
_generate_srv_eus(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/MVServ.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/svg_ros
)
_generate_srv_eus(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/GetLaserServ.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/svg_ros
)
_generate_srv_eus(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/svg_ros
)
_generate_srv_eus(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/ReadySrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/svg_ros
)
_generate_srv_eus(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/OverSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/svg_ros
)
_generate_srv_eus(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/svg_ros
)
_generate_srv_eus(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/SensorSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/svg_ros
)

### Generating Module File
_generate_module_eus(svg_ros
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/svg_ros
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(svg_ros_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(svg_ros_generate_messages svg_ros_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsPlannerSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_eus _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightRealSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_eus _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/MVServ.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_eus _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/GetLaserServ.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_eus _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_eus _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/ReadySrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_eus _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/OverSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_eus _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_eus _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/SensorSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_eus _svg_ros_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(svg_ros_geneus)
add_dependencies(svg_ros_geneus svg_ros_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS svg_ros_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsPlannerSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/svg_ros
)
_generate_srv_lisp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightRealSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/svg_ros
)
_generate_srv_lisp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/MVServ.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/svg_ros
)
_generate_srv_lisp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/GetLaserServ.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/svg_ros
)
_generate_srv_lisp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/svg_ros
)
_generate_srv_lisp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/ReadySrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/svg_ros
)
_generate_srv_lisp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/OverSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/svg_ros
)
_generate_srv_lisp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/svg_ros
)
_generate_srv_lisp(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/SensorSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/svg_ros
)

### Generating Module File
_generate_module_lisp(svg_ros
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/svg_ros
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(svg_ros_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(svg_ros_generate_messages svg_ros_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsPlannerSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_lisp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightRealSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_lisp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/MVServ.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_lisp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/GetLaserServ.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_lisp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_lisp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/ReadySrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_lisp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/OverSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_lisp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_lisp _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/SensorSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_lisp _svg_ros_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(svg_ros_genlisp)
add_dependencies(svg_ros_genlisp svg_ros_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS svg_ros_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services
_generate_srv_nodejs(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsPlannerSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/svg_ros
)
_generate_srv_nodejs(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightRealSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/svg_ros
)
_generate_srv_nodejs(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/MVServ.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/svg_ros
)
_generate_srv_nodejs(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/GetLaserServ.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/svg_ros
)
_generate_srv_nodejs(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/svg_ros
)
_generate_srv_nodejs(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/ReadySrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/svg_ros
)
_generate_srv_nodejs(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/OverSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/svg_ros
)
_generate_srv_nodejs(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/svg_ros
)
_generate_srv_nodejs(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/SensorSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/svg_ros
)

### Generating Module File
_generate_module_nodejs(svg_ros
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/svg_ros
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(svg_ros_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(svg_ros_generate_messages svg_ros_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsPlannerSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_nodejs _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightRealSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_nodejs _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/MVServ.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_nodejs _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/GetLaserServ.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_nodejs _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_nodejs _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/ReadySrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_nodejs _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/OverSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_nodejs _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_nodejs _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/SensorSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_nodejs _svg_ros_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(svg_ros_gennodejs)
add_dependencies(svg_ros_gennodejs svg_ros_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS svg_ros_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsPlannerSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/svg_ros
)
_generate_srv_py(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightRealSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/svg_ros
)
_generate_srv_py(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/MVServ.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/svg_ros
)
_generate_srv_py(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/GetLaserServ.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/svg_ros
)
_generate_srv_py(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/svg_ros
)
_generate_srv_py(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/ReadySrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/svg_ros
)
_generate_srv_py(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/OverSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/svg_ros
)
_generate_srv_py(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/svg_ros
)
_generate_srv_py(svg_ros
  "/home/biorobotica/catkin_ws/src/svg_ros/srv/SensorSrv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/svg_ros
)

### Generating Module File
_generate_module_py(svg_ros
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/svg_ros
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(svg_ros_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(svg_ros_generate_messages svg_ros_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsPlannerSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_py _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightRealSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_py _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/MVServ.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_py _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/GetLaserServ.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_py _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/LightSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_py _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/ReadySrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_py _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/OverSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_py _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/InputsSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_py _svg_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/svg_ros/srv/SensorSrv.srv" NAME_WE)
add_dependencies(svg_ros_generate_messages_py _svg_ros_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(svg_ros_genpy)
add_dependencies(svg_ros_genpy svg_ros_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS svg_ros_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/svg_ros)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/svg_ros
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(svg_ros_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/svg_ros)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/svg_ros
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(svg_ros_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/svg_ros)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/svg_ros
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(svg_ros_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/svg_ros)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/svg_ros
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(svg_ros_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/svg_ros)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/svg_ros\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/svg_ros
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(svg_ros_generate_messages_py std_msgs_generate_messages_py)
endif()

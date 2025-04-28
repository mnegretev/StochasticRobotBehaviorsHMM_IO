# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "planner_msgs: 6 messages, 1 services")

set(MSG_I_FLAGS "-Iplanner_msgs:/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg;-Iplanner_msgs:/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(planner_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdSend.msg" NAME_WE)
add_custom_target(_planner_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "planner_msgs" "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdSend.msg" ""
)

get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RepeatedSentence.msg" NAME_WE)
add_custom_target(_planner_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "planner_msgs" "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RepeatedSentence.msg" ""
)

get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg" NAME_WE)
add_custom_target(_planner_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "planner_msgs" "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg" ""
)

get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/srv/planning_cmd.srv" NAME_WE)
add_custom_target(_planner_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "planner_msgs" "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/srv/planning_cmd.srv" ""
)

get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RecognizedSpeech.msg" NAME_WE)
add_custom_target(_planner_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "planner_msgs" "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RecognizedSpeech.msg" ""
)

get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdClips.msg" NAME_WE)
add_custom_target(_planner_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "planner_msgs" "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdClips.msg" ""
)

get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCFR.msg" NAME_WE)
add_custom_target(_planner_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "planner_msgs" "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCFR.msg" "planner_msgs/CFRParams"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdSend.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/planner_msgs
)
_generate_msg_cpp(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RepeatedSentence.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/planner_msgs
)
_generate_msg_cpp(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/planner_msgs
)
_generate_msg_cpp(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RecognizedSpeech.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/planner_msgs
)
_generate_msg_cpp(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdClips.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/planner_msgs
)
_generate_msg_cpp(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCFR.msg"
  "${MSG_I_FLAGS}"
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/planner_msgs
)

### Generating Services
_generate_srv_cpp(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/srv/planning_cmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/planner_msgs
)

### Generating Module File
_generate_module_cpp(planner_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/planner_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(planner_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(planner_msgs_generate_messages planner_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdSend.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_cpp _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RepeatedSentence.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_cpp _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_cpp _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/srv/planning_cmd.srv" NAME_WE)
add_dependencies(planner_msgs_generate_messages_cpp _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RecognizedSpeech.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_cpp _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdClips.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_cpp _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCFR.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_cpp _planner_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(planner_msgs_gencpp)
add_dependencies(planner_msgs_gencpp planner_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS planner_msgs_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdSend.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/planner_msgs
)
_generate_msg_eus(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RepeatedSentence.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/planner_msgs
)
_generate_msg_eus(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/planner_msgs
)
_generate_msg_eus(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RecognizedSpeech.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/planner_msgs
)
_generate_msg_eus(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdClips.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/planner_msgs
)
_generate_msg_eus(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCFR.msg"
  "${MSG_I_FLAGS}"
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/planner_msgs
)

### Generating Services
_generate_srv_eus(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/srv/planning_cmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/planner_msgs
)

### Generating Module File
_generate_module_eus(planner_msgs
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/planner_msgs
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(planner_msgs_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(planner_msgs_generate_messages planner_msgs_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdSend.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_eus _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RepeatedSentence.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_eus _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_eus _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/srv/planning_cmd.srv" NAME_WE)
add_dependencies(planner_msgs_generate_messages_eus _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RecognizedSpeech.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_eus _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdClips.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_eus _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCFR.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_eus _planner_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(planner_msgs_geneus)
add_dependencies(planner_msgs_geneus planner_msgs_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS planner_msgs_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdSend.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/planner_msgs
)
_generate_msg_lisp(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RepeatedSentence.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/planner_msgs
)
_generate_msg_lisp(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/planner_msgs
)
_generate_msg_lisp(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RecognizedSpeech.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/planner_msgs
)
_generate_msg_lisp(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdClips.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/planner_msgs
)
_generate_msg_lisp(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCFR.msg"
  "${MSG_I_FLAGS}"
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/planner_msgs
)

### Generating Services
_generate_srv_lisp(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/srv/planning_cmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/planner_msgs
)

### Generating Module File
_generate_module_lisp(planner_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/planner_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(planner_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(planner_msgs_generate_messages planner_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdSend.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_lisp _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RepeatedSentence.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_lisp _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_lisp _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/srv/planning_cmd.srv" NAME_WE)
add_dependencies(planner_msgs_generate_messages_lisp _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RecognizedSpeech.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_lisp _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdClips.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_lisp _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCFR.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_lisp _planner_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(planner_msgs_genlisp)
add_dependencies(planner_msgs_genlisp planner_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS planner_msgs_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdSend.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/planner_msgs
)
_generate_msg_nodejs(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RepeatedSentence.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/planner_msgs
)
_generate_msg_nodejs(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/planner_msgs
)
_generate_msg_nodejs(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RecognizedSpeech.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/planner_msgs
)
_generate_msg_nodejs(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdClips.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/planner_msgs
)
_generate_msg_nodejs(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCFR.msg"
  "${MSG_I_FLAGS}"
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/planner_msgs
)

### Generating Services
_generate_srv_nodejs(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/srv/planning_cmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/planner_msgs
)

### Generating Module File
_generate_module_nodejs(planner_msgs
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/planner_msgs
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(planner_msgs_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(planner_msgs_generate_messages planner_msgs_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdSend.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_nodejs _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RepeatedSentence.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_nodejs _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_nodejs _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/srv/planning_cmd.srv" NAME_WE)
add_dependencies(planner_msgs_generate_messages_nodejs _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RecognizedSpeech.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_nodejs _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdClips.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_nodejs _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCFR.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_nodejs _planner_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(planner_msgs_gennodejs)
add_dependencies(planner_msgs_gennodejs planner_msgs_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS planner_msgs_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdSend.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/planner_msgs
)
_generate_msg_py(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RepeatedSentence.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/planner_msgs
)
_generate_msg_py(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/planner_msgs
)
_generate_msg_py(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RecognizedSpeech.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/planner_msgs
)
_generate_msg_py(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdClips.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/planner_msgs
)
_generate_msg_py(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCFR.msg"
  "${MSG_I_FLAGS}"
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/planner_msgs
)

### Generating Services
_generate_srv_py(planner_msgs
  "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/srv/planning_cmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/planner_msgs
)

### Generating Module File
_generate_module_py(planner_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/planner_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(planner_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(planner_msgs_generate_messages planner_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdSend.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_py _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RepeatedSentence.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_py _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/CFRParams.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_py _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/srv/planning_cmd.srv" NAME_WE)
add_dependencies(planner_msgs_generate_messages_py _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/RecognizedSpeech.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_py _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCmdClips.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_py _planner_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg/PlanningCFR.msg" NAME_WE)
add_dependencies(planner_msgs_generate_messages_py _planner_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(planner_msgs_genpy)
add_dependencies(planner_msgs_genpy planner_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS planner_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/planner_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/planner_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(planner_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(planner_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET planner_msgs_generate_messages_cpp)
  add_dependencies(planner_msgs_generate_messages_cpp planner_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/planner_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/planner_msgs
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(planner_msgs_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(planner_msgs_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET planner_msgs_generate_messages_eus)
  add_dependencies(planner_msgs_generate_messages_eus planner_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/planner_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/planner_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(planner_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(planner_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET planner_msgs_generate_messages_lisp)
  add_dependencies(planner_msgs_generate_messages_lisp planner_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/planner_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/planner_msgs
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(planner_msgs_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(planner_msgs_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET planner_msgs_generate_messages_nodejs)
  add_dependencies(planner_msgs_generate_messages_nodejs planner_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/planner_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/planner_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/planner_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(planner_msgs_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(planner_msgs_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET planner_msgs_generate_messages_py)
  add_dependencies(planner_msgs_generate_messages_py planner_msgs_generate_messages_py)
endif()

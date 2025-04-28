;; Auto-generated. Do not edit!


(when (boundp 'planner_msgs::PlanningCmdSend)
  (if (not (find-package "PLANNER_MSGS"))
    (make-package "PLANNER_MSGS"))
  (shadow 'PlanningCmdSend (find-package "PLANNER_MSGS")))
(unless (find-package "PLANNER_MSGS::PLANNINGCMDSEND")
  (make-package "PLANNER_MSGS::PLANNINGCMDSEND"))

(in-package "ROS")
;;//! \htmlinclude PlanningCmdSend.msg.html


(defclass planner_msgs::PlanningCmdSend
  :super ros::object
  :slots (_command ))

(defmethod planner_msgs::PlanningCmdSend
  (:init
   (&key
    ((:command __command) "")
    )
   (send-super :init)
   (setq _command (string __command))
   self)
  (:command
   (&optional __command)
   (if __command (setq _command __command)) _command)
  (:serialization-length
   ()
   (+
    ;; string _command
    4 (length _command)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _command
       (write-long (length _command) s) (princ _command s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _command
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _command (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get planner_msgs::PlanningCmdSend :md5sum-) "cba5e21e920a3a2b7b375cb65b64cdea")
(setf (get planner_msgs::PlanningCmdSend :datatype-) "planner_msgs/PlanningCmdSend")
(setf (get planner_msgs::PlanningCmdSend :definition-)
      "string command


")



(provide :planner_msgs/PlanningCmdSend "cba5e21e920a3a2b7b375cb65b64cdea")



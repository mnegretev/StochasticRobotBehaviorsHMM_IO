;; Auto-generated. Do not edit!


(when (boundp 'planner_msgs::planning_cmd)
  (if (not (find-package "PLANNER_MSGS"))
    (make-package "PLANNER_MSGS"))
  (shadow 'planning_cmd (find-package "PLANNER_MSGS")))
(unless (find-package "PLANNER_MSGS::PLANNING_CMD")
  (make-package "PLANNER_MSGS::PLANNING_CMD"))
(unless (find-package "PLANNER_MSGS::PLANNING_CMDREQUEST")
  (make-package "PLANNER_MSGS::PLANNING_CMDREQUEST"))
(unless (find-package "PLANNER_MSGS::PLANNING_CMDRESPONSE")
  (make-package "PLANNER_MSGS::PLANNING_CMDRESPONSE"))

(in-package "ROS")





(defclass planner_msgs::planning_cmdRequest
  :super ros::object
  :slots (_params _name ))

(defmethod planner_msgs::planning_cmdRequest
  (:init
   (&key
    ((:params __params) "")
    ((:name __name) "")
    )
   (send-super :init)
   (setq _params (string __params))
   (setq _name (string __name))
   self)
  (:params
   (&optional __params)
   (if __params (setq _params __params)) _params)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:serialization-length
   ()
   (+
    ;; string _params
    4 (length _params)
    ;; string _name
    4 (length _name)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _params
       (write-long (length _params) s) (princ _params s)
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _params
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _params (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass planner_msgs::planning_cmdResponse
  :super ros::object
  :slots (_success _args ))

(defmethod planner_msgs::planning_cmdResponse
  (:init
   (&key
    ((:success __success) nil)
    ((:args __args) "")
    )
   (send-super :init)
   (setq _success __success)
   (setq _args (string __args))
   self)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:args
   (&optional __args)
   (if __args (setq _args __args)) _args)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ;; string _args
    4 (length _args)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;; string _args
       (write-long (length _args) s) (princ _args s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; string _args
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _args (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass planner_msgs::planning_cmd
  :super ros::object
  :slots ())

(setf (get planner_msgs::planning_cmd :md5sum-) "f9f6635257061aef8bea97260f4e6a8b")
(setf (get planner_msgs::planning_cmd :datatype-) "planner_msgs/planning_cmd")
(setf (get planner_msgs::planning_cmd :request) planner_msgs::planning_cmdRequest)
(setf (get planner_msgs::planning_cmd :response) planner_msgs::planning_cmdResponse)

(defmethod planner_msgs::planning_cmdRequest
  (:response () (instance planner_msgs::planning_cmdResponse :init)))

(setf (get planner_msgs::planning_cmdRequest :md5sum-) "f9f6635257061aef8bea97260f4e6a8b")
(setf (get planner_msgs::planning_cmdRequest :datatype-) "planner_msgs/planning_cmdRequest")
(setf (get planner_msgs::planning_cmdRequest :definition-)
      "string params
string name
---
bool success
string args
")

(setf (get planner_msgs::planning_cmdResponse :md5sum-) "f9f6635257061aef8bea97260f4e6a8b")
(setf (get planner_msgs::planning_cmdResponse :datatype-) "planner_msgs/planning_cmdResponse")
(setf (get planner_msgs::planning_cmdResponse :definition-)
      "string params
string name
---
bool success
string args
")



(provide :planner_msgs/planning_cmd "f9f6635257061aef8bea97260f4e6a8b")



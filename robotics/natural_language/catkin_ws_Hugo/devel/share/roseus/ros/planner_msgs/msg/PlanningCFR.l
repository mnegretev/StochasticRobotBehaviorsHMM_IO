;; Auto-generated. Do not edit!


(when (boundp 'planner_msgs::PlanningCFR)
  (if (not (find-package "PLANNER_MSGS"))
    (make-package "PLANNER_MSGS"))
  (shadow 'PlanningCFR (find-package "PLANNER_MSGS")))
(unless (find-package "PLANNER_MSGS::PLANNINGCFR")
  (make-package "PLANNER_MSGS::PLANNINGCFR"))

(in-package "ROS")
;;//! \htmlinclude PlanningCFR.msg.html


(defclass planner_msgs::PlanningCFR
  :super ros::object
  :slots (_command _params ))

(defmethod planner_msgs::PlanningCFR
  (:init
   (&key
    ((:command __command) "")
    ((:params __params) (let (r) (dotimes (i 0) (push (instance planner_msgs::CFRParams :init) r)) r))
    )
   (send-super :init)
   (setq _command (string __command))
   (setq _params __params)
   self)
  (:command
   (&optional __command)
   (if __command (setq _command __command)) _command)
  (:params
   (&rest __params)
   (if (keywordp (car __params))
       (send* _params __params)
     (progn
       (if __params (setq _params (car __params)))
       _params)))
  (:serialization-length
   ()
   (+
    ;; string _command
    4 (length _command)
    ;; planner_msgs/CFRParams[] _params
    (apply #'+ (send-all _params :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _command
       (write-long (length _command) s) (princ _command s)
     ;; planner_msgs/CFRParams[] _params
     (write-long (length _params) s)
     (dolist (elem _params)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _command
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _command (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; planner_msgs/CFRParams[] _params
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _params (let (r) (dotimes (i n) (push (instance planner_msgs::CFRParams :init) r)) r))
     (dolist (elem- _params)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get planner_msgs::PlanningCFR :md5sum-) "1bda369640b5ce77a1917aec327930a1")
(setf (get planner_msgs::PlanningCFR :datatype-) "planner_msgs/PlanningCFR")
(setf (get planner_msgs::PlanningCFR :definition-)
      "string command
CFRParams[] params

================================================================================
MSG: planner_msgs/CFRParams
string frame_id
string frame_value

")



(provide :planner_msgs/PlanningCFR "1bda369640b5ce77a1917aec327930a1")



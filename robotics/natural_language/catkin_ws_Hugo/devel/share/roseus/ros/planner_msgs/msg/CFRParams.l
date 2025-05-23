;; Auto-generated. Do not edit!


(when (boundp 'planner_msgs::CFRParams)
  (if (not (find-package "PLANNER_MSGS"))
    (make-package "PLANNER_MSGS"))
  (shadow 'CFRParams (find-package "PLANNER_MSGS")))
(unless (find-package "PLANNER_MSGS::CFRPARAMS")
  (make-package "PLANNER_MSGS::CFRPARAMS"))

(in-package "ROS")
;;//! \htmlinclude CFRParams.msg.html


(defclass planner_msgs::CFRParams
  :super ros::object
  :slots (_frame_id _frame_value ))

(defmethod planner_msgs::CFRParams
  (:init
   (&key
    ((:frame_id __frame_id) "")
    ((:frame_value __frame_value) "")
    )
   (send-super :init)
   (setq _frame_id (string __frame_id))
   (setq _frame_value (string __frame_value))
   self)
  (:frame_id
   (&optional __frame_id)
   (if __frame_id (setq _frame_id __frame_id)) _frame_id)
  (:frame_value
   (&optional __frame_value)
   (if __frame_value (setq _frame_value __frame_value)) _frame_value)
  (:serialization-length
   ()
   (+
    ;; string _frame_id
    4 (length _frame_id)
    ;; string _frame_value
    4 (length _frame_value)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _frame_id
       (write-long (length _frame_id) s) (princ _frame_id s)
     ;; string _frame_value
       (write-long (length _frame_value) s) (princ _frame_value s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _frame_id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _frame_id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _frame_value
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _frame_value (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get planner_msgs::CFRParams :md5sum-) "4244adddfc44a0d0799b10600c99b834")
(setf (get planner_msgs::CFRParams :datatype-) "planner_msgs/CFRParams")
(setf (get planner_msgs::CFRParams :definition-)
      "string frame_id
string frame_value

")



(provide :planner_msgs/CFRParams "4244adddfc44a0d0799b10600c99b834")



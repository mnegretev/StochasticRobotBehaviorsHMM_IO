;; Auto-generated. Do not edit!


(when (boundp 'svg_ros::OverSrv)
  (if (not (find-package "SVG_ROS"))
    (make-package "SVG_ROS"))
  (shadow 'OverSrv (find-package "SVG_ROS")))
(unless (find-package "SVG_ROS::OVERSRV")
  (make-package "SVG_ROS::OVERSRV"))
(unless (find-package "SVG_ROS::OVERSRVREQUEST")
  (make-package "SVG_ROS::OVERSRVREQUEST"))
(unless (find-package "SVG_ROS::OVERSRVRESPONSE")
  (make-package "SVG_ROS::OVERSRVRESPONSE"))

(in-package "ROS")





(defclass svg_ros::OverSrvRequest
  :super ros::object
  :slots (_over_flg ))

(defmethod svg_ros::OverSrvRequest
  (:init
   (&key
    ((:over_flg __over_flg) 0)
    )
   (send-super :init)
   (setq _over_flg (round __over_flg))
   self)
  (:over_flg
   (&optional __over_flg)
   (if __over_flg (setq _over_flg __over_flg)) _over_flg)
  (:serialization-length
   ()
   (+
    ;; int32 _over_flg
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _over_flg
       (write-long _over_flg s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _over_flg
     (setq _over_flg (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass svg_ros::OverSrvResponse
  :super ros::object
  :slots (_answer ))

(defmethod svg_ros::OverSrvResponse
  (:init
   (&key
    ((:answer __answer) 0)
    )
   (send-super :init)
   (setq _answer (round __answer))
   self)
  (:answer
   (&optional __answer)
   (if __answer (setq _answer __answer)) _answer)
  (:serialization-length
   ()
   (+
    ;; int32 _answer
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _answer
       (write-long _answer s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _answer
     (setq _answer (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass svg_ros::OverSrv
  :super ros::object
  :slots ())

(setf (get svg_ros::OverSrv :md5sum-) "ed5c22717a93863499734f374ca8e9a3")
(setf (get svg_ros::OverSrv :datatype-) "svg_ros/OverSrv")
(setf (get svg_ros::OverSrv :request) svg_ros::OverSrvRequest)
(setf (get svg_ros::OverSrv :response) svg_ros::OverSrvResponse)

(defmethod svg_ros::OverSrvRequest
  (:response () (instance svg_ros::OverSrvResponse :init)))

(setf (get svg_ros::OverSrvRequest :md5sum-) "ed5c22717a93863499734f374ca8e9a3")
(setf (get svg_ros::OverSrvRequest :datatype-) "svg_ros/OverSrvRequest")
(setf (get svg_ros::OverSrvRequest :definition-)
      "int32 over_flg
---
int32 answer
")

(setf (get svg_ros::OverSrvResponse :md5sum-) "ed5c22717a93863499734f374ca8e9a3")
(setf (get svg_ros::OverSrvResponse :datatype-) "svg_ros/OverSrvResponse")
(setf (get svg_ros::OverSrvResponse :definition-)
      "int32 over_flg
---
int32 answer
")



(provide :svg_ros/OverSrv "ed5c22717a93863499734f374ca8e9a3")



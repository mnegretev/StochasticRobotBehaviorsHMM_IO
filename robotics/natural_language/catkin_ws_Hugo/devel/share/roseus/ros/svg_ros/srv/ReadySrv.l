;; Auto-generated. Do not edit!


(when (boundp 'svg_ros::ReadySrv)
  (if (not (find-package "SVG_ROS"))
    (make-package "SVG_ROS"))
  (shadow 'ReadySrv (find-package "SVG_ROS")))
(unless (find-package "SVG_ROS::READYSRV")
  (make-package "SVG_ROS::READYSRV"))
(unless (find-package "SVG_ROS::READYSRVREQUEST")
  (make-package "SVG_ROS::READYSRVREQUEST"))
(unless (find-package "SVG_ROS::READYSRVRESPONSE")
  (make-package "SVG_ROS::READYSRVRESPONSE"))

(in-package "ROS")





(defclass svg_ros::ReadySrvRequest
  :super ros::object
  :slots (_ready ))

(defmethod svg_ros::ReadySrvRequest
  (:init
   (&key
    ((:ready __ready) 0)
    )
   (send-super :init)
   (setq _ready (round __ready))
   self)
  (:ready
   (&optional __ready)
   (if __ready (setq _ready __ready)) _ready)
  (:serialization-length
   ()
   (+
    ;; int32 _ready
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _ready
       (write-long _ready s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _ready
     (setq _ready (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass svg_ros::ReadySrvResponse
  :super ros::object
  :slots (_answer ))

(defmethod svg_ros::ReadySrvResponse
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

(defclass svg_ros::ReadySrv
  :super ros::object
  :slots ())

(setf (get svg_ros::ReadySrv :md5sum-) "481bf4557884a8ae5f3651bd90c8f18f")
(setf (get svg_ros::ReadySrv :datatype-) "svg_ros/ReadySrv")
(setf (get svg_ros::ReadySrv :request) svg_ros::ReadySrvRequest)
(setf (get svg_ros::ReadySrv :response) svg_ros::ReadySrvResponse)

(defmethod svg_ros::ReadySrvRequest
  (:response () (instance svg_ros::ReadySrvResponse :init)))

(setf (get svg_ros::ReadySrvRequest :md5sum-) "481bf4557884a8ae5f3651bd90c8f18f")
(setf (get svg_ros::ReadySrvRequest :datatype-) "svg_ros/ReadySrvRequest")
(setf (get svg_ros::ReadySrvRequest :definition-)
      "int32 ready
---
int32 answer

")

(setf (get svg_ros::ReadySrvResponse :md5sum-) "481bf4557884a8ae5f3651bd90c8f18f")
(setf (get svg_ros::ReadySrvResponse :datatype-) "svg_ros/ReadySrvResponse")
(setf (get svg_ros::ReadySrvResponse :definition-)
      "int32 ready
---
int32 answer

")



(provide :svg_ros/ReadySrv "481bf4557884a8ae5f3651bd90c8f18f")



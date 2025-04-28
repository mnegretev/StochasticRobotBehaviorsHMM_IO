;; Auto-generated. Do not edit!


(when (boundp 'svg_ros::LightRealSrv)
  (if (not (find-package "SVG_ROS"))
    (make-package "SVG_ROS"))
  (shadow 'LightRealSrv (find-package "SVG_ROS")))
(unless (find-package "SVG_ROS::LIGHTREALSRV")
  (make-package "SVG_ROS::LIGHTREALSRV"))
(unless (find-package "SVG_ROS::LIGHTREALSRVREQUEST")
  (make-package "SVG_ROS::LIGHTREALSRVREQUEST"))
(unless (find-package "SVG_ROS::LIGHTREALSRVRESPONSE")
  (make-package "SVG_ROS::LIGHTREALSRVRESPONSE"))

(in-package "ROS")





(defclass svg_ros::LightRealSrvRequest
  :super ros::object
  :slots (_req ))

(defmethod svg_ros::LightRealSrvRequest
  (:init
   (&key
    ((:req __req) 0)
    )
   (send-super :init)
   (setq _req (round __req))
   self)
  (:req
   (&optional __req)
   (if __req (setq _req __req)) _req)
  (:serialization-length
   ()
   (+
    ;; int32 _req
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _req
       (write-long _req s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _req
     (setq _req (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass svg_ros::LightRealSrvResponse
  :super ros::object
  :slots (_quantized_attraction _quantized_intensity ))

(defmethod svg_ros::LightRealSrvResponse
  (:init
   (&key
    ((:quantized_attraction __quantized_attraction) 0)
    ((:quantized_intensity __quantized_intensity) 0)
    )
   (send-super :init)
   (setq _quantized_attraction (round __quantized_attraction))
   (setq _quantized_intensity (round __quantized_intensity))
   self)
  (:quantized_attraction
   (&optional __quantized_attraction)
   (if __quantized_attraction (setq _quantized_attraction __quantized_attraction)) _quantized_attraction)
  (:quantized_intensity
   (&optional __quantized_intensity)
   (if __quantized_intensity (setq _quantized_intensity __quantized_intensity)) _quantized_intensity)
  (:serialization-length
   ()
   (+
    ;; int32 _quantized_attraction
    4
    ;; int32 _quantized_intensity
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _quantized_attraction
       (write-long _quantized_attraction s)
     ;; int32 _quantized_intensity
       (write-long _quantized_intensity s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _quantized_attraction
     (setq _quantized_attraction (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _quantized_intensity
     (setq _quantized_intensity (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass svg_ros::LightRealSrv
  :super ros::object
  :slots ())

(setf (get svg_ros::LightRealSrv :md5sum-) "880a7d45ae2b2447f4ed19a09614d287")
(setf (get svg_ros::LightRealSrv :datatype-) "svg_ros/LightRealSrv")
(setf (get svg_ros::LightRealSrv :request) svg_ros::LightRealSrvRequest)
(setf (get svg_ros::LightRealSrv :response) svg_ros::LightRealSrvResponse)

(defmethod svg_ros::LightRealSrvRequest
  (:response () (instance svg_ros::LightRealSrvResponse :init)))

(setf (get svg_ros::LightRealSrvRequest :md5sum-) "880a7d45ae2b2447f4ed19a09614d287")
(setf (get svg_ros::LightRealSrvRequest :datatype-) "svg_ros/LightRealSrvRequest")
(setf (get svg_ros::LightRealSrvRequest :definition-)
      "int32 req
---
int32 quantized_attraction
int32 quantized_intensity
")

(setf (get svg_ros::LightRealSrvResponse :md5sum-) "880a7d45ae2b2447f4ed19a09614d287")
(setf (get svg_ros::LightRealSrvResponse :datatype-) "svg_ros/LightRealSrvResponse")
(setf (get svg_ros::LightRealSrvResponse :definition-)
      "int32 req
---
int32 quantized_attraction
int32 quantized_intensity
")



(provide :svg_ros/LightRealSrv "880a7d45ae2b2447f4ed19a09614d287")



;; Auto-generated. Do not edit!


(when (boundp 'svg_ros::LightSrv)
  (if (not (find-package "SVG_ROS"))
    (make-package "SVG_ROS"))
  (shadow 'LightSrv (find-package "SVG_ROS")))
(unless (find-package "SVG_ROS::LIGHTSRV")
  (make-package "SVG_ROS::LIGHTSRV"))
(unless (find-package "SVG_ROS::LIGHTSRVREQUEST")
  (make-package "SVG_ROS::LIGHTSRVREQUEST"))
(unless (find-package "SVG_ROS::LIGHTSRVRESPONSE")
  (make-package "SVG_ROS::LIGHTSRVRESPONSE"))

(in-package "ROS")





(defclass svg_ros::LightSrvRequest
  :super ros::object
  :slots (_req _coord_x _coord_y _coord_ang ))

(defmethod svg_ros::LightSrvRequest
  (:init
   (&key
    ((:req __req) 0)
    ((:coord_x __coord_x) 0.0)
    ((:coord_y __coord_y) 0.0)
    ((:coord_ang __coord_ang) 0.0)
    )
   (send-super :init)
   (setq _req (round __req))
   (setq _coord_x (float __coord_x))
   (setq _coord_y (float __coord_y))
   (setq _coord_ang (float __coord_ang))
   self)
  (:req
   (&optional __req)
   (if __req (setq _req __req)) _req)
  (:coord_x
   (&optional __coord_x)
   (if __coord_x (setq _coord_x __coord_x)) _coord_x)
  (:coord_y
   (&optional __coord_y)
   (if __coord_y (setq _coord_y __coord_y)) _coord_y)
  (:coord_ang
   (&optional __coord_ang)
   (if __coord_ang (setq _coord_ang __coord_ang)) _coord_ang)
  (:serialization-length
   ()
   (+
    ;; int32 _req
    4
    ;; float32 _coord_x
    4
    ;; float32 _coord_y
    4
    ;; float32 _coord_ang
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _req
       (write-long _req s)
     ;; float32 _coord_x
       (sys::poke _coord_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _coord_y
       (sys::poke _coord_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _coord_ang
       (sys::poke _coord_ang (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _req
     (setq _req (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _coord_x
     (setq _coord_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _coord_y
     (setq _coord_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _coord_ang
     (setq _coord_ang (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass svg_ros::LightSrvResponse
  :super ros::object
  :slots (_flag_dest _x _y _quantized_attraction _quantized_intensity ))

(defmethod svg_ros::LightSrvResponse
  (:init
   (&key
    ((:flag_dest __flag_dest) 0)
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:quantized_attraction __quantized_attraction) 0)
    ((:quantized_intensity __quantized_intensity) 0)
    )
   (send-super :init)
   (setq _flag_dest (round __flag_dest))
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _quantized_attraction (round __quantized_attraction))
   (setq _quantized_intensity (round __quantized_intensity))
   self)
  (:flag_dest
   (&optional __flag_dest)
   (if __flag_dest (setq _flag_dest __flag_dest)) _flag_dest)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:quantized_attraction
   (&optional __quantized_attraction)
   (if __quantized_attraction (setq _quantized_attraction __quantized_attraction)) _quantized_attraction)
  (:quantized_intensity
   (&optional __quantized_intensity)
   (if __quantized_intensity (setq _quantized_intensity __quantized_intensity)) _quantized_intensity)
  (:serialization-length
   ()
   (+
    ;; int32 _flag_dest
    4
    ;; float32 _x
    4
    ;; float32 _y
    4
    ;; int32 _quantized_attraction
    4
    ;; int32 _quantized_intensity
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _flag_dest
       (write-long _flag_dest s)
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int32 _quantized_attraction
       (write-long _quantized_attraction s)
     ;; int32 _quantized_intensity
       (write-long _quantized_intensity s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _flag_dest
     (setq _flag_dest (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int32 _quantized_attraction
     (setq _quantized_attraction (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _quantized_intensity
     (setq _quantized_intensity (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass svg_ros::LightSrv
  :super ros::object
  :slots ())

(setf (get svg_ros::LightSrv :md5sum-) "eba6c43e856487b2b6ad559a0d0f124d")
(setf (get svg_ros::LightSrv :datatype-) "svg_ros/LightSrv")
(setf (get svg_ros::LightSrv :request) svg_ros::LightSrvRequest)
(setf (get svg_ros::LightSrv :response) svg_ros::LightSrvResponse)

(defmethod svg_ros::LightSrvRequest
  (:response () (instance svg_ros::LightSrvResponse :init)))

(setf (get svg_ros::LightSrvRequest :md5sum-) "eba6c43e856487b2b6ad559a0d0f124d")
(setf (get svg_ros::LightSrvRequest :datatype-) "svg_ros/LightSrvRequest")
(setf (get svg_ros::LightSrvRequest :definition-)
      "int32 req
float32 coord_x
float32 coord_y
float32 coord_ang
---
int32 flag_dest
float32 x
float32 y
int32 quantized_attraction
int32 quantized_intensity
")

(setf (get svg_ros::LightSrvResponse :md5sum-) "eba6c43e856487b2b6ad559a0d0f124d")
(setf (get svg_ros::LightSrvResponse :datatype-) "svg_ros/LightSrvResponse")
(setf (get svg_ros::LightSrvResponse :definition-)
      "int32 req
float32 coord_x
float32 coord_y
float32 coord_ang
---
int32 flag_dest
float32 x
float32 y
int32 quantized_attraction
int32 quantized_intensity
")



(provide :svg_ros/LightSrv "eba6c43e856487b2b6ad559a0d0f124d")



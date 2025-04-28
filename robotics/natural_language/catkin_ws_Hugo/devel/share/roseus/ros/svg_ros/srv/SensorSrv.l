;; Auto-generated. Do not edit!


(when (boundp 'svg_ros::SensorSrv)
  (if (not (find-package "SVG_ROS"))
    (make-package "SVG_ROS"))
  (shadow 'SensorSrv (find-package "SVG_ROS")))
(unless (find-package "SVG_ROS::SENSORSRV")
  (make-package "SVG_ROS::SENSORSRV"))
(unless (find-package "SVG_ROS::SENSORSRVREQUEST")
  (make-package "SVG_ROS::SENSORSRVREQUEST"))
(unless (find-package "SVG_ROS::SENSORSRVRESPONSE")
  (make-package "SVG_ROS::SENSORSRVRESPONSE"))

(in-package "ROS")





(defclass svg_ros::SensorSrvRequest
  :super ros::object
  :slots (_coord_x _coord_y _coord_ang ))

(defmethod svg_ros::SensorSrvRequest
  (:init
   (&key
    ((:coord_x __coord_x) 0.0)
    ((:coord_y __coord_y) 0.0)
    ((:coord_ang __coord_ang) 0.0)
    )
   (send-super :init)
   (setq _coord_x (float __coord_x))
   (setq _coord_y (float __coord_y))
   (setq _coord_ang (float __coord_ang))
   self)
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
   ;; float32 _coord_x
     (setq _coord_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _coord_y
     (setq _coord_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _coord_ang
     (setq _coord_ang (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass svg_ros::SensorSrvResponse
  :super ros::object
  :slots (_flag _region _x _y _theta _sensors _num_sensors _sensor ))

(defmethod svg_ros::SensorSrvResponse
  (:init
   (&key
    ((:flag __flag) 0)
    ((:region __region) 0)
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:theta __theta) 0.0)
    ((:sensors __sensors) (make-array 500 :initial-element 0.0 :element-type :float))
    ((:num_sensors __num_sensors) 0)
    ((:sensor __sensor) "")
    )
   (send-super :init)
   (setq _flag (round __flag))
   (setq _region (round __region))
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _theta (float __theta))
   (setq _sensors __sensors)
   (setq _num_sensors (round __num_sensors))
   (setq _sensor (string __sensor))
   self)
  (:flag
   (&optional __flag)
   (if __flag (setq _flag __flag)) _flag)
  (:region
   (&optional __region)
   (if __region (setq _region __region)) _region)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:theta
   (&optional __theta)
   (if __theta (setq _theta __theta)) _theta)
  (:sensors
   (&optional __sensors)
   (if __sensors (setq _sensors __sensors)) _sensors)
  (:num_sensors
   (&optional __num_sensors)
   (if __num_sensors (setq _num_sensors __num_sensors)) _num_sensors)
  (:sensor
   (&optional __sensor)
   (if __sensor (setq _sensor __sensor)) _sensor)
  (:serialization-length
   ()
   (+
    ;; int32 _flag
    4
    ;; int32 _region
    4
    ;; float32 _x
    4
    ;; float32 _y
    4
    ;; float32 _theta
    4
    ;; float32[500] _sensors
    (* 4    500)
    ;; int32 _num_sensors
    4
    ;; string _sensor
    4 (length _sensor)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _flag
       (write-long _flag s)
     ;; int32 _region
       (write-long _region s)
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _theta
       (sys::poke _theta (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32[500] _sensors
     (dotimes (i 500)
       (sys::poke (elt _sensors i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; int32 _num_sensors
       (write-long _num_sensors s)
     ;; string _sensor
       (write-long (length _sensor) s) (princ _sensor s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _flag
     (setq _flag (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _region
     (setq _region (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _theta
     (setq _theta (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32[500] _sensors
   (dotimes (i (length _sensors))
     (setf (elt _sensors i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; int32 _num_sensors
     (setq _num_sensors (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; string _sensor
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _sensor (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass svg_ros::SensorSrv
  :super ros::object
  :slots ())

(setf (get svg_ros::SensorSrv :md5sum-) "b3a08c1472f241ab9eb4c0932b73ff18")
(setf (get svg_ros::SensorSrv :datatype-) "svg_ros/SensorSrv")
(setf (get svg_ros::SensorSrv :request) svg_ros::SensorSrvRequest)
(setf (get svg_ros::SensorSrv :response) svg_ros::SensorSrvResponse)

(defmethod svg_ros::SensorSrvRequest
  (:response () (instance svg_ros::SensorSrvResponse :init)))

(setf (get svg_ros::SensorSrvRequest :md5sum-) "b3a08c1472f241ab9eb4c0932b73ff18")
(setf (get svg_ros::SensorSrvRequest :datatype-) "svg_ros/SensorSrvRequest")
(setf (get svg_ros::SensorSrvRequest :definition-)
      "float32 coord_x
float32 coord_y
float32 coord_ang
---
int32 flag
int32 region
float32 x
float32 y
float32 theta
float32[500] sensors
int32 num_sensors
string sensor

")

(setf (get svg_ros::SensorSrvResponse :md5sum-) "b3a08c1472f241ab9eb4c0932b73ff18")
(setf (get svg_ros::SensorSrvResponse :datatype-) "svg_ros/SensorSrvResponse")
(setf (get svg_ros::SensorSrvResponse :definition-)
      "float32 coord_x
float32 coord_y
float32 coord_ang
---
int32 flag
int32 region
float32 x
float32 y
float32 theta
float32[500] sensors
int32 num_sensors
string sensor

")



(provide :svg_ros/SensorSrv "b3a08c1472f241ab9eb4c0932b73ff18")



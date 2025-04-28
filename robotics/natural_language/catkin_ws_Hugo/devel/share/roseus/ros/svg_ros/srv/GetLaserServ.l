;; Auto-generated. Do not edit!


(when (boundp 'svg_ros::GetLaserServ)
  (if (not (find-package "SVG_ROS"))
    (make-package "SVG_ROS"))
  (shadow 'GetLaserServ (find-package "SVG_ROS")))
(unless (find-package "SVG_ROS::GETLASERSERV")
  (make-package "SVG_ROS::GETLASERSERV"))
(unless (find-package "SVG_ROS::GETLASERSERVREQUEST")
  (make-package "SVG_ROS::GETLASERSERVREQUEST"))
(unless (find-package "SVG_ROS::GETLASERSERVRESPONSE")
  (make-package "SVG_ROS::GETLASERSERVRESPONSE"))

(in-package "ROS")





(defclass svg_ros::GetLaserServRequest
  :super ros::object
  :slots (_param _num_sensors _range _init_angle ))

(defmethod svg_ros::GetLaserServRequest
  (:init
   (&key
    ((:param __param) "")
    ((:num_sensors __num_sensors) 0)
    ((:range __range) 0.0)
    ((:init_angle __init_angle) 0.0)
    )
   (send-super :init)
   (setq _param (string __param))
   (setq _num_sensors (round __num_sensors))
   (setq _range (float __range))
   (setq _init_angle (float __init_angle))
   self)
  (:param
   (&optional __param)
   (if __param (setq _param __param)) _param)
  (:num_sensors
   (&optional __num_sensors)
   (if __num_sensors (setq _num_sensors __num_sensors)) _num_sensors)
  (:range
   (&optional __range)
   (if __range (setq _range __range)) _range)
  (:init_angle
   (&optional __init_angle)
   (if __init_angle (setq _init_angle __init_angle)) _init_angle)
  (:serialization-length
   ()
   (+
    ;; string _param
    4 (length _param)
    ;; int32 _num_sensors
    4
    ;; float32 _range
    4
    ;; float32 _init_angle
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _param
       (write-long (length _param) s) (princ _param s)
     ;; int32 _num_sensors
       (write-long _num_sensors s)
     ;; float32 _range
       (sys::poke _range (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _init_angle
       (sys::poke _init_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _param
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _param (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int32 _num_sensors
     (setq _num_sensors (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _range
     (setq _range (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _init_angle
     (setq _init_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass svg_ros::GetLaserServResponse
  :super ros::object
  :slots (_answer _sensors ))

(defmethod svg_ros::GetLaserServResponse
  (:init
   (&key
    ((:answer __answer) "")
    ((:sensors __sensors) (make-array 700 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _answer (string __answer))
   (setq _sensors __sensors)
   self)
  (:answer
   (&optional __answer)
   (if __answer (setq _answer __answer)) _answer)
  (:sensors
   (&optional __sensors)
   (if __sensors (setq _sensors __sensors)) _sensors)
  (:serialization-length
   ()
   (+
    ;; string _answer
    4 (length _answer)
    ;; float32[700] _sensors
    (* 4    700)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _answer
       (write-long (length _answer) s) (princ _answer s)
     ;; float32[700] _sensors
     (dotimes (i 700)
       (sys::poke (elt _sensors i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _answer
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _answer (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float32[700] _sensors
   (dotimes (i (length _sensors))
     (setf (elt _sensors i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;;
   self)
  )

(defclass svg_ros::GetLaserServ
  :super ros::object
  :slots ())

(setf (get svg_ros::GetLaserServ :md5sum-) "51e72a4807785eaabb7cee7d2a968e03")
(setf (get svg_ros::GetLaserServ :datatype-) "svg_ros/GetLaserServ")
(setf (get svg_ros::GetLaserServ :request) svg_ros::GetLaserServRequest)
(setf (get svg_ros::GetLaserServ :response) svg_ros::GetLaserServResponse)

(defmethod svg_ros::GetLaserServRequest
  (:response () (instance svg_ros::GetLaserServResponse :init)))

(setf (get svg_ros::GetLaserServRequest :md5sum-) "51e72a4807785eaabb7cee7d2a968e03")
(setf (get svg_ros::GetLaserServRequest :datatype-) "svg_ros/GetLaserServRequest")
(setf (get svg_ros::GetLaserServRequest :definition-)
      "string param
int32 num_sensors
float32 range
float32 init_angle
---
string answer
float32[700] sensors

")

(setf (get svg_ros::GetLaserServResponse :md5sum-) "51e72a4807785eaabb7cee7d2a968e03")
(setf (get svg_ros::GetLaserServResponse :datatype-) "svg_ros/GetLaserServResponse")
(setf (get svg_ros::GetLaserServResponse :definition-)
      "string param
int32 num_sensors
float32 range
float32 init_angle
---
string answer
float32[700] sensors

")



(provide :svg_ros/GetLaserServ "51e72a4807785eaabb7cee7d2a968e03")



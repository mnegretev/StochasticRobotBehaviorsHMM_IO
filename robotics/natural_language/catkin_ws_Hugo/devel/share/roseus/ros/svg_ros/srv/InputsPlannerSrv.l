;; Auto-generated. Do not edit!


(when (boundp 'svg_ros::InputsPlannerSrv)
  (if (not (find-package "SVG_ROS"))
    (make-package "SVG_ROS"))
  (shadow 'InputsPlannerSrv (find-package "SVG_ROS")))
(unless (find-package "SVG_ROS::INPUTSPLANNERSRV")
  (make-package "SVG_ROS::INPUTSPLANNERSRV"))
(unless (find-package "SVG_ROS::INPUTSPLANNERSRVREQUEST")
  (make-package "SVG_ROS::INPUTSPLANNERSRVREQUEST"))
(unless (find-package "SVG_ROS::INPUTSPLANNERSRVRESPONSE")
  (make-package "SVG_ROS::INPUTSPLANNERSRVRESPONSE"))

(in-package "ROS")





(defclass svg_ros::InputsPlannerSrvRequest
  :super ros::object
  :slots (_success ))

(defmethod svg_ros::InputsPlannerSrvRequest
  (:init
   (&key
    ((:success __success) 0)
    )
   (send-super :init)
   (setq _success (round __success))
   self)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; int32 _success
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _success
       (write-long _success s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _success
     (setq _success (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass svg_ros::InputsPlannerSrvResponse
  :super ros::object
  :slots (_origin_x _origin_y _origin_angRob _dest_x _dest_y _sensorBool _num_sensorsInt _angle_sensor_orig _range_angleRob _radiusRob _advance _max_angle _num_steps _select _largest_sensor _pathNAme _fileNAme _flgGUI _flg_noise ))

(defmethod svg_ros::InputsPlannerSrvResponse
  (:init
   (&key
    ((:origin_x __origin_x) 0.0)
    ((:origin_y __origin_y) 0.0)
    ((:origin_angRob __origin_angRob) 0.0)
    ((:dest_x __dest_x) 0.0)
    ((:dest_y __dest_y) 0.0)
    ((:sensorBool __sensorBool) "")
    ((:num_sensorsInt __num_sensorsInt) 0)
    ((:angle_sensor_orig __angle_sensor_orig) 0.0)
    ((:range_angleRob __range_angleRob) 0.0)
    ((:radiusRob __radiusRob) 0.0)
    ((:advance __advance) 0.0)
    ((:max_angle __max_angle) 0.0)
    ((:num_steps __num_steps) 0)
    ((:select __select) 0)
    ((:largest_sensor __largest_sensor) 0.0)
    ((:pathNAme __pathNAme) "")
    ((:fileNAme __fileNAme) "")
    ((:flgGUI __flgGUI) 0)
    ((:flg_noise __flg_noise) 0)
    )
   (send-super :init)
   (setq _origin_x (float __origin_x))
   (setq _origin_y (float __origin_y))
   (setq _origin_angRob (float __origin_angRob))
   (setq _dest_x (float __dest_x))
   (setq _dest_y (float __dest_y))
   (setq _sensorBool (string __sensorBool))
   (setq _num_sensorsInt (round __num_sensorsInt))
   (setq _angle_sensor_orig (float __angle_sensor_orig))
   (setq _range_angleRob (float __range_angleRob))
   (setq _radiusRob (float __radiusRob))
   (setq _advance (float __advance))
   (setq _max_angle (float __max_angle))
   (setq _num_steps (round __num_steps))
   (setq _select (round __select))
   (setq _largest_sensor (float __largest_sensor))
   (setq _pathNAme (string __pathNAme))
   (setq _fileNAme (string __fileNAme))
   (setq _flgGUI (round __flgGUI))
   (setq _flg_noise (round __flg_noise))
   self)
  (:origin_x
   (&optional __origin_x)
   (if __origin_x (setq _origin_x __origin_x)) _origin_x)
  (:origin_y
   (&optional __origin_y)
   (if __origin_y (setq _origin_y __origin_y)) _origin_y)
  (:origin_angRob
   (&optional __origin_angRob)
   (if __origin_angRob (setq _origin_angRob __origin_angRob)) _origin_angRob)
  (:dest_x
   (&optional __dest_x)
   (if __dest_x (setq _dest_x __dest_x)) _dest_x)
  (:dest_y
   (&optional __dest_y)
   (if __dest_y (setq _dest_y __dest_y)) _dest_y)
  (:sensorBool
   (&optional __sensorBool)
   (if __sensorBool (setq _sensorBool __sensorBool)) _sensorBool)
  (:num_sensorsInt
   (&optional __num_sensorsInt)
   (if __num_sensorsInt (setq _num_sensorsInt __num_sensorsInt)) _num_sensorsInt)
  (:angle_sensor_orig
   (&optional __angle_sensor_orig)
   (if __angle_sensor_orig (setq _angle_sensor_orig __angle_sensor_orig)) _angle_sensor_orig)
  (:range_angleRob
   (&optional __range_angleRob)
   (if __range_angleRob (setq _range_angleRob __range_angleRob)) _range_angleRob)
  (:radiusRob
   (&optional __radiusRob)
   (if __radiusRob (setq _radiusRob __radiusRob)) _radiusRob)
  (:advance
   (&optional __advance)
   (if __advance (setq _advance __advance)) _advance)
  (:max_angle
   (&optional __max_angle)
   (if __max_angle (setq _max_angle __max_angle)) _max_angle)
  (:num_steps
   (&optional __num_steps)
   (if __num_steps (setq _num_steps __num_steps)) _num_steps)
  (:select
   (&optional __select)
   (if __select (setq _select __select)) _select)
  (:largest_sensor
   (&optional __largest_sensor)
   (if __largest_sensor (setq _largest_sensor __largest_sensor)) _largest_sensor)
  (:pathNAme
   (&optional __pathNAme)
   (if __pathNAme (setq _pathNAme __pathNAme)) _pathNAme)
  (:fileNAme
   (&optional __fileNAme)
   (if __fileNAme (setq _fileNAme __fileNAme)) _fileNAme)
  (:flgGUI
   (&optional __flgGUI)
   (if __flgGUI (setq _flgGUI __flgGUI)) _flgGUI)
  (:flg_noise
   (&optional __flg_noise)
   (if __flg_noise (setq _flg_noise __flg_noise)) _flg_noise)
  (:serialization-length
   ()
   (+
    ;; float64 _origin_x
    8
    ;; float64 _origin_y
    8
    ;; float64 _origin_angRob
    8
    ;; float64 _dest_x
    8
    ;; float64 _dest_y
    8
    ;; string _sensorBool
    4 (length _sensorBool)
    ;; int32 _num_sensorsInt
    4
    ;; float64 _angle_sensor_orig
    8
    ;; float64 _range_angleRob
    8
    ;; float64 _radiusRob
    8
    ;; float64 _advance
    8
    ;; float64 _max_angle
    8
    ;; int32 _num_steps
    4
    ;; int32 _select
    4
    ;; float64 _largest_sensor
    8
    ;; string _pathNAme
    4 (length _pathNAme)
    ;; string _fileNAme
    4 (length _fileNAme)
    ;; int32 _flgGUI
    4
    ;; int32 _flg_noise
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _origin_x
       (sys::poke _origin_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _origin_y
       (sys::poke _origin_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _origin_angRob
       (sys::poke _origin_angRob (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dest_x
       (sys::poke _dest_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dest_y
       (sys::poke _dest_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; string _sensorBool
       (write-long (length _sensorBool) s) (princ _sensorBool s)
     ;; int32 _num_sensorsInt
       (write-long _num_sensorsInt s)
     ;; float64 _angle_sensor_orig
       (sys::poke _angle_sensor_orig (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _range_angleRob
       (sys::poke _range_angleRob (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _radiusRob
       (sys::poke _radiusRob (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _advance
       (sys::poke _advance (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _max_angle
       (sys::poke _max_angle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _num_steps
       (write-long _num_steps s)
     ;; int32 _select
       (write-long _select s)
     ;; float64 _largest_sensor
       (sys::poke _largest_sensor (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; string _pathNAme
       (write-long (length _pathNAme) s) (princ _pathNAme s)
     ;; string _fileNAme
       (write-long (length _fileNAme) s) (princ _fileNAme s)
     ;; int32 _flgGUI
       (write-long _flgGUI s)
     ;; int32 _flg_noise
       (write-long _flg_noise s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _origin_x
     (setq _origin_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _origin_y
     (setq _origin_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _origin_angRob
     (setq _origin_angRob (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dest_x
     (setq _dest_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dest_y
     (setq _dest_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; string _sensorBool
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _sensorBool (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int32 _num_sensorsInt
     (setq _num_sensorsInt (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _angle_sensor_orig
     (setq _angle_sensor_orig (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _range_angleRob
     (setq _range_angleRob (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _radiusRob
     (setq _radiusRob (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _advance
     (setq _advance (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _max_angle
     (setq _max_angle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _num_steps
     (setq _num_steps (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _select
     (setq _select (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _largest_sensor
     (setq _largest_sensor (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; string _pathNAme
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _pathNAme (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _fileNAme
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _fileNAme (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int32 _flgGUI
     (setq _flgGUI (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _flg_noise
     (setq _flg_noise (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass svg_ros::InputsPlannerSrv
  :super ros::object
  :slots ())

(setf (get svg_ros::InputsPlannerSrv :md5sum-) "188578d1209fb9d01aa3d1efc9744987")
(setf (get svg_ros::InputsPlannerSrv :datatype-) "svg_ros/InputsPlannerSrv")
(setf (get svg_ros::InputsPlannerSrv :request) svg_ros::InputsPlannerSrvRequest)
(setf (get svg_ros::InputsPlannerSrv :response) svg_ros::InputsPlannerSrvResponse)

(defmethod svg_ros::InputsPlannerSrvRequest
  (:response () (instance svg_ros::InputsPlannerSrvResponse :init)))

(setf (get svg_ros::InputsPlannerSrvRequest :md5sum-) "188578d1209fb9d01aa3d1efc9744987")
(setf (get svg_ros::InputsPlannerSrvRequest :datatype-) "svg_ros/InputsPlannerSrvRequest")
(setf (get svg_ros::InputsPlannerSrvRequest :definition-)
      "int32 success
---
float64 origin_x
float64 origin_y
float64 origin_angRob
float64 dest_x
float64 dest_y
string sensorBool
int32 num_sensorsInt
float64 angle_sensor_orig
float64 range_angleRob
float64 radiusRob
float64 advance
float64 max_angle
int32 num_steps
int32 select
float64 largest_sensor
string pathNAme
string fileNAme
int32 flgGUI
int32 flg_noise

")

(setf (get svg_ros::InputsPlannerSrvResponse :md5sum-) "188578d1209fb9d01aa3d1efc9744987")
(setf (get svg_ros::InputsPlannerSrvResponse :datatype-) "svg_ros/InputsPlannerSrvResponse")
(setf (get svg_ros::InputsPlannerSrvResponse :definition-)
      "int32 success
---
float64 origin_x
float64 origin_y
float64 origin_angRob
float64 dest_x
float64 dest_y
string sensorBool
int32 num_sensorsInt
float64 angle_sensor_orig
float64 range_angleRob
float64 radiusRob
float64 advance
float64 max_angle
int32 num_steps
int32 select
float64 largest_sensor
string pathNAme
string fileNAme
int32 flgGUI
int32 flg_noise

")



(provide :svg_ros/InputsPlannerSrv "188578d1209fb9d01aa3d1efc9744987")



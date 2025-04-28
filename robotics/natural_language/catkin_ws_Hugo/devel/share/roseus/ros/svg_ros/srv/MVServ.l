;; Auto-generated. Do not edit!


(when (boundp 'svg_ros::MVServ)
  (if (not (find-package "SVG_ROS"))
    (make-package "SVG_ROS"))
  (shadow 'MVServ (find-package "SVG_ROS")))
(unless (find-package "SVG_ROS::MVSERV")
  (make-package "SVG_ROS::MVSERV"))
(unless (find-package "SVG_ROS::MVSERVREQUEST")
  (make-package "SVG_ROS::MVSERVREQUEST"))
(unless (find-package "SVG_ROS::MVSERVRESPONSE")
  (make-package "SVG_ROS::MVSERVRESPONSE"))

(in-package "ROS")





(defclass svg_ros::MVServRequest
  :super ros::object
  :slots (_param _coord_x _coord_y _coord_ang ))

(defmethod svg_ros::MVServRequest
  (:init
   (&key
    ((:param __param) "")
    ((:coord_x __coord_x) 0.0)
    ((:coord_y __coord_y) 0.0)
    ((:coord_ang __coord_ang) 0.0)
    )
   (send-super :init)
   (setq _param (string __param))
   (setq _coord_x (float __coord_x))
   (setq _coord_y (float __coord_y))
   (setq _coord_ang (float __coord_ang))
   self)
  (:param
   (&optional __param)
   (if __param (setq _param __param)) _param)
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
    ;; string _param
    4 (length _param)
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
     ;; string _param
       (write-long (length _param) s) (princ _param s)
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
   ;; string _param
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _param (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float32 _coord_x
     (setq _coord_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _coord_y
     (setq _coord_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _coord_ang
     (setq _coord_ang (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass svg_ros::MVServResponse
  :super ros::object
  :slots (_answer ))

(defmethod svg_ros::MVServResponse
  (:init
   (&key
    ((:answer __answer) "")
    )
   (send-super :init)
   (setq _answer (string __answer))
   self)
  (:answer
   (&optional __answer)
   (if __answer (setq _answer __answer)) _answer)
  (:serialization-length
   ()
   (+
    ;; string _answer
    4 (length _answer)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _answer
       (write-long (length _answer) s) (princ _answer s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _answer
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _answer (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass svg_ros::MVServ
  :super ros::object
  :slots ())

(setf (get svg_ros::MVServ :md5sum-) "a5027d7394e6db0c454d58003c11ba06")
(setf (get svg_ros::MVServ :datatype-) "svg_ros/MVServ")
(setf (get svg_ros::MVServ :request) svg_ros::MVServRequest)
(setf (get svg_ros::MVServ :response) svg_ros::MVServResponse)

(defmethod svg_ros::MVServRequest
  (:response () (instance svg_ros::MVServResponse :init)))

(setf (get svg_ros::MVServRequest :md5sum-) "a5027d7394e6db0c454d58003c11ba06")
(setf (get svg_ros::MVServRequest :datatype-) "svg_ros/MVServRequest")
(setf (get svg_ros::MVServRequest :definition-)
      "string param
float32 coord_x
float32 coord_y
float32 coord_ang
---
string answer

")

(setf (get svg_ros::MVServResponse :md5sum-) "a5027d7394e6db0c454d58003c11ba06")
(setf (get svg_ros::MVServResponse :datatype-) "svg_ros/MVServResponse")
(setf (get svg_ros::MVServResponse :definition-)
      "string param
float32 coord_x
float32 coord_y
float32 coord_ang
---
string answer

")



(provide :svg_ros/MVServ "a5027d7394e6db0c454d58003c11ba06")



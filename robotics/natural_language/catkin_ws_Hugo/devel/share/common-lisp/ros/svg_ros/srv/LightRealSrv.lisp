; Auto-generated. Do not edit!


(cl:in-package svg_ros-srv)


;//! \htmlinclude LightRealSrv-request.msg.html

(cl:defclass <LightRealSrv-request> (roslisp-msg-protocol:ros-message)
  ((req
    :reader req
    :initarg :req
    :type cl:integer
    :initform 0))
)

(cl:defclass LightRealSrv-request (<LightRealSrv-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LightRealSrv-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LightRealSrv-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name svg_ros-srv:<LightRealSrv-request> is deprecated: use svg_ros-srv:LightRealSrv-request instead.")))

(cl:ensure-generic-function 'req-val :lambda-list '(m))
(cl:defmethod req-val ((m <LightRealSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader svg_ros-srv:req-val is deprecated.  Use svg_ros-srv:req instead.")
  (req m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LightRealSrv-request>) ostream)
  "Serializes a message object of type '<LightRealSrv-request>"
  (cl:let* ((signed (cl:slot-value msg 'req)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LightRealSrv-request>) istream)
  "Deserializes a message object of type '<LightRealSrv-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'req) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LightRealSrv-request>)))
  "Returns string type for a service object of type '<LightRealSrv-request>"
  "svg_ros/LightRealSrvRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LightRealSrv-request)))
  "Returns string type for a service object of type 'LightRealSrv-request"
  "svg_ros/LightRealSrvRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LightRealSrv-request>)))
  "Returns md5sum for a message object of type '<LightRealSrv-request>"
  "880a7d45ae2b2447f4ed19a09614d287")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LightRealSrv-request)))
  "Returns md5sum for a message object of type 'LightRealSrv-request"
  "880a7d45ae2b2447f4ed19a09614d287")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LightRealSrv-request>)))
  "Returns full string definition for message of type '<LightRealSrv-request>"
  (cl:format cl:nil "int32 req~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LightRealSrv-request)))
  "Returns full string definition for message of type 'LightRealSrv-request"
  (cl:format cl:nil "int32 req~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LightRealSrv-request>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LightRealSrv-request>))
  "Converts a ROS message object to a list"
  (cl:list 'LightRealSrv-request
    (cl:cons ':req (req msg))
))
;//! \htmlinclude LightRealSrv-response.msg.html

(cl:defclass <LightRealSrv-response> (roslisp-msg-protocol:ros-message)
  ((quantized_attraction
    :reader quantized_attraction
    :initarg :quantized_attraction
    :type cl:integer
    :initform 0)
   (quantized_intensity
    :reader quantized_intensity
    :initarg :quantized_intensity
    :type cl:integer
    :initform 0))
)

(cl:defclass LightRealSrv-response (<LightRealSrv-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LightRealSrv-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LightRealSrv-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name svg_ros-srv:<LightRealSrv-response> is deprecated: use svg_ros-srv:LightRealSrv-response instead.")))

(cl:ensure-generic-function 'quantized_attraction-val :lambda-list '(m))
(cl:defmethod quantized_attraction-val ((m <LightRealSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader svg_ros-srv:quantized_attraction-val is deprecated.  Use svg_ros-srv:quantized_attraction instead.")
  (quantized_attraction m))

(cl:ensure-generic-function 'quantized_intensity-val :lambda-list '(m))
(cl:defmethod quantized_intensity-val ((m <LightRealSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader svg_ros-srv:quantized_intensity-val is deprecated.  Use svg_ros-srv:quantized_intensity instead.")
  (quantized_intensity m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LightRealSrv-response>) ostream)
  "Serializes a message object of type '<LightRealSrv-response>"
  (cl:let* ((signed (cl:slot-value msg 'quantized_attraction)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'quantized_intensity)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LightRealSrv-response>) istream)
  "Deserializes a message object of type '<LightRealSrv-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'quantized_attraction) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'quantized_intensity) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LightRealSrv-response>)))
  "Returns string type for a service object of type '<LightRealSrv-response>"
  "svg_ros/LightRealSrvResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LightRealSrv-response)))
  "Returns string type for a service object of type 'LightRealSrv-response"
  "svg_ros/LightRealSrvResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LightRealSrv-response>)))
  "Returns md5sum for a message object of type '<LightRealSrv-response>"
  "880a7d45ae2b2447f4ed19a09614d287")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LightRealSrv-response)))
  "Returns md5sum for a message object of type 'LightRealSrv-response"
  "880a7d45ae2b2447f4ed19a09614d287")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LightRealSrv-response>)))
  "Returns full string definition for message of type '<LightRealSrv-response>"
  (cl:format cl:nil "int32 quantized_attraction~%int32 quantized_intensity~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LightRealSrv-response)))
  "Returns full string definition for message of type 'LightRealSrv-response"
  (cl:format cl:nil "int32 quantized_attraction~%int32 quantized_intensity~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LightRealSrv-response>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LightRealSrv-response>))
  "Converts a ROS message object to a list"
  (cl:list 'LightRealSrv-response
    (cl:cons ':quantized_attraction (quantized_attraction msg))
    (cl:cons ':quantized_intensity (quantized_intensity msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'LightRealSrv)))
  'LightRealSrv-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'LightRealSrv)))
  'LightRealSrv-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LightRealSrv)))
  "Returns string type for a service object of type '<LightRealSrv>"
  "svg_ros/LightRealSrv")

(cl:in-package :asdf)

(defsystem "svg_ros-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "ReadySrv" :depends-on ("_package_ReadySrv"))
    (:file "_package_ReadySrv" :depends-on ("_package"))
    (:file "OverSrv" :depends-on ("_package_OverSrv"))
    (:file "_package_OverSrv" :depends-on ("_package"))
    (:file "InputsPlannerSrv" :depends-on ("_package_InputsPlannerSrv"))
    (:file "_package_InputsPlannerSrv" :depends-on ("_package"))
    (:file "LightRealSrv" :depends-on ("_package_LightRealSrv"))
    (:file "_package_LightRealSrv" :depends-on ("_package"))
    (:file "SensorSrv" :depends-on ("_package_SensorSrv"))
    (:file "_package_SensorSrv" :depends-on ("_package"))
    (:file "MVServ" :depends-on ("_package_MVServ"))
    (:file "_package_MVServ" :depends-on ("_package"))
    (:file "InputsSrv" :depends-on ("_package_InputsSrv"))
    (:file "_package_InputsSrv" :depends-on ("_package"))
    (:file "GetLaserServ" :depends-on ("_package_GetLaserServ"))
    (:file "_package_GetLaserServ" :depends-on ("_package"))
    (:file "LightSrv" :depends-on ("_package_LightSrv"))
    (:file "_package_LightSrv" :depends-on ("_package"))
  ))
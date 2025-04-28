// Auto-generated. Do not edit!

// (in-package svg_ros.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class InputsPlannerSrvRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.success = null;
    }
    else {
      if (initObj.hasOwnProperty('success')) {
        this.success = initObj.success
      }
      else {
        this.success = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type InputsPlannerSrvRequest
    // Serialize message field [success]
    bufferOffset = _serializer.int32(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type InputsPlannerSrvRequest
    let len;
    let data = new InputsPlannerSrvRequest(null);
    // Deserialize message field [success]
    data.success = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/InputsPlannerSrvRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3c2bcf2ff0894cb3058b1bf4c8c4175a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 success
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new InputsPlannerSrvRequest(null);
    if (msg.success !== undefined) {
      resolved.success = msg.success;
    }
    else {
      resolved.success = 0
    }

    return resolved;
    }
};

class InputsPlannerSrvResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.origin_x = null;
      this.origin_y = null;
      this.origin_angRob = null;
      this.dest_x = null;
      this.dest_y = null;
      this.sensorBool = null;
      this.num_sensorsInt = null;
      this.angle_sensor_orig = null;
      this.range_angleRob = null;
      this.radiusRob = null;
      this.advance = null;
      this.max_angle = null;
      this.num_steps = null;
      this.select = null;
      this.largest_sensor = null;
      this.pathNAme = null;
      this.fileNAme = null;
      this.flgGUI = null;
      this.flg_noise = null;
    }
    else {
      if (initObj.hasOwnProperty('origin_x')) {
        this.origin_x = initObj.origin_x
      }
      else {
        this.origin_x = 0.0;
      }
      if (initObj.hasOwnProperty('origin_y')) {
        this.origin_y = initObj.origin_y
      }
      else {
        this.origin_y = 0.0;
      }
      if (initObj.hasOwnProperty('origin_angRob')) {
        this.origin_angRob = initObj.origin_angRob
      }
      else {
        this.origin_angRob = 0.0;
      }
      if (initObj.hasOwnProperty('dest_x')) {
        this.dest_x = initObj.dest_x
      }
      else {
        this.dest_x = 0.0;
      }
      if (initObj.hasOwnProperty('dest_y')) {
        this.dest_y = initObj.dest_y
      }
      else {
        this.dest_y = 0.0;
      }
      if (initObj.hasOwnProperty('sensorBool')) {
        this.sensorBool = initObj.sensorBool
      }
      else {
        this.sensorBool = '';
      }
      if (initObj.hasOwnProperty('num_sensorsInt')) {
        this.num_sensorsInt = initObj.num_sensorsInt
      }
      else {
        this.num_sensorsInt = 0;
      }
      if (initObj.hasOwnProperty('angle_sensor_orig')) {
        this.angle_sensor_orig = initObj.angle_sensor_orig
      }
      else {
        this.angle_sensor_orig = 0.0;
      }
      if (initObj.hasOwnProperty('range_angleRob')) {
        this.range_angleRob = initObj.range_angleRob
      }
      else {
        this.range_angleRob = 0.0;
      }
      if (initObj.hasOwnProperty('radiusRob')) {
        this.radiusRob = initObj.radiusRob
      }
      else {
        this.radiusRob = 0.0;
      }
      if (initObj.hasOwnProperty('advance')) {
        this.advance = initObj.advance
      }
      else {
        this.advance = 0.0;
      }
      if (initObj.hasOwnProperty('max_angle')) {
        this.max_angle = initObj.max_angle
      }
      else {
        this.max_angle = 0.0;
      }
      if (initObj.hasOwnProperty('num_steps')) {
        this.num_steps = initObj.num_steps
      }
      else {
        this.num_steps = 0;
      }
      if (initObj.hasOwnProperty('select')) {
        this.select = initObj.select
      }
      else {
        this.select = 0;
      }
      if (initObj.hasOwnProperty('largest_sensor')) {
        this.largest_sensor = initObj.largest_sensor
      }
      else {
        this.largest_sensor = 0.0;
      }
      if (initObj.hasOwnProperty('pathNAme')) {
        this.pathNAme = initObj.pathNAme
      }
      else {
        this.pathNAme = '';
      }
      if (initObj.hasOwnProperty('fileNAme')) {
        this.fileNAme = initObj.fileNAme
      }
      else {
        this.fileNAme = '';
      }
      if (initObj.hasOwnProperty('flgGUI')) {
        this.flgGUI = initObj.flgGUI
      }
      else {
        this.flgGUI = 0;
      }
      if (initObj.hasOwnProperty('flg_noise')) {
        this.flg_noise = initObj.flg_noise
      }
      else {
        this.flg_noise = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type InputsPlannerSrvResponse
    // Serialize message field [origin_x]
    bufferOffset = _serializer.float64(obj.origin_x, buffer, bufferOffset);
    // Serialize message field [origin_y]
    bufferOffset = _serializer.float64(obj.origin_y, buffer, bufferOffset);
    // Serialize message field [origin_angRob]
    bufferOffset = _serializer.float64(obj.origin_angRob, buffer, bufferOffset);
    // Serialize message field [dest_x]
    bufferOffset = _serializer.float64(obj.dest_x, buffer, bufferOffset);
    // Serialize message field [dest_y]
    bufferOffset = _serializer.float64(obj.dest_y, buffer, bufferOffset);
    // Serialize message field [sensorBool]
    bufferOffset = _serializer.string(obj.sensorBool, buffer, bufferOffset);
    // Serialize message field [num_sensorsInt]
    bufferOffset = _serializer.int32(obj.num_sensorsInt, buffer, bufferOffset);
    // Serialize message field [angle_sensor_orig]
    bufferOffset = _serializer.float64(obj.angle_sensor_orig, buffer, bufferOffset);
    // Serialize message field [range_angleRob]
    bufferOffset = _serializer.float64(obj.range_angleRob, buffer, bufferOffset);
    // Serialize message field [radiusRob]
    bufferOffset = _serializer.float64(obj.radiusRob, buffer, bufferOffset);
    // Serialize message field [advance]
    bufferOffset = _serializer.float64(obj.advance, buffer, bufferOffset);
    // Serialize message field [max_angle]
    bufferOffset = _serializer.float64(obj.max_angle, buffer, bufferOffset);
    // Serialize message field [num_steps]
    bufferOffset = _serializer.int32(obj.num_steps, buffer, bufferOffset);
    // Serialize message field [select]
    bufferOffset = _serializer.int32(obj.select, buffer, bufferOffset);
    // Serialize message field [largest_sensor]
    bufferOffset = _serializer.float64(obj.largest_sensor, buffer, bufferOffset);
    // Serialize message field [pathNAme]
    bufferOffset = _serializer.string(obj.pathNAme, buffer, bufferOffset);
    // Serialize message field [fileNAme]
    bufferOffset = _serializer.string(obj.fileNAme, buffer, bufferOffset);
    // Serialize message field [flgGUI]
    bufferOffset = _serializer.int32(obj.flgGUI, buffer, bufferOffset);
    // Serialize message field [flg_noise]
    bufferOffset = _serializer.int32(obj.flg_noise, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type InputsPlannerSrvResponse
    let len;
    let data = new InputsPlannerSrvResponse(null);
    // Deserialize message field [origin_x]
    data.origin_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [origin_y]
    data.origin_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [origin_angRob]
    data.origin_angRob = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [dest_x]
    data.dest_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [dest_y]
    data.dest_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [sensorBool]
    data.sensorBool = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [num_sensorsInt]
    data.num_sensorsInt = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [angle_sensor_orig]
    data.angle_sensor_orig = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [range_angleRob]
    data.range_angleRob = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [radiusRob]
    data.radiusRob = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [advance]
    data.advance = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [max_angle]
    data.max_angle = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [num_steps]
    data.num_steps = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [select]
    data.select = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [largest_sensor]
    data.largest_sensor = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [pathNAme]
    data.pathNAme = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [fileNAme]
    data.fileNAme = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [flgGUI]
    data.flgGUI = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [flg_noise]
    data.flg_noise = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.sensorBool.length;
    length += object.pathNAme.length;
    length += object.fileNAme.length;
    return length + 120;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/InputsPlannerSrvResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8f16552e1a74db709956ba597f0eadc7';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new InputsPlannerSrvResponse(null);
    if (msg.origin_x !== undefined) {
      resolved.origin_x = msg.origin_x;
    }
    else {
      resolved.origin_x = 0.0
    }

    if (msg.origin_y !== undefined) {
      resolved.origin_y = msg.origin_y;
    }
    else {
      resolved.origin_y = 0.0
    }

    if (msg.origin_angRob !== undefined) {
      resolved.origin_angRob = msg.origin_angRob;
    }
    else {
      resolved.origin_angRob = 0.0
    }

    if (msg.dest_x !== undefined) {
      resolved.dest_x = msg.dest_x;
    }
    else {
      resolved.dest_x = 0.0
    }

    if (msg.dest_y !== undefined) {
      resolved.dest_y = msg.dest_y;
    }
    else {
      resolved.dest_y = 0.0
    }

    if (msg.sensorBool !== undefined) {
      resolved.sensorBool = msg.sensorBool;
    }
    else {
      resolved.sensorBool = ''
    }

    if (msg.num_sensorsInt !== undefined) {
      resolved.num_sensorsInt = msg.num_sensorsInt;
    }
    else {
      resolved.num_sensorsInt = 0
    }

    if (msg.angle_sensor_orig !== undefined) {
      resolved.angle_sensor_orig = msg.angle_sensor_orig;
    }
    else {
      resolved.angle_sensor_orig = 0.0
    }

    if (msg.range_angleRob !== undefined) {
      resolved.range_angleRob = msg.range_angleRob;
    }
    else {
      resolved.range_angleRob = 0.0
    }

    if (msg.radiusRob !== undefined) {
      resolved.radiusRob = msg.radiusRob;
    }
    else {
      resolved.radiusRob = 0.0
    }

    if (msg.advance !== undefined) {
      resolved.advance = msg.advance;
    }
    else {
      resolved.advance = 0.0
    }

    if (msg.max_angle !== undefined) {
      resolved.max_angle = msg.max_angle;
    }
    else {
      resolved.max_angle = 0.0
    }

    if (msg.num_steps !== undefined) {
      resolved.num_steps = msg.num_steps;
    }
    else {
      resolved.num_steps = 0
    }

    if (msg.select !== undefined) {
      resolved.select = msg.select;
    }
    else {
      resolved.select = 0
    }

    if (msg.largest_sensor !== undefined) {
      resolved.largest_sensor = msg.largest_sensor;
    }
    else {
      resolved.largest_sensor = 0.0
    }

    if (msg.pathNAme !== undefined) {
      resolved.pathNAme = msg.pathNAme;
    }
    else {
      resolved.pathNAme = ''
    }

    if (msg.fileNAme !== undefined) {
      resolved.fileNAme = msg.fileNAme;
    }
    else {
      resolved.fileNAme = ''
    }

    if (msg.flgGUI !== undefined) {
      resolved.flgGUI = msg.flgGUI;
    }
    else {
      resolved.flgGUI = 0
    }

    if (msg.flg_noise !== undefined) {
      resolved.flg_noise = msg.flg_noise;
    }
    else {
      resolved.flg_noise = 0
    }

    return resolved;
    }
};

module.exports = {
  Request: InputsPlannerSrvRequest,
  Response: InputsPlannerSrvResponse,
  md5sum() { return '188578d1209fb9d01aa3d1efc9744987'; },
  datatype() { return 'svg_ros/InputsPlannerSrv'; }
};

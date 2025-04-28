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

class SensorSrvRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.coord_x = null;
      this.coord_y = null;
      this.coord_ang = null;
    }
    else {
      if (initObj.hasOwnProperty('coord_x')) {
        this.coord_x = initObj.coord_x
      }
      else {
        this.coord_x = 0.0;
      }
      if (initObj.hasOwnProperty('coord_y')) {
        this.coord_y = initObj.coord_y
      }
      else {
        this.coord_y = 0.0;
      }
      if (initObj.hasOwnProperty('coord_ang')) {
        this.coord_ang = initObj.coord_ang
      }
      else {
        this.coord_ang = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SensorSrvRequest
    // Serialize message field [coord_x]
    bufferOffset = _serializer.float32(obj.coord_x, buffer, bufferOffset);
    // Serialize message field [coord_y]
    bufferOffset = _serializer.float32(obj.coord_y, buffer, bufferOffset);
    // Serialize message field [coord_ang]
    bufferOffset = _serializer.float32(obj.coord_ang, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SensorSrvRequest
    let len;
    let data = new SensorSrvRequest(null);
    // Deserialize message field [coord_x]
    data.coord_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [coord_y]
    data.coord_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [coord_ang]
    data.coord_ang = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 12;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/SensorSrvRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7eb93eecd92959fb5dd28a3a8fff896e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 coord_x
    float32 coord_y
    float32 coord_ang
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SensorSrvRequest(null);
    if (msg.coord_x !== undefined) {
      resolved.coord_x = msg.coord_x;
    }
    else {
      resolved.coord_x = 0.0
    }

    if (msg.coord_y !== undefined) {
      resolved.coord_y = msg.coord_y;
    }
    else {
      resolved.coord_y = 0.0
    }

    if (msg.coord_ang !== undefined) {
      resolved.coord_ang = msg.coord_ang;
    }
    else {
      resolved.coord_ang = 0.0
    }

    return resolved;
    }
};

class SensorSrvResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.flag = null;
      this.region = null;
      this.x = null;
      this.y = null;
      this.theta = null;
      this.sensors = null;
      this.num_sensors = null;
      this.sensor = null;
    }
    else {
      if (initObj.hasOwnProperty('flag')) {
        this.flag = initObj.flag
      }
      else {
        this.flag = 0;
      }
      if (initObj.hasOwnProperty('region')) {
        this.region = initObj.region
      }
      else {
        this.region = 0;
      }
      if (initObj.hasOwnProperty('x')) {
        this.x = initObj.x
      }
      else {
        this.x = 0.0;
      }
      if (initObj.hasOwnProperty('y')) {
        this.y = initObj.y
      }
      else {
        this.y = 0.0;
      }
      if (initObj.hasOwnProperty('theta')) {
        this.theta = initObj.theta
      }
      else {
        this.theta = 0.0;
      }
      if (initObj.hasOwnProperty('sensors')) {
        this.sensors = initObj.sensors
      }
      else {
        this.sensors = new Array(500).fill(0);
      }
      if (initObj.hasOwnProperty('num_sensors')) {
        this.num_sensors = initObj.num_sensors
      }
      else {
        this.num_sensors = 0;
      }
      if (initObj.hasOwnProperty('sensor')) {
        this.sensor = initObj.sensor
      }
      else {
        this.sensor = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SensorSrvResponse
    // Serialize message field [flag]
    bufferOffset = _serializer.int32(obj.flag, buffer, bufferOffset);
    // Serialize message field [region]
    bufferOffset = _serializer.int32(obj.region, buffer, bufferOffset);
    // Serialize message field [x]
    bufferOffset = _serializer.float32(obj.x, buffer, bufferOffset);
    // Serialize message field [y]
    bufferOffset = _serializer.float32(obj.y, buffer, bufferOffset);
    // Serialize message field [theta]
    bufferOffset = _serializer.float32(obj.theta, buffer, bufferOffset);
    // Check that the constant length array field [sensors] has the right length
    if (obj.sensors.length !== 500) {
      throw new Error('Unable to serialize array field sensors - length must be 500')
    }
    // Serialize message field [sensors]
    bufferOffset = _arraySerializer.float32(obj.sensors, buffer, bufferOffset, 500);
    // Serialize message field [num_sensors]
    bufferOffset = _serializer.int32(obj.num_sensors, buffer, bufferOffset);
    // Serialize message field [sensor]
    bufferOffset = _serializer.string(obj.sensor, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SensorSrvResponse
    let len;
    let data = new SensorSrvResponse(null);
    // Deserialize message field [flag]
    data.flag = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [region]
    data.region = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [x]
    data.x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [y]
    data.y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [theta]
    data.theta = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [sensors]
    data.sensors = _arrayDeserializer.float32(buffer, bufferOffset, 500)
    // Deserialize message field [num_sensors]
    data.num_sensors = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [sensor]
    data.sensor = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.sensor.length;
    return length + 2028;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/SensorSrvResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9cadfc1937ef183a51963b4c6c84ee1a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 flag
    int32 region
    float32 x
    float32 y
    float32 theta
    float32[500] sensors
    int32 num_sensors
    string sensor
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SensorSrvResponse(null);
    if (msg.flag !== undefined) {
      resolved.flag = msg.flag;
    }
    else {
      resolved.flag = 0
    }

    if (msg.region !== undefined) {
      resolved.region = msg.region;
    }
    else {
      resolved.region = 0
    }

    if (msg.x !== undefined) {
      resolved.x = msg.x;
    }
    else {
      resolved.x = 0.0
    }

    if (msg.y !== undefined) {
      resolved.y = msg.y;
    }
    else {
      resolved.y = 0.0
    }

    if (msg.theta !== undefined) {
      resolved.theta = msg.theta;
    }
    else {
      resolved.theta = 0.0
    }

    if (msg.sensors !== undefined) {
      resolved.sensors = msg.sensors;
    }
    else {
      resolved.sensors = new Array(500).fill(0)
    }

    if (msg.num_sensors !== undefined) {
      resolved.num_sensors = msg.num_sensors;
    }
    else {
      resolved.num_sensors = 0
    }

    if (msg.sensor !== undefined) {
      resolved.sensor = msg.sensor;
    }
    else {
      resolved.sensor = ''
    }

    return resolved;
    }
};

module.exports = {
  Request: SensorSrvRequest,
  Response: SensorSrvResponse,
  md5sum() { return 'b3a08c1472f241ab9eb4c0932b73ff18'; },
  datatype() { return 'svg_ros/SensorSrv'; }
};

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

class GetLaserServRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.param = null;
      this.num_sensors = null;
      this.range = null;
      this.init_angle = null;
    }
    else {
      if (initObj.hasOwnProperty('param')) {
        this.param = initObj.param
      }
      else {
        this.param = '';
      }
      if (initObj.hasOwnProperty('num_sensors')) {
        this.num_sensors = initObj.num_sensors
      }
      else {
        this.num_sensors = 0;
      }
      if (initObj.hasOwnProperty('range')) {
        this.range = initObj.range
      }
      else {
        this.range = 0.0;
      }
      if (initObj.hasOwnProperty('init_angle')) {
        this.init_angle = initObj.init_angle
      }
      else {
        this.init_angle = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetLaserServRequest
    // Serialize message field [param]
    bufferOffset = _serializer.string(obj.param, buffer, bufferOffset);
    // Serialize message field [num_sensors]
    bufferOffset = _serializer.int32(obj.num_sensors, buffer, bufferOffset);
    // Serialize message field [range]
    bufferOffset = _serializer.float32(obj.range, buffer, bufferOffset);
    // Serialize message field [init_angle]
    bufferOffset = _serializer.float32(obj.init_angle, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetLaserServRequest
    let len;
    let data = new GetLaserServRequest(null);
    // Deserialize message field [param]
    data.param = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [num_sensors]
    data.num_sensors = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [range]
    data.range = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [init_angle]
    data.init_angle = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.param.length;
    return length + 16;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/GetLaserServRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7d51aa037cb9e92d030c9070ae81e3eb';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string param
    int32 num_sensors
    float32 range
    float32 init_angle
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GetLaserServRequest(null);
    if (msg.param !== undefined) {
      resolved.param = msg.param;
    }
    else {
      resolved.param = ''
    }

    if (msg.num_sensors !== undefined) {
      resolved.num_sensors = msg.num_sensors;
    }
    else {
      resolved.num_sensors = 0
    }

    if (msg.range !== undefined) {
      resolved.range = msg.range;
    }
    else {
      resolved.range = 0.0
    }

    if (msg.init_angle !== undefined) {
      resolved.init_angle = msg.init_angle;
    }
    else {
      resolved.init_angle = 0.0
    }

    return resolved;
    }
};

class GetLaserServResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.answer = null;
      this.sensors = null;
    }
    else {
      if (initObj.hasOwnProperty('answer')) {
        this.answer = initObj.answer
      }
      else {
        this.answer = '';
      }
      if (initObj.hasOwnProperty('sensors')) {
        this.sensors = initObj.sensors
      }
      else {
        this.sensors = new Array(700).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetLaserServResponse
    // Serialize message field [answer]
    bufferOffset = _serializer.string(obj.answer, buffer, bufferOffset);
    // Check that the constant length array field [sensors] has the right length
    if (obj.sensors.length !== 700) {
      throw new Error('Unable to serialize array field sensors - length must be 700')
    }
    // Serialize message field [sensors]
    bufferOffset = _arraySerializer.float32(obj.sensors, buffer, bufferOffset, 700);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetLaserServResponse
    let len;
    let data = new GetLaserServResponse(null);
    // Deserialize message field [answer]
    data.answer = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [sensors]
    data.sensors = _arrayDeserializer.float32(buffer, bufferOffset, 700)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.answer.length;
    return length + 2804;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/GetLaserServResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5f68907596d9632843680d4d7b67e844';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string answer
    float32[700] sensors
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GetLaserServResponse(null);
    if (msg.answer !== undefined) {
      resolved.answer = msg.answer;
    }
    else {
      resolved.answer = ''
    }

    if (msg.sensors !== undefined) {
      resolved.sensors = msg.sensors;
    }
    else {
      resolved.sensors = new Array(700).fill(0)
    }

    return resolved;
    }
};

module.exports = {
  Request: GetLaserServRequest,
  Response: GetLaserServResponse,
  md5sum() { return '51e72a4807785eaabb7cee7d2a968e03'; },
  datatype() { return 'svg_ros/GetLaserServ'; }
};

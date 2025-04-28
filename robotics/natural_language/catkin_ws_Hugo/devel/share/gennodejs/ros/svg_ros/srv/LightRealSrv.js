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

class LightRealSrvRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.req = null;
    }
    else {
      if (initObj.hasOwnProperty('req')) {
        this.req = initObj.req
      }
      else {
        this.req = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LightRealSrvRequest
    // Serialize message field [req]
    bufferOffset = _serializer.int32(obj.req, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LightRealSrvRequest
    let len;
    let data = new LightRealSrvRequest(null);
    // Deserialize message field [req]
    data.req = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/LightRealSrvRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '688ec893d5ff2cccc11b9bc8bc41109b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 req
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LightRealSrvRequest(null);
    if (msg.req !== undefined) {
      resolved.req = msg.req;
    }
    else {
      resolved.req = 0
    }

    return resolved;
    }
};

class LightRealSrvResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.quantized_attraction = null;
      this.quantized_intensity = null;
    }
    else {
      if (initObj.hasOwnProperty('quantized_attraction')) {
        this.quantized_attraction = initObj.quantized_attraction
      }
      else {
        this.quantized_attraction = 0;
      }
      if (initObj.hasOwnProperty('quantized_intensity')) {
        this.quantized_intensity = initObj.quantized_intensity
      }
      else {
        this.quantized_intensity = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LightRealSrvResponse
    // Serialize message field [quantized_attraction]
    bufferOffset = _serializer.int32(obj.quantized_attraction, buffer, bufferOffset);
    // Serialize message field [quantized_intensity]
    bufferOffset = _serializer.int32(obj.quantized_intensity, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LightRealSrvResponse
    let len;
    let data = new LightRealSrvResponse(null);
    // Deserialize message field [quantized_attraction]
    data.quantized_attraction = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [quantized_intensity]
    data.quantized_intensity = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/LightRealSrvResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4e1519ab7e1a2ef915cdb29776ebb89f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 quantized_attraction
    int32 quantized_intensity
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LightRealSrvResponse(null);
    if (msg.quantized_attraction !== undefined) {
      resolved.quantized_attraction = msg.quantized_attraction;
    }
    else {
      resolved.quantized_attraction = 0
    }

    if (msg.quantized_intensity !== undefined) {
      resolved.quantized_intensity = msg.quantized_intensity;
    }
    else {
      resolved.quantized_intensity = 0
    }

    return resolved;
    }
};

module.exports = {
  Request: LightRealSrvRequest,
  Response: LightRealSrvResponse,
  md5sum() { return '880a7d45ae2b2447f4ed19a09614d287'; },
  datatype() { return 'svg_ros/LightRealSrv'; }
};

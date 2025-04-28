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

class LightSrvRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.req = null;
      this.coord_x = null;
      this.coord_y = null;
      this.coord_ang = null;
    }
    else {
      if (initObj.hasOwnProperty('req')) {
        this.req = initObj.req
      }
      else {
        this.req = 0;
      }
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
    // Serializes a message object of type LightSrvRequest
    // Serialize message field [req]
    bufferOffset = _serializer.int32(obj.req, buffer, bufferOffset);
    // Serialize message field [coord_x]
    bufferOffset = _serializer.float32(obj.coord_x, buffer, bufferOffset);
    // Serialize message field [coord_y]
    bufferOffset = _serializer.float32(obj.coord_y, buffer, bufferOffset);
    // Serialize message field [coord_ang]
    bufferOffset = _serializer.float32(obj.coord_ang, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LightSrvRequest
    let len;
    let data = new LightSrvRequest(null);
    // Deserialize message field [req]
    data.req = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [coord_x]
    data.coord_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [coord_y]
    data.coord_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [coord_ang]
    data.coord_ang = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/LightSrvRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ccc3c9539e73d3e6e2e232b07d01776a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 req
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
    const resolved = new LightSrvRequest(null);
    if (msg.req !== undefined) {
      resolved.req = msg.req;
    }
    else {
      resolved.req = 0
    }

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

class LightSrvResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.flag_dest = null;
      this.x = null;
      this.y = null;
      this.quantized_attraction = null;
      this.quantized_intensity = null;
    }
    else {
      if (initObj.hasOwnProperty('flag_dest')) {
        this.flag_dest = initObj.flag_dest
      }
      else {
        this.flag_dest = 0;
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
    // Serializes a message object of type LightSrvResponse
    // Serialize message field [flag_dest]
    bufferOffset = _serializer.int32(obj.flag_dest, buffer, bufferOffset);
    // Serialize message field [x]
    bufferOffset = _serializer.float32(obj.x, buffer, bufferOffset);
    // Serialize message field [y]
    bufferOffset = _serializer.float32(obj.y, buffer, bufferOffset);
    // Serialize message field [quantized_attraction]
    bufferOffset = _serializer.int32(obj.quantized_attraction, buffer, bufferOffset);
    // Serialize message field [quantized_intensity]
    bufferOffset = _serializer.int32(obj.quantized_intensity, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LightSrvResponse
    let len;
    let data = new LightSrvResponse(null);
    // Deserialize message field [flag_dest]
    data.flag_dest = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [x]
    data.x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [y]
    data.y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [quantized_attraction]
    data.quantized_attraction = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [quantized_intensity]
    data.quantized_intensity = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 20;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/LightSrvResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b0731a4b9c1587ca15e6de254cc3d558';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 flag_dest
    float32 x
    float32 y
    int32 quantized_attraction
    int32 quantized_intensity
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LightSrvResponse(null);
    if (msg.flag_dest !== undefined) {
      resolved.flag_dest = msg.flag_dest;
    }
    else {
      resolved.flag_dest = 0
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
  Request: LightSrvRequest,
  Response: LightSrvResponse,
  md5sum() { return 'eba6c43e856487b2b6ad559a0d0f124d'; },
  datatype() { return 'svg_ros/LightSrv'; }
};

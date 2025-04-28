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

class MVServRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.param = null;
      this.coord_x = null;
      this.coord_y = null;
      this.coord_ang = null;
    }
    else {
      if (initObj.hasOwnProperty('param')) {
        this.param = initObj.param
      }
      else {
        this.param = '';
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
    // Serializes a message object of type MVServRequest
    // Serialize message field [param]
    bufferOffset = _serializer.string(obj.param, buffer, bufferOffset);
    // Serialize message field [coord_x]
    bufferOffset = _serializer.float32(obj.coord_x, buffer, bufferOffset);
    // Serialize message field [coord_y]
    bufferOffset = _serializer.float32(obj.coord_y, buffer, bufferOffset);
    // Serialize message field [coord_ang]
    bufferOffset = _serializer.float32(obj.coord_ang, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MVServRequest
    let len;
    let data = new MVServRequest(null);
    // Deserialize message field [param]
    data.param = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [coord_x]
    data.coord_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [coord_y]
    data.coord_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [coord_ang]
    data.coord_ang = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.param.length;
    return length + 16;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/MVServRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd3cc9a10efcfe8293203cd968ed57a1b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string param
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
    const resolved = new MVServRequest(null);
    if (msg.param !== undefined) {
      resolved.param = msg.param;
    }
    else {
      resolved.param = ''
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

class MVServResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.answer = null;
    }
    else {
      if (initObj.hasOwnProperty('answer')) {
        this.answer = initObj.answer
      }
      else {
        this.answer = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MVServResponse
    // Serialize message field [answer]
    bufferOffset = _serializer.string(obj.answer, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MVServResponse
    let len;
    let data = new MVServResponse(null);
    // Deserialize message field [answer]
    data.answer = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.answer.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/MVServResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd7e708f879c94bb931716d8f4f130f30';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string answer
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MVServResponse(null);
    if (msg.answer !== undefined) {
      resolved.answer = msg.answer;
    }
    else {
      resolved.answer = ''
    }

    return resolved;
    }
};

module.exports = {
  Request: MVServRequest,
  Response: MVServResponse,
  md5sum() { return 'a5027d7394e6db0c454d58003c11ba06'; },
  datatype() { return 'svg_ros/MVServ'; }
};

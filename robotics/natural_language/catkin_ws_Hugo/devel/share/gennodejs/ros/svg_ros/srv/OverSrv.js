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

class OverSrvRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.over_flg = null;
    }
    else {
      if (initObj.hasOwnProperty('over_flg')) {
        this.over_flg = initObj.over_flg
      }
      else {
        this.over_flg = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type OverSrvRequest
    // Serialize message field [over_flg]
    bufferOffset = _serializer.int32(obj.over_flg, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type OverSrvRequest
    let len;
    let data = new OverSrvRequest(null);
    // Deserialize message field [over_flg]
    data.over_flg = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/OverSrvRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '27cbf5183d3654cc200ef0b2bc3c0ae5';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 over_flg
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new OverSrvRequest(null);
    if (msg.over_flg !== undefined) {
      resolved.over_flg = msg.over_flg;
    }
    else {
      resolved.over_flg = 0
    }

    return resolved;
    }
};

class OverSrvResponse {
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
        this.answer = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type OverSrvResponse
    // Serialize message field [answer]
    bufferOffset = _serializer.int32(obj.answer, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type OverSrvResponse
    let len;
    let data = new OverSrvResponse(null);
    // Deserialize message field [answer]
    data.answer = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/OverSrvResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '470a19a3f8e6b2cdb8f4d6ac8875463a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 answer
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new OverSrvResponse(null);
    if (msg.answer !== undefined) {
      resolved.answer = msg.answer;
    }
    else {
      resolved.answer = 0
    }

    return resolved;
    }
};

module.exports = {
  Request: OverSrvRequest,
  Response: OverSrvResponse,
  md5sum() { return 'ed5c22717a93863499734f374ca8e9a3'; },
  datatype() { return 'svg_ros/OverSrv'; }
};

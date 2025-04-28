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

class ReadySrvRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ready = null;
    }
    else {
      if (initObj.hasOwnProperty('ready')) {
        this.ready = initObj.ready
      }
      else {
        this.ready = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ReadySrvRequest
    // Serialize message field [ready]
    bufferOffset = _serializer.int32(obj.ready, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ReadySrvRequest
    let len;
    let data = new ReadySrvRequest(null);
    // Deserialize message field [ready]
    data.ready = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/ReadySrvRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '291f89bf3c78c525c8b92db5f257f513';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 ready
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ReadySrvRequest(null);
    if (msg.ready !== undefined) {
      resolved.ready = msg.ready;
    }
    else {
      resolved.ready = 0
    }

    return resolved;
    }
};

class ReadySrvResponse {
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
    // Serializes a message object of type ReadySrvResponse
    // Serialize message field [answer]
    bufferOffset = _serializer.int32(obj.answer, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ReadySrvResponse
    let len;
    let data = new ReadySrvResponse(null);
    // Deserialize message field [answer]
    data.answer = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'svg_ros/ReadySrvResponse';
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
    const resolved = new ReadySrvResponse(null);
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
  Request: ReadySrvRequest,
  Response: ReadySrvResponse,
  md5sum() { return '481bf4557884a8ae5f3651bd90c8f18f'; },
  datatype() { return 'svg_ros/ReadySrv'; }
};

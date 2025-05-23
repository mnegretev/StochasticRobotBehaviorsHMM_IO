# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from svg_ros/LightSrvRequest.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class LightSrvRequest(genpy.Message):
  _md5sum = "ccc3c9539e73d3e6e2e232b07d01776a"
  _type = "svg_ros/LightSrvRequest"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """int32 req
float32 coord_x
float32 coord_y
float32 coord_ang
"""
  __slots__ = ['req','coord_x','coord_y','coord_ang']
  _slot_types = ['int32','float32','float32','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       req,coord_x,coord_y,coord_ang

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(LightSrvRequest, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.req is None:
        self.req = 0
      if self.coord_x is None:
        self.coord_x = 0.
      if self.coord_y is None:
        self.coord_y = 0.
      if self.coord_ang is None:
        self.coord_ang = 0.
    else:
      self.req = 0
      self.coord_x = 0.
      self.coord_y = 0.
      self.coord_ang = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_i3f().pack(_x.req, _x.coord_x, _x.coord_y, _x.coord_ang))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 16
      (_x.req, _x.coord_x, _x.coord_y, _x.coord_ang,) = _get_struct_i3f().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_i3f().pack(_x.req, _x.coord_x, _x.coord_y, _x.coord_ang))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 16
      (_x.req, _x.coord_x, _x.coord_y, _x.coord_ang,) = _get_struct_i3f().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_i3f = None
def _get_struct_i3f():
    global _struct_i3f
    if _struct_i3f is None:
        _struct_i3f = struct.Struct("<i3f")
    return _struct_i3f
# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from svg_ros/LightSrvResponse.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class LightSrvResponse(genpy.Message):
  _md5sum = "b0731a4b9c1587ca15e6de254cc3d558"
  _type = "svg_ros/LightSrvResponse"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """int32 flag_dest
float32 x
float32 y
int32 quantized_attraction
int32 quantized_intensity
"""
  __slots__ = ['flag_dest','x','y','quantized_attraction','quantized_intensity']
  _slot_types = ['int32','float32','float32','int32','int32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       flag_dest,x,y,quantized_attraction,quantized_intensity

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(LightSrvResponse, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.flag_dest is None:
        self.flag_dest = 0
      if self.x is None:
        self.x = 0.
      if self.y is None:
        self.y = 0.
      if self.quantized_attraction is None:
        self.quantized_attraction = 0
      if self.quantized_intensity is None:
        self.quantized_intensity = 0
    else:
      self.flag_dest = 0
      self.x = 0.
      self.y = 0.
      self.quantized_attraction = 0
      self.quantized_intensity = 0

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_i2f2i().pack(_x.flag_dest, _x.x, _x.y, _x.quantized_attraction, _x.quantized_intensity))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 20
      (_x.flag_dest, _x.x, _x.y, _x.quantized_attraction, _x.quantized_intensity,) = _get_struct_i2f2i().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_i2f2i().pack(_x.flag_dest, _x.x, _x.y, _x.quantized_attraction, _x.quantized_intensity))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 20
      (_x.flag_dest, _x.x, _x.y, _x.quantized_attraction, _x.quantized_intensity,) = _get_struct_i2f2i().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_i2f2i = None
def _get_struct_i2f2i():
    global _struct_i2f2i
    if _struct_i2f2i is None:
        _struct_i2f2i = struct.Struct("<i2f2i")
    return _struct_i2f2i
class LightSrv(object):
  _type          = 'svg_ros/LightSrv'
  _md5sum = 'eba6c43e856487b2b6ad559a0d0f124d'
  _request_class  = LightSrvRequest
  _response_class = LightSrvResponse

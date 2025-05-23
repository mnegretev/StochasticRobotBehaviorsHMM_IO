// Generated by gencpp from file svg_ros/LightSrvResponse.msg
// DO NOT EDIT!


#ifndef SVG_ROS_MESSAGE_LIGHTSRVRESPONSE_H
#define SVG_ROS_MESSAGE_LIGHTSRVRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace svg_ros
{
template <class ContainerAllocator>
struct LightSrvResponse_
{
  typedef LightSrvResponse_<ContainerAllocator> Type;

  LightSrvResponse_()
    : flag_dest(0)
    , x(0.0)
    , y(0.0)
    , quantized_attraction(0)
    , quantized_intensity(0)  {
    }
  LightSrvResponse_(const ContainerAllocator& _alloc)
    : flag_dest(0)
    , x(0.0)
    , y(0.0)
    , quantized_attraction(0)
    , quantized_intensity(0)  {
  (void)_alloc;
    }



   typedef int32_t _flag_dest_type;
  _flag_dest_type flag_dest;

   typedef float _x_type;
  _x_type x;

   typedef float _y_type;
  _y_type y;

   typedef int32_t _quantized_attraction_type;
  _quantized_attraction_type quantized_attraction;

   typedef int32_t _quantized_intensity_type;
  _quantized_intensity_type quantized_intensity;





  typedef boost::shared_ptr< ::svg_ros::LightSrvResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::svg_ros::LightSrvResponse_<ContainerAllocator> const> ConstPtr;

}; // struct LightSrvResponse_

typedef ::svg_ros::LightSrvResponse_<std::allocator<void> > LightSrvResponse;

typedef boost::shared_ptr< ::svg_ros::LightSrvResponse > LightSrvResponsePtr;
typedef boost::shared_ptr< ::svg_ros::LightSrvResponse const> LightSrvResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::svg_ros::LightSrvResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::svg_ros::LightSrvResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace svg_ros

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::svg_ros::LightSrvResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::svg_ros::LightSrvResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::svg_ros::LightSrvResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::svg_ros::LightSrvResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::svg_ros::LightSrvResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::svg_ros::LightSrvResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::svg_ros::LightSrvResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "b0731a4b9c1587ca15e6de254cc3d558";
  }

  static const char* value(const ::svg_ros::LightSrvResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xb0731a4b9c1587caULL;
  static const uint64_t static_value2 = 0x15e6de254cc3d558ULL;
};

template<class ContainerAllocator>
struct DataType< ::svg_ros::LightSrvResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "svg_ros/LightSrvResponse";
  }

  static const char* value(const ::svg_ros::LightSrvResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::svg_ros::LightSrvResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 flag_dest\n\
float32 x\n\
float32 y\n\
int32 quantized_attraction\n\
int32 quantized_intensity\n\
";
  }

  static const char* value(const ::svg_ros::LightSrvResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::svg_ros::LightSrvResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.flag_dest);
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.quantized_attraction);
      stream.next(m.quantized_intensity);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct LightSrvResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::svg_ros::LightSrvResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::svg_ros::LightSrvResponse_<ContainerAllocator>& v)
  {
    s << indent << "flag_dest: ";
    Printer<int32_t>::stream(s, indent + "  ", v.flag_dest);
    s << indent << "x: ";
    Printer<float>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<float>::stream(s, indent + "  ", v.y);
    s << indent << "quantized_attraction: ";
    Printer<int32_t>::stream(s, indent + "  ", v.quantized_attraction);
    s << indent << "quantized_intensity: ";
    Printer<int32_t>::stream(s, indent + "  ", v.quantized_intensity);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SVG_ROS_MESSAGE_LIGHTSRVRESPONSE_H

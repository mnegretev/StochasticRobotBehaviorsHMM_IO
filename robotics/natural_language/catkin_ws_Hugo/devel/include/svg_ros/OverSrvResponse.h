// Generated by gencpp from file svg_ros/OverSrvResponse.msg
// DO NOT EDIT!


#ifndef SVG_ROS_MESSAGE_OVERSRVRESPONSE_H
#define SVG_ROS_MESSAGE_OVERSRVRESPONSE_H


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
struct OverSrvResponse_
{
  typedef OverSrvResponse_<ContainerAllocator> Type;

  OverSrvResponse_()
    : answer(0)  {
    }
  OverSrvResponse_(const ContainerAllocator& _alloc)
    : answer(0)  {
  (void)_alloc;
    }



   typedef int32_t _answer_type;
  _answer_type answer;





  typedef boost::shared_ptr< ::svg_ros::OverSrvResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::svg_ros::OverSrvResponse_<ContainerAllocator> const> ConstPtr;

}; // struct OverSrvResponse_

typedef ::svg_ros::OverSrvResponse_<std::allocator<void> > OverSrvResponse;

typedef boost::shared_ptr< ::svg_ros::OverSrvResponse > OverSrvResponsePtr;
typedef boost::shared_ptr< ::svg_ros::OverSrvResponse const> OverSrvResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::svg_ros::OverSrvResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::svg_ros::OverSrvResponse_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::svg_ros::OverSrvResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::svg_ros::OverSrvResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::svg_ros::OverSrvResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::svg_ros::OverSrvResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::svg_ros::OverSrvResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::svg_ros::OverSrvResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::svg_ros::OverSrvResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "470a19a3f8e6b2cdb8f4d6ac8875463a";
  }

  static const char* value(const ::svg_ros::OverSrvResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x470a19a3f8e6b2cdULL;
  static const uint64_t static_value2 = 0xb8f4d6ac8875463aULL;
};

template<class ContainerAllocator>
struct DataType< ::svg_ros::OverSrvResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "svg_ros/OverSrvResponse";
  }

  static const char* value(const ::svg_ros::OverSrvResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::svg_ros::OverSrvResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 answer\n\
";
  }

  static const char* value(const ::svg_ros::OverSrvResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::svg_ros::OverSrvResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.answer);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct OverSrvResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::svg_ros::OverSrvResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::svg_ros::OverSrvResponse_<ContainerAllocator>& v)
  {
    s << indent << "answer: ";
    Printer<int32_t>::stream(s, indent + "  ", v.answer);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SVG_ROS_MESSAGE_OVERSRVRESPONSE_H

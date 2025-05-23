// Generated by gencpp from file planner_msgs/PlanningCmdSend.msg
// DO NOT EDIT!


#ifndef PLANNER_MSGS_MESSAGE_PLANNINGCMDSEND_H
#define PLANNER_MSGS_MESSAGE_PLANNINGCMDSEND_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace planner_msgs
{
template <class ContainerAllocator>
struct PlanningCmdSend_
{
  typedef PlanningCmdSend_<ContainerAllocator> Type;

  PlanningCmdSend_()
    : command()  {
    }
  PlanningCmdSend_(const ContainerAllocator& _alloc)
    : command(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _command_type;
  _command_type command;





  typedef boost::shared_ptr< ::planner_msgs::PlanningCmdSend_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::planner_msgs::PlanningCmdSend_<ContainerAllocator> const> ConstPtr;

}; // struct PlanningCmdSend_

typedef ::planner_msgs::PlanningCmdSend_<std::allocator<void> > PlanningCmdSend;

typedef boost::shared_ptr< ::planner_msgs::PlanningCmdSend > PlanningCmdSendPtr;
typedef boost::shared_ptr< ::planner_msgs::PlanningCmdSend const> PlanningCmdSendConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::planner_msgs::PlanningCmdSend_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::planner_msgs::PlanningCmdSend_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace planner_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'planner_msgs': ['/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg', '/home/biorobotica/catkin_ws/src/planeacion/planner_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::planner_msgs::PlanningCmdSend_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::planner_msgs::PlanningCmdSend_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::planner_msgs::PlanningCmdSend_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::planner_msgs::PlanningCmdSend_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::planner_msgs::PlanningCmdSend_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::planner_msgs::PlanningCmdSend_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::planner_msgs::PlanningCmdSend_<ContainerAllocator> >
{
  static const char* value()
  {
    return "cba5e21e920a3a2b7b375cb65b64cdea";
  }

  static const char* value(const ::planner_msgs::PlanningCmdSend_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xcba5e21e920a3a2bULL;
  static const uint64_t static_value2 = 0x7b375cb65b64cdeaULL;
};

template<class ContainerAllocator>
struct DataType< ::planner_msgs::PlanningCmdSend_<ContainerAllocator> >
{
  static const char* value()
  {
    return "planner_msgs/PlanningCmdSend";
  }

  static const char* value(const ::planner_msgs::PlanningCmdSend_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::planner_msgs::PlanningCmdSend_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string command\n\
\n\
";
  }

  static const char* value(const ::planner_msgs::PlanningCmdSend_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::planner_msgs::PlanningCmdSend_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.command);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PlanningCmdSend_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::planner_msgs::PlanningCmdSend_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::planner_msgs::PlanningCmdSend_<ContainerAllocator>& v)
  {
    s << indent << "command: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.command);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PLANNER_MSGS_MESSAGE_PLANNINGCMDSEND_H

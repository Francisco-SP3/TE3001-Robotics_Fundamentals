// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_msgs:msg/SignalParams.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MSGS__MSG__DETAIL__SIGNAL_PARAMS__BUILDER_HPP_
#define CUSTOM_MSGS__MSG__DETAIL__SIGNAL_PARAMS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_msgs/msg/detail/signal_params__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_msgs
{

namespace msg
{

namespace builder
{

class Init_SignalParams_time
{
public:
  explicit Init_SignalParams_time(::custom_msgs::msg::SignalParams & msg)
  : msg_(msg)
  {}
  ::custom_msgs::msg::SignalParams time(::custom_msgs::msg::SignalParams::_time_type arg)
  {
    msg_.time = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_msgs::msg::SignalParams msg_;
};

class Init_SignalParams_phase
{
public:
  explicit Init_SignalParams_phase(::custom_msgs::msg::SignalParams & msg)
  : msg_(msg)
  {}
  Init_SignalParams_time phase(::custom_msgs::msg::SignalParams::_phase_type arg)
  {
    msg_.phase = std::move(arg);
    return Init_SignalParams_time(msg_);
  }

private:
  ::custom_msgs::msg::SignalParams msg_;
};

class Init_SignalParams_offset
{
public:
  explicit Init_SignalParams_offset(::custom_msgs::msg::SignalParams & msg)
  : msg_(msg)
  {}
  Init_SignalParams_phase offset(::custom_msgs::msg::SignalParams::_offset_type arg)
  {
    msg_.offset = std::move(arg);
    return Init_SignalParams_phase(msg_);
  }

private:
  ::custom_msgs::msg::SignalParams msg_;
};

class Init_SignalParams_frequency
{
public:
  explicit Init_SignalParams_frequency(::custom_msgs::msg::SignalParams & msg)
  : msg_(msg)
  {}
  Init_SignalParams_offset frequency(::custom_msgs::msg::SignalParams::_frequency_type arg)
  {
    msg_.frequency = std::move(arg);
    return Init_SignalParams_offset(msg_);
  }

private:
  ::custom_msgs::msg::SignalParams msg_;
};

class Init_SignalParams_amplitude
{
public:
  explicit Init_SignalParams_amplitude(::custom_msgs::msg::SignalParams & msg)
  : msg_(msg)
  {}
  Init_SignalParams_frequency amplitude(::custom_msgs::msg::SignalParams::_amplitude_type arg)
  {
    msg_.amplitude = std::move(arg);
    return Init_SignalParams_frequency(msg_);
  }

private:
  ::custom_msgs::msg::SignalParams msg_;
};

class Init_SignalParams_type
{
public:
  Init_SignalParams_type()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SignalParams_amplitude type(::custom_msgs::msg::SignalParams::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_SignalParams_amplitude(msg_);
  }

private:
  ::custom_msgs::msg::SignalParams msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_msgs::msg::SignalParams>()
{
  return custom_msgs::msg::builder::Init_SignalParams_type();
}

}  // namespace custom_msgs

#endif  // CUSTOM_MSGS__MSG__DETAIL__SIGNAL_PARAMS__BUILDER_HPP_

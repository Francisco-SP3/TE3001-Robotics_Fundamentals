// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from xarm_msgs:srv/SetInt16ById.idl
// generated code does not contain a copyright notice

#ifndef XARM_MSGS__SRV__DETAIL__SET_INT16_BY_ID__FUNCTIONS_H_
#define XARM_MSGS__SRV__DETAIL__SET_INT16_BY_ID__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "xarm_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "xarm_msgs/srv/detail/set_int16_by_id__struct.h"

/// Initialize srv/SetInt16ById message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * xarm_msgs__srv__SetInt16ById_Request
 * )) before or use
 * xarm_msgs__srv__SetInt16ById_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
bool
xarm_msgs__srv__SetInt16ById_Request__init(xarm_msgs__srv__SetInt16ById_Request * msg);

/// Finalize srv/SetInt16ById message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
void
xarm_msgs__srv__SetInt16ById_Request__fini(xarm_msgs__srv__SetInt16ById_Request * msg);

/// Create srv/SetInt16ById message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * xarm_msgs__srv__SetInt16ById_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
xarm_msgs__srv__SetInt16ById_Request *
xarm_msgs__srv__SetInt16ById_Request__create();

/// Destroy srv/SetInt16ById message.
/**
 * It calls
 * xarm_msgs__srv__SetInt16ById_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
void
xarm_msgs__srv__SetInt16ById_Request__destroy(xarm_msgs__srv__SetInt16ById_Request * msg);

/// Check for srv/SetInt16ById message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
bool
xarm_msgs__srv__SetInt16ById_Request__are_equal(const xarm_msgs__srv__SetInt16ById_Request * lhs, const xarm_msgs__srv__SetInt16ById_Request * rhs);

/// Copy a srv/SetInt16ById message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
bool
xarm_msgs__srv__SetInt16ById_Request__copy(
  const xarm_msgs__srv__SetInt16ById_Request * input,
  xarm_msgs__srv__SetInt16ById_Request * output);

/// Initialize array of srv/SetInt16ById messages.
/**
 * It allocates the memory for the number of elements and calls
 * xarm_msgs__srv__SetInt16ById_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
bool
xarm_msgs__srv__SetInt16ById_Request__Sequence__init(xarm_msgs__srv__SetInt16ById_Request__Sequence * array, size_t size);

/// Finalize array of srv/SetInt16ById messages.
/**
 * It calls
 * xarm_msgs__srv__SetInt16ById_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
void
xarm_msgs__srv__SetInt16ById_Request__Sequence__fini(xarm_msgs__srv__SetInt16ById_Request__Sequence * array);

/// Create array of srv/SetInt16ById messages.
/**
 * It allocates the memory for the array and calls
 * xarm_msgs__srv__SetInt16ById_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
xarm_msgs__srv__SetInt16ById_Request__Sequence *
xarm_msgs__srv__SetInt16ById_Request__Sequence__create(size_t size);

/// Destroy array of srv/SetInt16ById messages.
/**
 * It calls
 * xarm_msgs__srv__SetInt16ById_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
void
xarm_msgs__srv__SetInt16ById_Request__Sequence__destroy(xarm_msgs__srv__SetInt16ById_Request__Sequence * array);

/// Check for srv/SetInt16ById message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
bool
xarm_msgs__srv__SetInt16ById_Request__Sequence__are_equal(const xarm_msgs__srv__SetInt16ById_Request__Sequence * lhs, const xarm_msgs__srv__SetInt16ById_Request__Sequence * rhs);

/// Copy an array of srv/SetInt16ById messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
bool
xarm_msgs__srv__SetInt16ById_Request__Sequence__copy(
  const xarm_msgs__srv__SetInt16ById_Request__Sequence * input,
  xarm_msgs__srv__SetInt16ById_Request__Sequence * output);

/// Initialize srv/SetInt16ById message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * xarm_msgs__srv__SetInt16ById_Response
 * )) before or use
 * xarm_msgs__srv__SetInt16ById_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
bool
xarm_msgs__srv__SetInt16ById_Response__init(xarm_msgs__srv__SetInt16ById_Response * msg);

/// Finalize srv/SetInt16ById message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
void
xarm_msgs__srv__SetInt16ById_Response__fini(xarm_msgs__srv__SetInt16ById_Response * msg);

/// Create srv/SetInt16ById message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * xarm_msgs__srv__SetInt16ById_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
xarm_msgs__srv__SetInt16ById_Response *
xarm_msgs__srv__SetInt16ById_Response__create();

/// Destroy srv/SetInt16ById message.
/**
 * It calls
 * xarm_msgs__srv__SetInt16ById_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
void
xarm_msgs__srv__SetInt16ById_Response__destroy(xarm_msgs__srv__SetInt16ById_Response * msg);

/// Check for srv/SetInt16ById message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
bool
xarm_msgs__srv__SetInt16ById_Response__are_equal(const xarm_msgs__srv__SetInt16ById_Response * lhs, const xarm_msgs__srv__SetInt16ById_Response * rhs);

/// Copy a srv/SetInt16ById message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
bool
xarm_msgs__srv__SetInt16ById_Response__copy(
  const xarm_msgs__srv__SetInt16ById_Response * input,
  xarm_msgs__srv__SetInt16ById_Response * output);

/// Initialize array of srv/SetInt16ById messages.
/**
 * It allocates the memory for the number of elements and calls
 * xarm_msgs__srv__SetInt16ById_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
bool
xarm_msgs__srv__SetInt16ById_Response__Sequence__init(xarm_msgs__srv__SetInt16ById_Response__Sequence * array, size_t size);

/// Finalize array of srv/SetInt16ById messages.
/**
 * It calls
 * xarm_msgs__srv__SetInt16ById_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
void
xarm_msgs__srv__SetInt16ById_Response__Sequence__fini(xarm_msgs__srv__SetInt16ById_Response__Sequence * array);

/// Create array of srv/SetInt16ById messages.
/**
 * It allocates the memory for the array and calls
 * xarm_msgs__srv__SetInt16ById_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
xarm_msgs__srv__SetInt16ById_Response__Sequence *
xarm_msgs__srv__SetInt16ById_Response__Sequence__create(size_t size);

/// Destroy array of srv/SetInt16ById messages.
/**
 * It calls
 * xarm_msgs__srv__SetInt16ById_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
void
xarm_msgs__srv__SetInt16ById_Response__Sequence__destroy(xarm_msgs__srv__SetInt16ById_Response__Sequence * array);

/// Check for srv/SetInt16ById message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
bool
xarm_msgs__srv__SetInt16ById_Response__Sequence__are_equal(const xarm_msgs__srv__SetInt16ById_Response__Sequence * lhs, const xarm_msgs__srv__SetInt16ById_Response__Sequence * rhs);

/// Copy an array of srv/SetInt16ById messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_xarm_msgs
bool
xarm_msgs__srv__SetInt16ById_Response__Sequence__copy(
  const xarm_msgs__srv__SetInt16ById_Response__Sequence * input,
  xarm_msgs__srv__SetInt16ById_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // XARM_MSGS__SRV__DETAIL__SET_INT16_BY_ID__FUNCTIONS_H_

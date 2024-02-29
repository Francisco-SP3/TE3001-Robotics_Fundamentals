from launch import LaunchDescription

from launch_ros.actions import Node, RosTimer

def generate_launch_description():

  #new_phase_value = LaunchConfiguration('new_phase')

  sig_gen = Node(
    #prefix=['terminator --execute '],
    name='signal_generator',
    namespace='',
    package='courseworks',
    executable='signal_generator',
  )
  proc = Node(
    #prefix=['terminator --execute '],
    name='process',
    namespace='',
    package='courseworks',
    executable='process',
  )
  graph = Node(
    name='signal_graph',
    namespace='',
    package='rqt_graph',
    executable='rqt_graph',
  )
  plot = Node(
    name='signal_plot',
    namespace='',
    package='rqt_plot',
    executable='rqt_plot',
    arguments=['/signal/data', '/proc_signal/data'],
  )

  return LaunchDescription([
    sig_gen,
    RosTimer(period=0.25, actions=[proc]),
    RosTimer(period=0.75, actions=[graph]),
    RosTimer(period=1.0, actions=[plot]),
  ])

import os

from launch import LaunchDescription

from launch_ros.actions import Node, RosTimer

from ament_index_python.packages import get_package_share_directory

def generate_launch_description():

  #new_phase_value = LaunchConfiguration('new_phase')

  config = os.path.join(
    get_package_share_directory('signal_reconstruct'),
    'config',
    'params.yaml'
    )

  sig_gen = Node(
    #prefix=['terminator --execute '],
    name='signal_generator',
    namespace='',
    package='signal_reconstruct',
    executable='signal_generator',
    parameters=[config],
  )
  proc = Node(
    #prefix=['terminator --execute '],
    name='reconstruction',
    namespace='',
    package='signal_reconstruct',
    executable='reconstruction',
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
  ])

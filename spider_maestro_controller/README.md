SPIDER_MAESTRO_CONTROLLER
======

The function of this node is to make the servos move.

It receives messages containing the position desired for each servo, and it communicate that to the [maestro](https://www.pololu.com/product/1356)(servo-controller chip).

How it works
-----

Receives data from `/joints_to_controller` topic, and it converts them into commands for the maestro, writing by default in [/dev/ttyACM0](https://github.com/erlerobot/erle-spider/blob/spider/software/src/spider_maestro_controller/src/controller_sub.cpp#L19) (the interface that comunicate [Erle-Brain](https://erlerobotics.com/blog/erle-brain-es/) with [Mini-Maestro](https://www.pololu.com/product/1356)), but you can change it using the [port_name](https://github.com/erlerobot/erle-spider/blob/spider/software/launch-files/spider-physic.launch#L4) param of the launch file.

Input
-----

topic `/joints_to_controller`

 * msg type: [LegsJointsState](https://github.com/erlerobot/erle-spider/blob/spider/software/src/spider_msgs/msg/LegsJointsState.msg)

 * publishers: [/spider_body_kinematics](https://github.com/erlerobot/erle-spider/tree/master/software/src/spider_body_kinematics) and [/spider_gait](https://github.com/erlerobot/erle-spider/tree/master/software/src/spider_gait)


Output
------

0-255 value for each servo-motor, 127 is the medium position, while 0 and 255 are a 45º degree movements. 


Graph
----

![alt tag](../../../docs/img/rqt_graph_captures/maestro.png?raw=true)

Details
----

**rosnode info /spider_maestro_controller:**

```
--------------------------------------------------------------------------------
Node [/spider_maestro_controller]
Publications: 
 * /rosout [rosgraph_msgs/Log]

Subscriptions: 
 * /joints_to_controller [spider_msgs/LegsJointsState]

Services: 
 * /spider_maestro_controller/set_logger_level
 * /spider_maestro_controller/get_loggers


contacting node http://xabi-XPS-13-9343:50422/ ...
Pid: 24554
Connections:
 * topic: /rosout
    * to: /rosout
    * direction: outbound
    * transport: TCPROS
 * topic: /joints_to_controller
    * to: /spider_body_kinematics (http://xabi-XPS-13-9343:51525/)
    * direction: inbound
    * transport: TCPROS
 * topic: /joints_to_controller
    * to: /spider_gait (http://xabi-XPS-13-9343:44378/)
    * direction: inbound
    * transport: TCPROS

```


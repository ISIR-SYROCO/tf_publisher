#ifndef OROCOS_TF_PUBLISHER_COMPONENT_HPP
#define OROCOS_TF_PUBLISHER_COMPONENT_HPP

#include <rtt/RTT.hpp>
#include <rtt/Port.hpp>
#include <geometry_msgs/typekit/Types.hpp>
#include <iostream>
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

class Tf_publisher
    : public RTT::TaskContext
{
 public:
    Tf_publisher(std::string const& name);

    bool configureHook();

    bool startHook();

    void updateHook();

    void stopHook();

    void cleanupHook();

	void createPorts();

 public:
	unsigned int number_of_segments;
	std::vector< RTT::OutputPort< tf::StampedTransform >*  > _oports;


};

#endif

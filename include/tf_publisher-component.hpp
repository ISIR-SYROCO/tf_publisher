#ifndef OROCOS_TF_PUBLISHER_COMPONENT_HPP
#define OROCOS_TF_PUBLISHER_COMPONENT_HPP

#include <rtt/RTT.hpp>
#include <rtt/Port.hpp>
#include <geometry_msgs/typekit/Types.hpp>
#include <iostream>
#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/tfMessage.h>
#include<Eigen/Core>
#include<Eigen/Lgsm>

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
	//std::vector< RTT::OutputPort< tf::tfMessage >*  > _oports;


};

#endif

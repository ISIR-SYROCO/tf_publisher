#include "tf_publisher-component.hpp"
#include <rtt/Component.hpp>
#include <ros/ros.h>


Tf_publisher::Tf_publisher(std::string const& name)
	: TaskContext(name, PreOperational),
	  number_of_segments(0){
		this->addProperty("numSegments", number_of_segments).doc("number of link of the robot");
		std::cout << "Tf_publisher constructed !" <<std::endl;
}

bool Tf_publisher::configureHook(){
	if(number_of_segments == 0){
		std::cout << "Please define numSegments" << std::endl;
		return false;
	}

	createPorts();

	std::cout << "Tf_publisher configured !" <<std::endl;
	return true;
}

bool Tf_publisher::startHook(){
	if (number_of_segments == 0){
		std::cout << "Please set numSegments" << std::endl;
		return false;
	}
	std::cout << "Tf_publisher started !" << std::endl;
	return true;
}

void Tf_publisher::updateHook(){
	int i = 0;
	for(std::vector< RTT::OutputPort < tf::StampedTransform >* >::iterator it = _oports.begin();
			it != _oports.end();
			++it){
		std::ostringstream ss_segment_name;
		ss_segment_name << "segment_" << i;
		i++;
		tf::Transform transform;
		tf::StampedTransform(transform, ros::Time::now(), "world", ss_segment_name.str());
	}
}

void Tf_publisher::stopHook(){
	std::cout << "Tf_publisher executes stopping !" <<std::endl;
}

void Tf_publisher::cleanupHook(){
	std::cout << "Tf_publisher cleaning up !" <<std::endl;
}

void Tf_publisher::createPorts(){
	_oports.resize(number_of_segments);
	for (unsigned int i=0; i<number_of_segments; i++){

		std::ostringstream ss_segName;
		ss_segName << "segment" << i;

		_oports[i] = new RTT::OutputPort< tf::StampedTransform >(ss_segName.str());
		this->addPort(*(_oports[i]));
	}

}

/*
 * Using this macro, only one component may live
 * in one library *and* you may *not* link this library
 * with another component library. Use
 * ORO_CREATE_COMPONENT_TYPE()
 * ORO_LIST_COMPONENT_TYPE(Tf_publisher)
 * In case you want to link with another library that
 * already contains components.
 *
 * If you have put your component class
 * in a namespace, don't forget to add it here too:
 */
ORO_CREATE_COMPONENT(Tf_publisher)

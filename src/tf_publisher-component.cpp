#include "tf_publisher-component.hpp"
#include <tf_lgsm/tf_lgsm.h>
#include <rtt/Component.hpp>
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

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
    ros::start();
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

	Eigen::Displacementd p1(0.0, 0.0, 0.35999999999999999, 1.0, 0.0, 0.0, 0.0);
	Eigen::Displacementd p2(0.0, 0.0, 0.35999999999999999, 0.85965458317679577, 0.0, 0.0, 0.51087571641557739);
	Eigen::Displacementd p3(0.0, 0.0, 0.35999999999999999, 0.79333436744057395, -0.19676561949834656, 0.3310990543848395, 0.47146292389387456);
	Eigen::Displacementd p4(0.13592386699527353, 0.24976120034624139, 0.64132551463146004, 0.29964378078697473, 0.064289416465290863, 0.37974988827019718,	0.87285193356319746);
	Eigen::Displacementd p5(0.13592386699527353, 0.24976120034624139, 0.64132551463146004,	-0.55145571137898231, 0.042101567767920102, -0.67963241931357277, 0.48189607904294474);
	Eigen::Displacementd p6(0.44408295955948468, 0.01241106286408053, 0.66966075606684139, -0.72583622489357003, -0.34005998850496433, -0.58994234600386186, 0.097411535465335236);
	Eigen::Displacementd p7(0.44408295955948468, 0.01241106286408053, 0.66966075606684139, -0.33772857879309282, -0.8107157428040318, -0.3111036553014388, -0.3631720075861965);
	Eigen::Displacementd p8(0.44408295955948468, 0.01241106286408053, 0.66966075606684139, -0.33870416921432822, -0.80987604484114317, -0.31328308598562427, -0.36226231626353628);

	std::vector<Eigen::Displacementd> vd;
	vd.push_back(p1);
	vd.push_back(p2);
	vd.push_back(p3);
	vd.push_back(p4);
	vd.push_back(p5);
	vd.push_back(p6);
	vd.push_back(p7);
	vd.push_back(p8);

	//for(std::vector< RTT::OutputPort < tf::StampedTransform >* >::iterator it = _oports.begin();
	//		it != _oports.end();
	//		++it){
	for(int i=0; i<8; ++i){
		std::ostringstream ss_segment_name;
		ss_segment_name << "segment_" << i;
		tf::Transform transform;
		tf::LgsmDisplacementToTransformTF(vd[i], transform);

		static tf::TransformBroadcaster br;
		br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", ss_segment_name.str()));
	}
}

void Tf_publisher::stopHook(){
	std::cout << "Tf_publisher executes stopping !" <<std::endl;
}

void Tf_publisher::cleanupHook(){
	std::cout << "Tf_publisher cleaning up !" <<std::endl;
}

void Tf_publisher::createPorts(){
//	_oports.resize(number_of_segments);
//	for (unsigned int i=0; i<number_of_segments; i++){
//
//		std::ostringstream ss_segName;
//		ss_segName << "segment" << i;
//
//		_oports[i] = new RTT::OutputPort< tf::tfMessage >(ss_segName.str());
//		this->addPort(*(_oports[i]));
//	}

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


#include "Webcam.h"

int main(char *argv[], int argc)
{
	


	// Register Local Transport
	boost::shared_ptr<RobotRaconteur::LocalTransport> t1 = boost::make_shared<RobotRaconteur::LocalTransport>();
	t1->StartServerAsNodeName("example.webcam");
	RobotRaconteur::RobotRaconteurNode::s()->RegisterTransport(t1);

	// Register TCP Transport on port 2345
	boost::shared_ptr<RobotRaconteur::TcpTransport> t = boost::make_shared<RobotRaconteur::TcpTransport>();
	t->StartServer(2345);
	t->EnableNodeAnnounce(RobotRaconteur::IPNodeDiscoveryFlags_LINK_LOCAL |
		RobotRaconteur::IPNodeDiscoveryFlags_NODE_LOCAL |
		RobotRaconteur::IPNodeDiscoveryFlags_SITE_LOCAL);
	RobotRaconteur::RobotRaconteurNode::s()->RegisterTransport(t);

	// Register the service type with Robot Raconteur
	RobotRaconteur::RobotRaconteurNode::s()->RegisterServiceType(boost::make_shared<edu::rpi::cats::sensors::camera_interface::edu__rpi__cats__sensors__camera_interfaceFactory>());
	RobotRaconteur::RobotRaconteurNode::s()->RegisterServiceType(boost::make_shared<example::webcam::example__webcamFactory>());

	// Create the Webcam object
	RR_SHARED_PTR<Webcam> w = boost::make_shared<Webcam>();


	// Register the MathSolver object as a service
	RobotRaconteur::RobotRaconteurNode::s()->RegisterService("Webcam", "example.webcam", w);

	std::cout << "Connect to Webcam object at: " << std::endl;
	std::cout << "tcp://localhost:2345/example.webcam/Webcam" << std::endl;
	std::cout << "Press enter to quit" << std::endl;

	std::getline(std::cin, std::string());
	
	return 0;
}
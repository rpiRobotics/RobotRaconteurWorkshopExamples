
#include "MathSolver.h"

int main(int argc, char *argv[])
{
	// Register Local Transport
	boost::shared_ptr<RobotRaconteur::LocalTransport> t1 = boost::make_shared<RobotRaconteur::LocalTransport>();
	t1->StartServerAsNodeName("example.math");
	RobotRaconteur::RobotRaconteurNode::s()->RegisterTransport(t1);

	// Register TCP Transport on port 1234
	boost::shared_ptr<RobotRaconteur::TcpTransport> t = boost::make_shared<RobotRaconteur::TcpTransport>();
	t->StartServer(1234);
	t->EnableNodeAnnounce(RobotRaconteur::IPNodeDiscoveryFlags_LINK_LOCAL |
		RobotRaconteur::IPNodeDiscoveryFlags_NODE_LOCAL |
		RobotRaconteur::IPNodeDiscoveryFlags_SITE_LOCAL);
	RobotRaconteur::RobotRaconteurNode::s()->RegisterTransport(t);

	// Create the MathSolver object
	boost::shared_ptr<MathSolver> m = boost::make_shared<MathSolver>();

	// Register the service type with Robot Raconteur
	RobotRaconteur::RobotRaconteurNode::s()->RegisterServiceType(boost::make_shared<example::math::example__mathFactory>());


	// Register the MathSolver object as a service
	RobotRaconteur::RobotRaconteurNode::s()->RegisterService("MathSolver", "example.math", m);

	std::cout << "Connect to MathSolver object at: " << std::endl;
	std::cout << "tcp://localhost:1234/example.math/MathSolver" << std::endl;
	std::cout << "Press enter to quit" << std::endl;

	std::getline(std::cin, std::string());
	
	return 0;
}
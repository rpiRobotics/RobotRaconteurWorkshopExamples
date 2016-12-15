
#include "example__math.h"
#include "example__math_stubskel.h"

#include <RobotRaconteur.h>

int main(int argc, char *argv[])
{
	// Register Local Transport
	RR_SHARED_PTR<RobotRaconteur::LocalTransport> t1 = RR_MAKE_SHARED<RobotRaconteur::LocalTransport>();
	RobotRaconteur::RobotRaconteurNode::s()->RegisterTransport(t1);


	RR_SHARED_PTR<RobotRaconteur::TcpTransport> t = RR_MAKE_SHARED<RobotRaconteur::TcpTransport>();
	t->EnableNodeDiscoveryListening();
	RobotRaconteur::RobotRaconteurNode::s()->RegisterTransport(t);

	RR_SHARED_PTR<example::math::MathSolver> m = RobotRaconteur::rr_cast<example::math::MathSolver>(RobotRaconteur::RobotRaconteurNode::s()->ConnectService("tcp://localhost:1234/example.math/MathSolver"));
	//boost::shared_ptr<example::math::MathSolver> m = RobotRaconteur::rr_cast<example::math::MathSolver >(RobotRaconteur::RobotRaconteurNode::s()->ConnectService("tcp://localhost:1234/example.math/MathSolver", 
	//																																			"", 
	//																																			boost::shared_ptr<RobotRaconteur::RRMap<std::string, RobotRaconteur::RRObject> >(),
	//																																			NULL,
	//																																			"example.math"));

	std::cout << m->add(1, 2) << std::endl;
	std::vector<double> a1 = { 0, 1, 2 };
	std::vector<double> b1 = { 3, 4, 5 };
	RR_SHARED_PTR<RobotRaconteur::RRArray<double > > a = RobotRaconteur::AllocateRRArray<double>(a1.size()); 
	a = RobotRaconteur::AttachRRArrayCopy<double>(&a1[0], a1.size());
	RR_SHARED_PTR<RobotRaconteur::RRArray<double > > b = RobotRaconteur::AllocateRRArray<double>(b1.size());
	a = RobotRaconteur::AttachRRArrayCopy<double>(&b1[0], b1.size());
	std::cout << m->dot(a, b) << std::endl;
	std::cout << m->get_value() << std::endl;
	m->set_value(5);
	std::cout << m->get_value() << std::endl;
	std::vector<double> c1 = { 0, 5, 6, 3, 2 };
	RR_SHARED_PTR<RobotRaconteur::RRArray<double > > c = RobotRaconteur::AllocateRRArray<double>(c1.size());
	a = RobotRaconteur::AttachRRArrayCopy<double>(&c1[0], c1.size());
	RR_SHARED_PTR<RobotRaconteur::RRArray<double > > d = m->sort_sequence(c, "backward");
	for (int i = 0; i < d->size(); i++)
		std::cout << d->ptr()[i] << " ";
}
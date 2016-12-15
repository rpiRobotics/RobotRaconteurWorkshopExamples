
#ifdef SendMessage
#undef SendMessage
#endif


#include <RobotRaconteur.h>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>

#include "example__math.h"
#include "example__math_stubskel.h"

#include <Windows.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

#include <boost/enable_shared_from_this.hpp>
#include <map>

class MathSolver : public example::math::MathSolver, public boost::enable_shared_from_this < MathSolver >
{
public:

	MathSolver();

	virtual int32_t get_value();
	virtual void set_value(int32_t value);

	virtual double add(double a, double b);

	virtual double dot(RR_SHARED_PTR<RobotRaconteur::RRArray<double > > a, RR_SHARED_PTR<RobotRaconteur::RRArray<double > > b);

	virtual RR_SHARED_PTR<RobotRaconteur::RRArray<double > > sort_sequence(RR_SHARED_PTR<RobotRaconteur::RRArray<double > > seq, std::string dir);

private:
	int value;
	boost::mutex mtx_;
};
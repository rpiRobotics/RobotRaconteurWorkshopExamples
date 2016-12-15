
#include "MathSolver.h"

MathSolver::MathSolver()
{
	this->value = 0;
}

int32_t MathSolver::get_value()
{
	boost::lock_guard<boost::mutex> guard(mtx_);
	return this->value;
}
void MathSolver::set_value(int32_t value)
{
	boost::lock_guard<boost::mutex> guard(mtx_);
	this->value = value;
}

double MathSolver::add(double a, double b)
{
	boost::lock_guard<boost::mutex> guard(mtx_);
	return a + b;
}

double MathSolver::dot(RR_SHARED_PTR<RobotRaconteur::RRArray<double > > a, RR_SHARED_PTR<RobotRaconteur::RRArray<double > > b)
{
	boost::lock_guard<boost::mutex> guard(mtx_);
	double val = 0;
	if (a->size() == b->size())
	{
		
		for (int i = 0; i < a->size(); ++i)
			val += a->ptr()[i] * b->ptr()[i];
	}
	return val;
}

RR_SHARED_PTR<RobotRaconteur::RRArray<double > > MathSolver::sort_sequence(RR_SHARED_PTR<RobotRaconteur::RRArray<double > > seq, std::string dir)
{
	boost::lock_guard<boost::mutex> guard(mtx_);
	std::vector<double> my_seq = std::vector<double>(seq->size());
	my_seq.assign(seq->ptr(), seq->ptr() + seq->size());
	std::sort(my_seq.begin(), my_seq.end());
	if (strcmpi(dir.c_str(), "backward") == 0)
		std::reverse(my_seq.begin(), my_seq.end());

	RR_SHARED_PTR<RobotRaconteur::RRArray<double > > ret_seq = RobotRaconteur::AllocateRRArray<double>(my_seq.size());
	ret_seq = RobotRaconteur::AttachRRArrayCopy<double>(&my_seq[0], my_seq.size()); 
	return ret_seq;
}
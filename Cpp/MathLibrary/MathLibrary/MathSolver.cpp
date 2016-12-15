
#include "MathSolver.h"

MathSolver::MathSolver()
{
	value = 0;
}

double MathSolver::add(double a, double b)
{
	return a + b;
}

double MathSolver::dot(std::vector<double> a, std::vector<double> b)
{
	double val = 0;
	if (a.size() == b.size())
	{
		for (int i = 0; i < a.size(); ++i)
			val += a[i] * b[i];
	}
	return val;
}

int MathSolver::get_value()
{
	return value;
}

void MathSolver::set_value(int new_value)
{
	value = new_value;
}

std::vector<double> MathSolver::sort_sequence(std::vector<double> seq, std::string dir)
{
	std::sort(seq.begin(), seq.end());
	if (strcmpi(dir.c_str(), "backward") == 0)
		std::reverse(seq.begin(), seq.end());	
	return seq;
}
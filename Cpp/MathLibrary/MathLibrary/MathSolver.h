
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

class MathSolver
{
public:
	MathSolver();

	double add(double a, double b);
	double dot(std::vector<double> a, std::vector<double> b);

	int get_value();
	void set_value(int new_value);

	std::vector<double> sort_sequence(std::vector<double> seq, std::string dir);

private:
	int value;
};
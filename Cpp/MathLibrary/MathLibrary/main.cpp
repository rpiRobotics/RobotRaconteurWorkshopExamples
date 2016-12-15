
#include "MathSolver.h"

int main(int argc, char *argv[])
{
	MathSolver m = MathSolver();

	std::cout << m.add(1, 2) << std::endl;
	std::vector<double> a = { 0, 1, 2 };
	std::vector<double> b = { 3, 4, 5 };
	std::cout << m.dot(a, b) << std::endl;
	std::cout << m.get_value() << std::endl;
	m.set_value(5);
	std::cout << m.get_value() << std::endl;
	std::vector<double> c = { 0, 5, 6, 3, 2 };
	//std::vector<double> d = m.sort_sequence(c, "backward");
	std::vector<double> d = m.sort_sequence(c, "forward");
	for (int i = 0; i < d.size(); i++)
		std::cout << d[i] << " ";

	return 0;
}
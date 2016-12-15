clear variables; close all;

math_solver = RobotRaconteur.ConnectService('tcp://localhost:1234/example.math/MathSolver');

math_solver.add(1,2)
math_solver.dot([0;1;2],[3;4;5])
math_solver.value
math_solver.value = int32(5);
math_solver.value
math_solver.sort_sequence([0;5;6;3;2], 'backward')
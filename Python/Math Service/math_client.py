
import RobotRaconteur as RR
# Convenient shorthand
RRN = RR.RobotRaconteurNode.s


def main():
    # Use NumPy
    RRN.UseNumPy = True
    
    # Register a Local Transport
    t1 = RR.LocalTransport()
    RRN.RegisterTransport(t1)
    
    # Register a TCP Transport
    t2 = RR.TcpTransport()
    RRN.RegisterTransport(t2)
    
    #math_solver = RRN.ConnectService('tcp://localhost:1234/example.math/MathSolver')
    math_solver = RRN.ConnectService('tcp://10.0.1.25:1234/example.math/MathSolver')
    
    print math_solver.add(1,2)
    print math_solver.dot([0,1,2],[3,4,5])
    print math_solver.value
    math_solver.value = 5
    print math_solver.value
    print math_solver.sort_sequence([0,5,6,3,2], "backward")
    
    raw_input("press enter to quit")
    
    # THIS MUST BE HERE
    RRN.Shutdown()

if __name__ == '__main__':
    main()
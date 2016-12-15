import RobotRaconteur as RR
# Convenient shorthand
RRN = RR.RobotRaconteurNode.s
import thread
import threading
import numpy # Numerical Toolbox for Python

class MathSolver(object):
        
    # Constructor
    def __init__(self):
        print "Created MathSolver Object"
        self._value = 0
        self._lock = threading.RLock()
    
    # add 2 numbers
    def add(self,a,b):
        with self._lock:
            return a + b
    
    # vector dot product
    def dot(self,a,b):
        with self._lock:
            if len(a) == len(b):
                return numpy.dot(a,b)
            return None
    
    @property
    def value(self):
        with self._lock:
            return self._value
    
    @value.setter
    def value(self, new_val):
        with self._lock:
            self._value = new_val
    
    def sort_sequence(self, seq, dir):
        with self._lock:
            return sorted(seq, reverse=(dir.lower() == "backward"))
    
# Main Function
def main():
    RRN.UseNumPy = True
    
    # Create and Register Local Transport (names the node example.math)
    t1 = RR.LocalTransport()
    t1.StartServerAsNodeName("example.math")
    RRN.RegisterTransport(t1)
    
    # Create and Register TCP Transport
    t2 = RR.TcpTransport()
    t2.EnableNodeAnnounce()
    t2.StartServer(1234)
    RRN.RegisterTransport(t2)
    
    # read in Service Definition File
    with open('math_service.robdef','r') as f:
        service_def = f.read()
    
    # Register Service Definition
    RRN.RegisterServiceType(service_def)
    
    # Create instance of MathSolver object
    solver_obj = MathSolver()
    
    # Register Service 'MathSolver' of type 'example.math.MathSolver'
    RRN.RegisterService("MathSolver","example.math.MathSolver", solver_obj)
    
    print "Connect to MathSolver object at:"
    # address : port / node name / service
    print "tcp://localhost:1234/example.math/MathSolver"
    raw_input('press enter to quit')
    
    # THIS MUST BE HERE OR RISK SEGFAULT
    RRN.Shutdown()

# Entry point for program
if __name__== '__main__':
    main()
    
    
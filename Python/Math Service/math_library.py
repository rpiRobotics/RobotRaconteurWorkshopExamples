import numpy # Numerical Toolbox for Python

class MathSolver(object):
        
    # Constructor
    def __init__(self):
        print "Created MathSolver Object"
        self._value = 0
    
    # add 2 numbers
    def add(self,a,b):
        return a + b
    
    # vector dot product
    def dot(self,a,b):
        if len(a) == len(b):
            return numpy.dot(a,b)
        return None
    
    @property
    def value(self):
        return self._value
    
    @value.setter
    def value(self, new_val):
        self._value = new_val
    
    def sort_sequence(self, seq, dir):
        return sorted(seq, reverse=(dir.lower() == "backward"))
    
# Main Function
def main():
    s = MathSolver()
    print s.add(1,2)
    print s.dot([0,1,2],[3,4,5])
    print s.value
    s.value = 5
    print s.value
    print s.sort_sequence([0,5,6,3,2], "backward")
    
    raw_input("enter to quit")
    
# Entry point for program
if __name__== '__main__':
    main()
    
    
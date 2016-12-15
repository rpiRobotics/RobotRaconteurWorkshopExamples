import time
import RobotRaconteur as RR
# Convenient shorthand
RRN = RR.RobotRaconteurNode.s
import thread
import threading
import numpy
import traceback
import cv2.cv as cv

class Webcam(object):
    def __init__(self):
        # Lock for multithreading
        self._lock = threading.RLock()
                
        # initialize camera
        self._cam = cv.CaptureFromCAM(0)
        self._streaming = False
        
        # initialize constant properties of image
        self._imgsize = RRN.NewStructure("edu.rpi.cats.sensors.camera_interface.ImageHeader")
        self._imgsize.width = 0
        self._imgsize.height = 0
        self._imgsize.channels = 0
        self._imgsize.step = 0
        
        if not self._cam:
            print "Camera Not Found!"
        else:
            img = cv.QueryFrame(self._cam)
            frame = cv.GetMat(img)
            self._imgsize.width = frame.width
            self._imgsize.height = frame.height
            self._imgsize.step = frame.step / frame.width
            self._imgsize.channels = len(frame[0,0])
        
        # For the image stream pipe
        self._imagestream=None
        
    @property 
    def camera_found(self):
        if self._cam:
            return 1
        return 0
    
    @camera_found.setter
    def camera_found(self, val):
        return None # do nothing
    
    def StartStreaming(self):
        if (self._streaming):
            return
        self._streaming = True
        thread.start_new_thread(self.streaming_threadfunc,())
    
    def StopStreaming(self):
        if (not self._streaming):
            return
        self._streaming = False
    
    def captureImage(self):
        with self._lock:
            img = cv.QueryFrame(self._cam)
            self._frame = cv.GetMat(img)
    
    def getImageHeader(self):
        with self._lock:
            return self._imgsize
    
    def getCurrentImage(self):
        with self._lock:
            if (not self._streaming):
                self.captureImage()
            RRimg = RRN.NewStructure("edu.rpi.cats.sensors.camera_interface.Image")
            RRimg.width = self._imgsize.width
            RRimg.height = self._imgsize.height
            RRimg.channels = self._imgsize.channels
            RRimg.data = numpy.frombuffer(self._frame.tostring(),dtype="u1")
            return RRimg

    def streaming_threadfunc(self):
        # Loop while streaming
        while(self._streaming):
            # read in image
            try:
                self.captureImage()
            except:
                self._streaming = False
                return
            
            RRimg = self.getCurrentImage()
            
            #Send the new frame to the broadcaster.  Use AsyncSendPacket
            #and a blank handler.  We really don't care when the send finishes
            #since we are using the "backlog" flow control in the broadcaster.
            self._imagestream_broadcaster.AsyncSendPacket(RRimg, lambda: None)
            # Put in artificial delay
            time.sleep(1.0/20)
    
    # pipe getter/setter
    @property
    def ImageStream(self):
        return self._imagestream
    
    @ImageStream.setter
    def ImageStream(self, value):
        self._imagestream = value
        #Create the PipeBroadcaster and set backlog to 3 so packets
        #will be dropped if the transport is overloaded
        self._imagestream_broadcaster = RR.PipeBroadcaster(value,3)
    
    def Shutdown(self):
        self.StopStreaming()
        time.sleep(1.0)
        if self._cam:
            del(self._cam)
    
def main():
    try:
        RRN.UseNumPy = True
        
        # Register Local Transport
        t1 = RR.LocalTransport()
        t1.StartServerAsNodeName("example.webcam")
        RRN.RegisterTransport(t1)
        
        # Register TCP Transport
        t2 = RR.TcpTransport()
        t2.EnableNodeAnnounce()
        t2.StartServer(2345)
        RR.RobotRaconteurNode.s.RegisterTransport(t2)
        
        # read in robot service definitions
        with open('camera_interface.robdef','r') as f:
            service_def = f.read()
            # Register Service Type within Robot Raconteur
            RRN.RegisterServiceType(service_def)
        with open('webcam_service.robdef','r') as f:
            service_def = f.read()
            # Register Service Type within Robot Raconteur
            RRN.RegisterServiceType(service_def)
        
        # Create instance of Webcam object
        webcam_obj = Webcam()
        
        RR.RobotRaconteurNode.s.RegisterService("Webcam","example.webcam.Webcam",webcam_obj)
        
        print "Connect to Webcam object at:"
        print "tcp://localhost:2345/example.webcam/Webcam"
        raw_input("Press Enter to Quit")
        
        webcam_obj.Shutdown()
    except:
        print "error!"
    finally:
        # THIS MUST BE HERE OR RISK SEGFAULT
        RRN.Shutdown()
    
if __name__ == '__main__':
    main()
        
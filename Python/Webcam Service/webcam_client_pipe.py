import numpy
import RobotRaconteur as RR
# Convenient shorthand
RRN = RR.RobotRaconteurNode.s
import cv2.cv as cv


class WebcamClient(object):
    def __init__(self, webcam):
        self._img = None
        RRimg_header = webcam.getImageHeader()
        self.init_image(RRimg_header)
        self._image_pipe = webcam.ImageStream.Connect(-1)
        self._image_pipe.PacketReceivedEvent+=self.new_frame
        try:
            webcam.StartStreaming()
        except: pass
        
    def current_image(self):
        return self._img
    
    def init_image(self, img_header):
        c = img_header.channels
        if c == 1:
            self._img = cv.CreateMat(img_header.height, img_header.width, cv.CV_8UC1)
        elif c == 3:
            self._img = cv.CreateMat(img_header.height, img_header.width, cv.CV_8UC3)
        elif c == 4:
            self._img = cv.CreateMat(img_header.height, img_header.width, cv.CV_8UC4)
    
    def new_frame(self, pipe_ep):        
        while (pipe_ep.Available > 0):
            RRimg = pipe_ep.ReceivePacket()
            cv.SetData(self._img, RRimg.data.tostring())
    
    def shutdown(self):
        self._image_pipe.Close()
        

def main():
    # Use NumPy
    RRN.UseNumPy = True
    
    # Register a Local Transport
    t1 = RR.LocalTransport()
    RRN.RegisterTransport(t1)
    
    # Register a TCP Transport
    t2 = RR.TcpTransport()
    RRN.RegisterTransport(t2)
    
    webcam = RRN.ConnectService('tcp://localhost:2345/example.webcam/Webcam');
    if webcam.camera_found > 0:
        
        webcam_client = WebcamClient(webcam)
        
        cv.NamedWindow("Image")
        
        while True:
            I = webcam_client.current_image()
            if (not I is None):
                cv.ShowImage("Image", I)
            if cv.WaitKey(50) > 0:
                break
        
        cv.DestroyAllWindows()
        webcam_client.shutdown()
        webcam.StopStreaming()

    # THIS MUST BE HERE OR RISK SEGFAULT
    RRN.Shutdown()

if __name__ == '__main__':
    main()
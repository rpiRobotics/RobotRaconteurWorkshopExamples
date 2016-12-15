import numpy
import RobotRaconteur as RR
# Convenient shorthand
RRN = RR.RobotRaconteurNode.s
import cv2.cv as cv

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
        cv.NamedWindow("Image")
        
        img_header = webcam.getImageHeader()
        c = img_header.channels
        if c == 1:
            current_image = cv.CreateMat(img_header.height, img_header.width, cv.CV_8UC1)
        elif c == 3:
            current_image = cv.CreateMat(img_header.height, img_header.width, cv.CV_8UC3)
        elif c == 4:
            current_image = cv.CreateMat(img_header.height, img_header.width, cv.CV_8UC4)
        
        webcam.StartStreaming()
        while True:
            RRimg = webcam.getCurrentImage()
            cv.SetData(current_image, RRimg.data.tostring())
            if (not current_image is None):
                cv.ShowImage("Image", current_image)
            if cv.WaitKey(50) > 0:
                break
        
        cv.DestroyAllWindows()
        webcam.StopStreaming()

    # THIS MUST BE HERE OR RISK SEGFAULT
    RRN.Shutdown()

if __name__ == '__main__':
    main()
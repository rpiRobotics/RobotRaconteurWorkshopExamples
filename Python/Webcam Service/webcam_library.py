
import time
import thread
import threading
import numpy # Numerical Toolbox for Python
import cv2.cv as cv # OpenCV

class Webcam(object):
    def __init__(self):
        # Lock for multithreading
        self._lock = threading.RLock()
        
        # initialize camera
        self._cam = cv.CaptureFromCAM(0)
        self._streaming = False
        img = cv.QueryFrame(self._cam)
        self._frame = cv.GetMat(img)
        
        if not self._cam:
            print "Camera Not Found!"
    
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
        
    def getCurrentImage(self):
        with self._lock:
            if (not self._streaming):
                captureImage()
            return self._frame
    
    def streaming_threadfunc(self):
        # Loop while streaming
        while(self._streaming):
            # read in image
            try:
                self.captureImage()
            except:
                self._streaming = False
                return
            # Put in artificial delay
            time.sleep(1.0/20)
    
    def Shutdown(self):
        self.StopStreaming()
        time.sleep(1.0)
        if self._cam:
            del(self._cam)

def main():
    
    webcam = Webcam()
    
    if webcam.camera_found > 0:
        cv.NamedWindow("Image")
        
        webcam.StartStreaming()
        while True:
            current_image = webcam.getCurrentImage()
            if (not current_image is None):
                cv.ShowImage("Image", current_image)
            if cv.WaitKey(50) > 0:
                break
        
        cv.DestroyAllWindows()
    
    webcam.Shutdown()
    
if __name__ == '__main__':
    main()

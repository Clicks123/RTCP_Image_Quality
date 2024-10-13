import numpy as np
import cv2 as cv

cap = cv.VideoCapture(0, cv.CAP_DSHOW)
cap1 = cv.VideoCapture(0, cv.CAP_DSHOW)
if not cap.isOpened():
 print("Cannot open camera")
 exit()
if not cap1.isOpened():
 print("Cannot open camera")
 exit()
while True:
 # Capture frame-by-frame
 ret, frame = cap.read()
 ret1, frame1 = cap1.read()
 # if frame is read correctly ret is True
 if not ret:
    print("Can't receive frame (stream end?). Exiting ...")
    break
 if not ret1:
    print("Can't receive frame1 (stream end?). Exiting ...")
    break
 # Our operations on the frame come here
 gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY) #this will convert frame to gray scale
 # Display the resulting frame
 cv.imshow('frame', gray)
 cv.imshow('frame1', frame1)
 if cv.waitKey(1) == ord('q'):
    break

# When everything done, release the capture
cap.release()
cap1.release()
cv.destroyAllWindows()
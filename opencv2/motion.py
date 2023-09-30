import cv2
import time 
import os

width, height = 640, 480

cap = cv2.VideoCapture(0)
cap.set(3,width)
cap.set(4,height)

while True:
    ret, frame = cap.read()

    cv2.imshow("Frame", frame)

    key = cv2.waitKey(1)
    if key == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
import cv2
import time 
import os
import HandDetector as hd
import Xlib.display
import numpy as np
#import libclicker as lb
import uinput

#mouse input keys
keys = [
    uinput.BTN_LEFT,
    uinput.BTN_MIDDLE,
    uinput.BTN_RIGHT,
    uinput.REL_X,
    uinput.REL_Y,
    uinput.REL_WHEEL,
    uinput.REL_HWHEEL,
]

#starting Device
device = uinput.Device(keys)

# Wait for the system to detect the new device
time.sleep(1)

def move_mouse(x : int, y : int):
    device.emit(uinput.REL_X, -25000)
    device.emit(uinput.REL_Y, -25000)
    device.emit(uinput.REL_X, x//2)
    device.emit(uinput.REL_Y, y//2)


def get_screen_resolution():
    display = Xlib.display.Display()
    screen = display.screen()
    width = screen.width_in_pixels
    height = screen.height_in_pixels
    return width, height

screen_width, screen_height = get_screen_resolution()
print(f"Screen Resolution: {screen_width}x{screen_height}")

width, height = 640, 480

cap = cv2.VideoCapture(0)
cap.set(3,width)
cap.set(4,height)
#hand detector
detector = hd.handDetector(maxHands=1)

#previous Frame
pTime = 0

while True:

    #image and Hand Detection
    ret, img = cap.read()
    img = detector.findHand(img,draw=False)
    lmList, bbox = detector.findPosition(img)

    #tip and thumb
    if len(lmList)!=0:
        x1,y1 = lmList[8][1:]
        x2,y2 = lmList[4][1:]
        #print(f"Tip: [{x1},{x2}] Thumb: [{x2},{y2}]")

        #fingers Up
        fingers = detector.fingersUp()
        
        #tip Up, move Mode
        if fingers[1] == 1 and fingers[0] == 0:
            x3 = np.interp(x1,(0,width),(0,screen_width))
            y3 = np.interp(y1,(0,height),(0,screen_height))
            move_mouse(x1,y1)
            time.sleep(0.02)


        
    
     
            
    
    #fpsDisplay
    cTime = time.time()
    fps = 1/(cTime-pTime)
    pTime = cTime
    cv2.putText(img,str(int(fps)),(20,50),cv2.FONT_HERSHEY_PLAIN,3,(255,0,0),3)

    cv2.imshow("Frame", img)

    key = cv2.waitKey(1)
    if key == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
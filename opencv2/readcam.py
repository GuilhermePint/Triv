import cv2
import numpy as np
import libclicker as lb

cap = cv2.VideoCapture("RGB.mp4")

# video framerate
fps = 24
delay = 1000 // fps

# image size
width = 60
height = 60

# red -> brownnoise
red_audio = False
green_audio = False
blue_audio = False

while True:
    ret, frame = cap.read()

    if not ret:
        cap.set(cv2.CAP_PROP_POS_FRAMES, 0)
        continue

    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # limit to red
    lower_red = np.array([0, 100, 100])
    higher_red = np.array([10, 255, 255])

    # create mask
    mask = cv2.inRange(hsv_frame, lower_red, higher_red)

    # read red pixels
    red_pixels = cv2.countNonZero(mask)

    if red_pixels > 1000 and not red_audio:
        print("Vermelho")
        lb.click(50,60,2,1)
        red_audio = True

    elif red_pixels == 0:
        red_audio = False

    cv2.imshow("Frame", frame)

    key = cv2.waitKey(delay)
    if key == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()

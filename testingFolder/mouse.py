import uinput

with uinput.Device([uinput.REL_X, uinput.REL_Y,
                    uinput.BTN_LEFT, uinput.BTN_RIGHT]) as device:
    for i in range(20):
        device.emit(uinput.REL_X, 5)
        device.emit(uinput.REL_Y, 5)
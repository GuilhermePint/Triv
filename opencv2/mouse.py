import libclicker as lb
import Xlib.display

#lb.click(1920,1080,2,1)

def get_screen_resolution():
    display = Xlib.display.Display()
    screen = display.screen()
    width = screen.width_in_pixels
    height = screen.height_in_pixels
    return width, height

screen_width, screen_height = get_screen_resolution()
print(f"Screen Resolution: {screen_width}x{screen_height}")
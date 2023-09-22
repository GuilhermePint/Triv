#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>

int main() {
    int fd;
    char video_device[32]; //Iterar até 32 dispositivos
    int index = 0;

    while (1) {
        snprintf(video_device, sizeof(video_device), "/dev/video%d", index);
        fd = open(video_device, O_RDONLY);

        if (fd == -1) {
            
            break;
        }

        struct v4l2_capability cap;
        memset(&cap, 0, sizeof(struct v4l2_capability));

        if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1) {
            perror("VIDIOC_QUERYCAP");
            close(fd);
            exit(1);
        }

        printf("Video Device %d:\n", index);
        printf("  Driver: %s\n", cap.driver);
        printf("  Card: %s\n", cap.card);
        printf("  Bus Info: %s\n", cap.bus_info);
        printf("  Version: %d\n", cap.version);
        printf("  Capabilities: 0x%08X\n", cap.capabilities);
        printf("\n");

        close(fd);
        index++;
    }

    if (index == 0) {
        printf("No video devices found.\n");
    }

    return 0;
}
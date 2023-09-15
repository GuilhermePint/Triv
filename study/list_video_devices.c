#include <linux/videodev2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void list_video_devices() {
    int fd;
    struct v4l2_capability cap;
    char video_device[16]; 

    for (int i = 0; i < 10; i++) { 
        snprintf(video_device, sizeof(video_device), "/dev/video%d", i);

        fd = open(video_device, O_RDWR);
        if (fd == -1) {
            continue; 
        }

        if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == 0) {
            printf("Video Device %d: %s\n", i, cap.card);
        }

        close(fd);
    }
}

int main() {
    list_video_devices();

    return 0;
}
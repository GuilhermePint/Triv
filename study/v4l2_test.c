#include <linux/videodev2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct v4l2_input input;
int input_index; 

int main() {
    int fd = 0;

    if (-1 == ioctl(fd, VIDIOC_G_INPUT, &input_index)) {
        perror("VIDIOC_G_INPUT");
        exit(EXIT_FAILURE);
    }

    memset(&input, 0, sizeof(input));
    input.index = input_index;

    if (-1 == ioctl(fd, VIDIOC_ENUMINPUT, &input)) {
        perror("VIDIOC_ENUMINPUT");
        exit(EXIT_FAILURE);
    }

    printf("Current input: %s\\n", input.name);

    return 0;
}
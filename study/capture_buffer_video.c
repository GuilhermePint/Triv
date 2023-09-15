#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <sys/mman.h>

#define VIDEO_DEVICE "/dev/video0"

int main()
{
    int fd;
    struct v4l2_format fmt;
    struct v4l2_requestbuffers reqbuf;
    struct v4l2_buffer buf;

    // Open the video device
    fd = open(VIDEO_DEVICE, O_RDWR);
    if (fd == -1)
    {
        perror("Error opening the video device");
        exit(EXIT_FAILURE);
    }

    // (YU12 format)
    memset(&fmt, 0, sizeof(fmt));
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = 640;                       // Frame width
    fmt.fmt.pix.height = 480;                      // Frame height
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUV420; // Pixel format (YU12)

    if (ioctl(fd, VIDIOC_S_FMT, &fmt) == -1)
    {
        perror("Error configuring video format");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Request video buffers for capture
    memset(&reqbuf, 0, sizeof(reqbuf));
    reqbuf.count = 1; // Number of desired video buffers (1 to capture a single frame)
    reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbuf.memory = V4L2_MEMORY_MMAP;

    if (ioctl(fd, VIDIOC_REQBUFS, &reqbuf) == -1)
    {
        perror("Error requesting video buffers");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Map the video buffer
    struct buffer
    {
        void *start;
        size_t length;
    } buffer;

    memset(&buf, 0, sizeof(buf));
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;

    if (ioctl(fd, VIDIOC_QUERYBUF, &buf) == -1)
    {
        perror("Error querying video buffer");
        close(fd);
        exit(EXIT_FAILURE);
    }

    buffer.length = buf.length;
    buffer.start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);

    if (buffer.start == MAP_FAILED)
    {
        perror("Error mapping video buffer");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Start video capture
    if (ioctl(fd, VIDIOC_QBUF, &buf) == -1)
    {
        perror("Error queuing video buffer");
        close(fd);
        munmap(buffer.start, buffer.length);
        exit(EXIT_FAILURE);
    }

    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(fd, VIDIOC_STREAMON, &type) == -1)
    {
        perror("Error starting video capture");
        close(fd);
        munmap(buffer.start, buffer.length);
        exit(EXIT_FAILURE);
    }

    // Capture video frames
    if (ioctl(fd, VIDIOC_DQBUF, &buf) == -1)
    {
        perror("Error dequeuing video buffer");
        close(fd);
        munmap(buffer.start, buffer.length);
        exit(EXIT_FAILURE);
    }

    // Process and display the captured frame
    unsigned char *y_plane = (unsigned char *)buffer.start;
    unsigned char *u_plane = y_plane + (fmt.fmt.pix.width * fmt.fmt.pix.height);
    unsigned char *v_plane = u_plane + ((fmt.fmt.pix.width * fmt.fmt.pix.height) / 4);

    // Stop video capture
    if (ioctl(fd, VIDIOC_STREAMOFF, &type) == -1)
    {
        perror("Error stopping video capture");
    }

    // Close the video device and free memory
    close(fd);
    munmap(buffer.start, buffer.length);

    return 0;
}

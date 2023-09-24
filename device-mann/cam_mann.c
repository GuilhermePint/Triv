#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>           //system file control
#include <unistd.h>          //unix standard
#include <sys/ioctl.h>       //ioctl *importante para utilização do v4l2*
#include <linux/videodev2.h> // v4l2

// definir tamanho da webcam
#define WIDTH 640
#define HEIGHT 480
// definir formato de vídeo
#define FRAME_FORMAT V4L2_PIX_FMT_YVU420

int main()
{
    // abrir o dispositivo virtual localizado em /dev/video0
    int fd = open("/dev/video0", O_RDWR);
    if (fd == -1)
    {
        perror("Falha ao abrir Dispositivo Virtual de Webcam");
        return 1;
    }
    close(fd);

    struct v4l2_format format;
    memset(&format, 0, sizeof(format));
    // selecionar formato da camera virtual
    format.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    format.fmt.pix.width = WIDTH;
    format.fmt.pix.height = HEIGHT;
    format.fmt.pix.pixelformat = PIXEL_FORMAT;

    // utiliza do ioctl para configurar a webcam de acordo com a estrutura citada acima (format)
    if (ioctl(fd, VIDIOC_S_FMT, &format) == -1)
    {
        perror("Erro ao configurar formato");
        close(fd);
        return 1;
    }

    return 0;
}

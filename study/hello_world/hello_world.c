#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/genhd.h>  // Para informações de dispositivos de bloco
#include <linux/blkdev.h>

MODULE_AUTHOR("Guilherme Pinto");
MODULE_DESCRIPTION("Módulo de Teste");
MODULE_INFO(difficulty, "Fácil");
MODULE_LICENSE("GPL");

struct v4l2_input input;
int index;

if (-1 == ioctl(fd, VIDIOC_G_INPUT, &index)) {
    perror("VIDIOC_G_INPUT");
    exit(EXIT_FAILURE);
}

memset(&input, 0, sizeof(input));
input.index = index;

if (-1 == ioctl(fd, VIDIOC_ENUMINPUT, &input)) {
    perror("VIDIOC_ENUMINPUT");
    exit(EXIT_FAILURE);
}

printf("Current input: %s\\n", input.name);

module_init(list_devices);
module_exit(cleanup_devices);
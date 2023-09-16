#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Guilherme Pinto");
MODULE_DESCRIPTION("Módulo de Teste");
MODULE_INFO(difficulty, "Fácil");
MODULE_LICENSE("GPL");


static struct snd_pcm_hardware my_pcm_hw = {
    .info = (SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED),
    .formats = SNDRV_PCM_FMTBIT_S16_LE,
    .rates = SNDRV_PCM_RATE_CONTINUOUS,
    .rate_min = 8000,
    .rate_max = 48000,
    .channels_min = 2,
    .channels_max = 2,
};

static struct snd_pcm_ops my_pcm_ops = {
    .open = my_pcm_open,
    .close = my_pcm_close,
    .hw_params = my_pcm_hw_params,
    .prepare = my_pcm_prepare,
    .trigger = my_pcm_trigger,
    .pointer = my_pcm_pointer,
};

static struct snd_card my_soundcard = {
    .shortname = "myalsa",
    .longname = "My ALSA Audio",
};

static int __init my_alsa_module_init(void) {
    int err;

    pr_info("Initializing My ALSA Audio Module\n");

    err = snd_card_create(-1, "myalsa", THIS_MODULE, 0, &my_soundcard);
    if (err < 0) {
        pr_err("Failed to create sound card\n");
        return err;
    }

    /* Register PCM device */
    if ((err = snd_pcm_new(my_soundcard, "mypcm", 0, 1, 0, &my_pcm)) < 0) {
        pr_err("Failed to create PCM device\n");
        goto failed;
    }

    my_pcm->private_data = NULL;
    strcpy(my_pcm->name, "My PCM");
    my_pcm->info_flags = 0;

    my_pcm->ops = &my_pcm_ops;

    return 0;

failed:
    snd_card_free(my_soundcard);
    return err;
}

static void my_alsa_module_exit(void)
{
    pr_info("Exiting My ALSA Audio Module\n");

    if (my_pcm) {
        snd_pcm_free(my_pcm);
    }

    if (my_soundcard) {
        snd_card_free(my_soundcard);
    }
}

module_init(my_alsa_module_init);
module_exit(my_alsa_module_exit);

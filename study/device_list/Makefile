obj-m := device_list.o
KDIR ?= /lib/modules/$(shell uname -r)/build
CC := gcc-11  # Set the correct compiler
all: modules
install: modules_install
modules modules_install help clean:
	$(MAKE) -C $(KDIR) M=$(shell pwd) $(@)
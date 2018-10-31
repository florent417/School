ifeq ($(KERNELRELEASE),)

KERNELDIR = ~/sources/rpi-4.14/
CCPREFIX = arm-poky-linux-gnueabi-

PWD := $(shell pwd) #current dir

default:
		$(MAKE) ARCH=arm CROSS_COMPILE=$(CCPREFIX) -C $(KERNELDIR) M=$(PWD) modules
clean:
		rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.order Module.symvers

.PHONY: modules clean

else
			obj-m := hello.o
			ccflags-y := -DDEBUG -g -std=gnu99 -Wno-declaration-after-statement -Werror
endif

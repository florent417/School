ifeq ($(KERNELRELEASE),)
# If we are NOT invoked from the
# kernel build system (KERNELRELEASE = ””)
KERNELDIR = ~/sources/rpi-4.14/
PWD := $(shell pwd)
default:
	$(MAKE) ARCH=arm CROSS_COMPILE=arm-poky-linux-gnueabi- -C $(KERNELDIR) M=$(PWD) modules
# called from kernel build system:
# just declare what our modules are
else
# $(obj-m) specifies object files which are built as loadable	kernel modules.
	obj-m := SWDriver.o
	ccflags-y := -std=gnu99 -Wno-declaration-after-statement -Werror
endif

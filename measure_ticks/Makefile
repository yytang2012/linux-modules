export ARCH=ARM

obj-m += enable_the_performance_counter.o

ifeq ($(ARCH), ARM)
	export ARCH=arm
	export CROSS_COMPILE=arm-linux-gnueabihf-
	export BUILD=~/projects/chromebook/linux-kvm-arm
else
	export BUILD=/lib/modules/$(shell uname -r)/build
endif
all:
	make -C $(BUILD) M=$(PWD) modules
clean:
	make -C $(BUILD) M=$(PWD) clean

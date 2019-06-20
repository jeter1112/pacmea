obj-m += spoof.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
insmod:
	sudo insmod spoof.ko
rmmod:
	sudo rmmod spoof
route:
	@echo `sudo route del default enp4s0 2> /dev/null` >/dev/null

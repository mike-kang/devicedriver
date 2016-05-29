KDIR = /lib/modules/$(shell uname -r)/build
#KDIR = /home/mikeakng/work/rasp/linux

obj-m := nl.o

default:
	$(MAKE) -C $(KDIR) M=$$PWD modules

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean


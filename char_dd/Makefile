#KDIR = /lib/modules/3.18.7-v7/build
KDIR = /home/mikeakng/work/rasp/linux

obj-m := char_sk.o

default:
	$(MAKE) -C $(KDIR) M=$$PWD modules

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean


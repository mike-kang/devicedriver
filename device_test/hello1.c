#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/slab.h>


MODULE_LICENSE("Dual BSD/GPL");

static struct class *cuse_class;
struct device		*dev;


static int hello_init(void)
{
  printk(KERN_ALERT "Hello, world\n");

 	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return 1;;

  cuse_class = class_create(THIS_MODULE, "cuse");
  if (IS_ERR(cuse_class))
    return PTR_ERR(cuse_class);

  //cuse_class->dev_groups = cuse_class_dev_groups;

	device_initialize(dev);
	dev_set_uevent_suppress(dev, 1);
	dev->class = cuse_class;
	//dev->devt = devt;
	//dev->release = cuse_gendev_release;
	//dev_set_drvdata(dev, cc);
	dev_set_name(dev, "%s", "kang");

  int rc = device_add(dev);
  return 0;
}

static void hello_exit(void)
{
  printk(KERN_ALERT "Goodbye, cruel world\n");

  device_del(dev);
  class_destroy(cuse_class);
}

module_init(hello_init);
module_exit(hello_exit);

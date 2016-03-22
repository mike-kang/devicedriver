#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/slab.h>


MODULE_LICENSE("Dual BSD/GPL");

static struct class *parent_class;
static struct class *child_class;

struct device		*dev;
struct device		*dev_child;

static int hello_init(void)
{
  printk(KERN_ALERT "Hello, world\n");

  dev = kzalloc(sizeof(*dev), GFP_KERNEL);
  if (!dev)
    return 1;;

  parent_class = class_create(THIS_MODULE, "parent");
  if (IS_ERR(parent_class))
    return PTR_ERR(parent_class);

  device_initialize(dev);
  dev_set_uevent_suppress(dev, 1);
  dev->class = parent_class;
  dev_set_name(dev, "%s", "kang");

  int rc = device_add(dev);

  //child
  dev_child = kzalloc(sizeof(*dev_child), GFP_KERNEL);
  if (!dev_child)
    return 1;;
  child_class = class_create(THIS_MODULE, "child");

  device_initialize(dev_child);
  dev_set_uevent_suppress(dev_child, 1);
  dev_child->class = child_class;
  dev_set_name(dev_child, "%s", "san");
  dev_child->parent = dev;
  rc = device_add(dev_child);
  printk("child kobject %p\n", dev_child->kobj.sd);

  return 0;
}

static void hello_exit(void)
{
  printk(KERN_ALERT "Goodbye, cruel world\n");

  device_del(dev);
  device_del(dev_child);
  class_destroy(parent_class);
  class_destroy(child_class);
}

module_init(hello_init);
module_exit(hello_exit);

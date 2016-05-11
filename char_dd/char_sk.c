#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>                              /* open( ), read( ), write( ), close( ) 커널 함수 */
#include <linux/cdev.h>

struct cdev cdev;
dev_t dev = 0;	

MODULE_LICENSE("Dual BSD/GPL");

static int csk_open(struct inode *inod, struct file *fil)
{
  printk("CSK Device opened(%d/%d)\n", imajor(inod), iminor(inod));
  return 0;
}

static int csk_release(struct inode *inod, struct file *fil)
{
  printk("CSK Device closed\n");
  return 0;
}

static ssize_t csk_read(struct file *fil, char *buff, size_t len, loff_t *off)
{
  printk("CSK Device read : \n");
  return 0;
}

static ssize_t csk_write(struct file *fil, const char *buff, size_t len, loff_t *off)
{
  printk("CSK Device write : \n");
  return 0;
}

static struct file_operations csk_fops = {
  .owner = THIS_MODULE,
 
  .read = csk_read,
  .write = csk_write,
  .open = csk_open,
  .release = csk_release,
};

static int csk_init(void)
{
  int err;

  printk(KERN_ALERT "Hello, world\n");
  alloc_chrdev_region(&dev, 0/*start device minor#*/, 1/*count*/, "csk");

  cdev_init(&cdev, &csk_fops);
  cdev.owner = THIS_MODULE;
  
  err = cdev_add (&cdev, dev, 1);
  /* Fail gracefully if need be */
  if (err)
    printk(KERN_NOTICE "Error %d adding scull\n", err);
  return 0;
}

static void csk_exit(void)
{
  printk(KERN_ALERT "Goodbye, CSK\n");
  cdev_del(&cdev); 
  unregister_chrdev_region(dev, 1);
}

module_init(csk_init);
module_exit(csk_exit);


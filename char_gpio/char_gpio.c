#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>                              /* open( ), read( ), write( ), close( ) 커널 함수 */
#include <linux/cdev.h>
#include <linux/io.h>  /*ioremap_nocache*/
#include <asm/uaccess.h>                    /* copy_to_user( )*/
#include "gpio.h"

dev_t dev = 0;	
struct cdev cdev;
static char msg[BLOCK_SIZE] = {0,};
#define GPIO_LED 21	//gpio 21
static volatile unsigned int* gpio;
 
MODULE_LICENSE("Dual BSD/GPL");

static int cgpio_open(struct inode *inod, struct file *fil)
{
    printk("CGPIO Device opened(%d/%d)\n", imajor(inod), iminor(inod));

    return 0;
}

static int cgpio_release(struct inode *inod, struct file *fil)
{
    printk("CGPIO Device closed\n");

    return 0;
}

static ssize_t cgpio_read(struct file *fil, char *buff, size_t len, loff_t *off)
{
    int length = strlen(msg) + 1;
    printk("CGPIO Device read len : %d\n");
    copy_to_user(buff, msg, length);

    return length;
}

static ssize_t cgpio_write(struct file *fil, const char *buff, size_t len, loff_t *off)
{
    short count;
    printk("CGPIO Device write len : %d\n", len);

    memset(msg, 0x00, BLOCK_SIZE);
    count = copy_from_user(msg, buff, len);
    (!strncmp(msg, "0", 1))?GPIO_CLR(GPIO_LED):GPIO_SET(GPIO_LED);
    return len;
}

static struct file_operations cgpio_fops = {
   .owner = THIS_MODULE,
   .read = cgpio_read,
   .write = cgpio_write,
   .open = cgpio_open,
   .release = cgpio_release,
};

static int cgpio_init(void)
{
	
    int err;
    
    printk(KERN_ALERT "Hello, world\n");
	 alloc_chrdev_region(&dev, 0/*start device minor#*/, 1/*count*/,
	"cgpio");

    cdev_init(&cdev, &cgpio_fops);
    cdev.owner = THIS_MODULE;
    
    void* map = ioremap_nocache(GPIO_BASE, GPIO_SIZE);
    if(!map){
      printk("Error : mapping GPIO memory\n");
      return -EBUSY;
    }
    gpio = (volatile unsigned int*)map;
    GPIO_IN(GPIO_LED);
    GPIO_OUT(GPIO_LED);
    err = cdev_add (&cdev, dev, 1);
    /* Fail gracefully if need be */
    if (err)
        printk(KERN_NOTICE "Error %d adding scull\n", err);
    return 0;
}

static void cgpio_exit(void)
{
    printk(KERN_ALERT "Goodbye, CGPIO\n");
    if (gpio) {
       iounmap(gpio); 
    }
    cdev_del(&cdev); 
    unregister_chrdev_region(dev, 1);

}

module_init(cgpio_init);
module_exit(cgpio_exit);


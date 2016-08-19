#include <linux/init.h>
#include <linux/module.h>
#include <linux/kfifo.h>

MODULE_LICENSE("Dual BSD/GPL");

struct fox {
  unsigned long tail_length;
  unsigned long weight;
  bool          is_fantastic;
};

struct kfifo fifo;

struct fox red_fox = {
  .tail_length = 40,
  .weight = 6,
  .is_fantastic = false, 
};

static int _init(void)
{
  int ret;
  struct fox temp;
  ret = kfifo_alloc(&fifo, PAGE_SIZE, GFP_KERNEL);
  if(ret) return ret;

  ret = kfifo_in(&fifo, &red_fox, sizeof(struct fox));
  printk("kfifo_in %d\n", ret);
  ret = kfifo_out(&fifo, &temp, sizeof(struct fox));
  printk("kfifo_out %d\n", ret);

  return 0;
}

static void list_exit(void)
{
}



module_init(_init);
module_exit(list_exit);


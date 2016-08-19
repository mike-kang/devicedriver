#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>
MODULE_LICENSE("Dual BSD/GPL");

struct fox {
  unsigned long tail_length;
  unsigned long weight;
  bool          is_fantastic;
  
  struct list_head list;
};

static struct list_head *fox_list; 
/*
struct fox red_fox = {
  .tail_length = 40,
  .weight = 6,
  .list = LIST_HEAD_INIT(red_fox.list),
  .is_fantastic = false, 
};
*/
static int _init(void)
{
  struct fox *f;
  struct fox *red_fox;
  fox_list = kmalloc(sizeof(struct list_head), GFP_KERNEL);
  INIT_LIST_HEAD(fox_list);
  red_fox = kmalloc(sizeof(*red_fox), GFP_KERNEL);
  if(!red_fox){
    printk("error kmalloc \n");
    return -1;
  }
  printk("kmalloc ok\n");
    
  red_fox->tail_length = 40;
  red_fox->weight = 6;
  red_fox->is_fantastic = false;
  INIT_LIST_HEAD(&red_fox->list);
  list_add(&red_fox->list, fox_list);

  list_for_each_entry(f, fox_list, list) {
    printk("tail length %ld\n", f->tail_length);
  }
  return 0;
}

static void list_exit(void)
{
}



module_init(_init);
module_exit(list_exit);


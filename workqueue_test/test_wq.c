#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/kthread.h> //for current
#include <linux/sched.h>
static struct workqueue_struct *my_wq;


typedef struct {  
  struct work_struct my_work;  
  int    x;
} my_work_t;
//my_work_t *work, *work2;

static void my_wq_function( struct work_struct *work)
{ 
  my_work_t *my_work = (my_work_t *)work;  

  printk( "[%s[%d]]my_work.x %d\n", current->comm, current->pid, my_work->x );  

  kfree( (void *)work );
  return;

}

int my_init_module( void )
{  
  int ret;  
  my_work_t *work;
  printk("%s pid %d\n", current->comm, current->pid);
  my_wq = create_workqueue("my_queue"); 

  if (my_wq) {    
    //-- Queue some work (item 1) --    
    work = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);    
    if (work) {     
      INIT_WORK( (struct work_struct *)work, my_wq_function );      
      work->x = 1;     
      //ret = queue_work( my_wq, (struct work_struct *)work );   
    }    
    while(work_pending((struct work_struct *)work)){
      printk("work_pending\n");
      set_current_state(TASK_INTERRUPTIBLE);
      schedule_timeout(100);
      set_current_state(TASK_RUNNING);

    }
#if 0    
    //-- Queue some additional work (item 2) --    
    work2 = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);   
    if (work2) {     
      INIT_WORK( (struct work_struct *)work2, my_wq_function );      
      work2->x = 2;     
      ret = queue_work( my_wq, (struct work_struct *)work2 );   
    }
#endif
  
  } 
  return 0;
}

void my_exit_module( void )
{  
  destroy_workqueue(my_wq);
}

module_init(my_init_module);
module_exit(my_exit_module);
MODULE_LICENSE("Dual BSD/GPL");

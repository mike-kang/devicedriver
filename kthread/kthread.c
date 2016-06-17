#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/completion.h>
#include <linux/delay.h>
#include <linux/kthread.h>

struct task_struct *ts=NULL;

static int kthread_example_thr_fun(void *arg)
{
  printk(KERN_ALERT "@ %s() : called\n", __FUNCTION__);
  while(!kthread_should_stop())
  {
    printk(KERN_ALERT "@ %s() : loop pid:%d\n", __FUNCTION__, ts->pid);
    ssleep(1); 
  }
  printk(KERN_ALERT "@ %s() : kthread_should_stop() called. Bye.\n", __FUNCTION__);
  return 113;
} 

static int __init kthread_example_init(void)
{
  printk(KERN_ALERT "@ %s() : called. current task pid:%d\n", __FUNCTION__, current->pid);
 
  if(ts == NULL){ 
     ts = (struct task_struct *)kthread_run(kthread_example_thr_fun, NULL, "kthread_example");
  }
  return 0;
} 

static void __exit kthread_example_release(void)
{
  int ret = 0;
  if(ts){
     ret = kthread_stop(ts);
     ts = NULL;
  }
  printk(KERN_ALERT "@ %s() : Bye.current task pid:%d ret:%d\n", __FUNCTION__, current->pid, ret);
} 
 
module_init(kthread_example_init);
module_exit(kthread_example_release);
MODULE_LICENSE("Dual BSD/GPL");

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>

int print_self_init_module(void)
{
  struct task_struct *task;

  printk(KERN_INFO "My process id/pid is %d\n", current->pid);
  printk(KERN_INFO "My running state is ");
  switch(current->state)
  {
    case -1 :
      printk("unrunnable\n");
      break;
    case 0 :
      printk("runnable\n");
      break;
    default :
      printk("stopped\n");
      break;
  }
  printk(KERN_INFO "My name is %s\n", current->comm);
  printk(KERN_INFO "My parent processes until init :\n");
  for(task=current;task!=&init_task;task=task->parent)
  {
    printk(KERN_INFO "%s [%d]\n",task->comm , task->pid);
  }
  printk(KERN_INFO "My start time is %llu\n", (unsigned long long)current->se.exec_start);
  printk(KERN_INFO "My virtual runtime is %llu", (unsigned long long)current->se.vruntime);
  return 0;
}

void print_self_cleanup_module(void)
{
  printk(KERN_INFO "Cleaning Up.\n");
}

asmlinkage int sys_print_self(void)
{
  print_self_init_module();
  print_self_cleanup_module();
  return 1;
}

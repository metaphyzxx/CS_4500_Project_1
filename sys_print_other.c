#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>

int print_other_init_module(int pid)
{
  struct task_struct *task;
  struct task_struct *temp_task;

  task = pid_task(find_vpid(pid), PIDTYPE_PID);

  if (task == NULL)
  {
    printk(KERN_INFO "Cannot find a process with that PID\n");
  }
  else
  {
    printk(KERN_INFO "PID %d's running state is ", pid);
    switch(task->state)
    {
      case -1 :
        printk(KERN_INFO "unrunnable\n");
        break;
      case 0 :
        printk(KERN_INFO "runnable\n");
        break;
      default :
        printk(KERN_INFO "stopped\n");
        break;
    }
    printk(KERN_INFO "PID %d's name is %s\n", pid, task->comm);
    printk(KERN_INFO "PID %d's parent processes until init :\n", pid);
    for(temp_task=task;temp_task!=&init_task;temp_task=temp_task->parent)
    {
      printk(KERN_INFO "%s [%d]\n",temp_task->comm , temp_task->pid);
    }
    printk(KERN_INFO "PID %d's start time is %llu\n", pid, (unsigned long long)current->se.exec_start);
    printk(KERN_INFO "PID %d's virtual runtime is %llu", pid, (unsigned long long)current->se.vruntime);
  }

  return 0;
}

void print_other_cleanup_module(void)
{
  printk(KERN_INFO "Cleaning Up.\n");
}

asmlinkage int sys_print_other(int pid)
{
  print_other_init_module(pid);
  print_other_cleanup_module();
  return 1;
}

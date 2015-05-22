#include <linux/kernel.h> 
#include <linux/sched.h> 
 
asmlinkage int sys_helloworld(void) 
{ 
  printk(KERN_INFO "Hello World !\n"); 
  return 1; 
}

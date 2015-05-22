#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>

#define __NR_helloworld 337
#define __NR_print_self 338
#define __NR_print_other 339

int main(int argc, char *argv[])
{
  int pid;

  syscall(__NR_helloworld);
  syscall(__NR_print_self);
  printf("Please enter a PID: ");
  scanf("%d", &pid);
  printf("You entered PID %d\n", pid);
  if (kill(pid, 0) == 0)
  {
    syscall(__NR_print_other, pid);
  }
  else
  {
    printf("PID %d is not running.", pid);
  }
  return 0;
}

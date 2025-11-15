#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int pid = getpid();

  printf(1, "_______TESTING get_num_syscall(pid)_______\n");

  // print initial count
  printf(1, "get_num_syscall(%d): %d\n", pid, get_num_syscall(pid));

  // make a few syscalls (sleep is counted as one)
  sleep(10);

  // print updated count
  printf(1, "get_num_syscall(%d) [after sleep syscall]: %d\n",
         pid, get_num_syscall(pid));

  exit();
}

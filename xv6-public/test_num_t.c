#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int pid = getpid();
  volatile int sink = 0;   // volatile prevents optimization

  printf(1, "_______TESTING get_num_timer_interrupts(pid)_______\n");
  printf(1, "get_num_timer_interrupts(%d): %d\n",
         pid, get_num_timer_interrupts(pid));

  // Busy loop that the compiler cannot optimize away
  for (long i = 0; i < 100000000; i++)
    sink += (int)(i & 1);

  printf(1, "get_num_timer_interrupts(%d) [after long for loop]: %d\n",
         pid, get_num_timer_interrupts(pid));

  exit();
}

#include "syscall.h"
#include "traps.h"

#define SYSCALL(name) \
  .globl name; \
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
SYSCALL(exit)
SYSCALL(wait)
SYSCALL(pipe)
SYSCALL(read)
SYSCALL(write)
SYSCALL(close)
SYSCALL(kill)
SYSCALL(exec)
SYSCALL(open)
SYSCALL(mknod)
SYSCALL(unlink)
SYSCALL(fstat)
SYSCALL(link)
SYSCALL(mkdir)
SYSCALL(chdir)
SYSCALL(dup)
SYSCALL(getpid)
SYSCALL(sbrk)
SYSCALL(sleep)
SYSCALL(uptime)
<<<<<<< HEAD
SYSCALL(getchildren)
SYSCALL(get_proc_state)
SYSCALL(fill_proc_name)
SYSCALL(get_name)

=======
SYSCALL(hello)
SYSCALL(helloYou)
SYSCALL(getSibling)
SYSCALL(welcomeFunction)
SYSCALL(welcomeDone)
SYSCALL(is_proc_valid)
>>>>>>> 76556f9daa06642e51f91332ba6ee681f8e83608

#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

#include "spinlock.h"
extern struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

int 
sys_get_proc_state(void)
{
  int pid;
  char *ubuf;
  int size;
  struct proc *p;
  char *state_str="UNKNOWN";
  int found = 0;

  if ( argint(0,&pid)<0)
  return 0;
  if(argint(2,&size)<0)
  return 0;
  if(argptr(1,&ubuf,sizeof(char * ))<0)
  return 0;

  acquire(&ptable.lock);
  for(p=ptable.proc;p<&ptable.proc[NPROC];p++)
  {
    if(p->pid==pid){
      found=1;
      switch(p->state)
      {
        case UNUSED : state_str="UNUSED";break;
        case EMBRYO : state_str="EMBRYO";break;
        case SLEEPING : state_str="SLEEPING";break;
        case RUNNABLE: state_str="RUNNABLE";break;
        case RUNNING : state_str="RUNNING";break;
        case ZOMBIE : state_str="ZOMBIE";break;
        default :    state_str = "UNKNOWN"; break ;
        
      }

      safestrcpy(ubuf,state_str,size);
    break;
      }
  }
  release(&ptable.lock);
  if(found)
  return 1;
  else return 0;


}

int 
sys_fill_proc_name(void)
{
  int pid ;
  char *uname;
  struct proc *p;
  int found =0;
  if(argint(0,&pid)<0)
  return 0;
   if (argptr(1, &uname, sizeof(char *)) < 0)
        return 0;

     acquire(&ptable.lock);
    for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
        if (p->pid == pid) {
            safestrcpy(p->custom_name, uname, sizeof(p->custom_name));
            found = 1;
            break;
        }
    }
    release ( &ptable.lock);
    return found;

}
int
sys_get_name(void)
{
    int pid;
    char *ubuf;
    int size;
    struct proc *p;
    int found = 0;

    // Fetch syscall arguments
    if (argint(0, &pid) < 0)
        return 0;
    if (argptr(1, &ubuf, sizeof(char *)) < 0)
        return 0;
    if (argint(2, &size) < 0)
        return 0;

    acquire(&ptable.lock);
    for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
        if (p->pid == pid) {
            safestrcpy(ubuf, p->custom_name, size);
            found = 1;
            break;
        }
    }
    release(&ptable.lock);

    return found;
}


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
int
sys_getchildren(void)
{
  struct proc *p;
  struct proc *cur = myproc();
  int count = 0;

  acquire(&ptable.lock);
  cprintf("Children PID's are:\n");
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state != UNUSED && p->parent == cur){
      cprintf("%d\n", p->pid);
      count++;
    }
  }
  release(&ptable.lock);

  cprintf("No. of Children: %d\n", count);
  return 0;
}

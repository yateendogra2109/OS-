#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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
sys_helloYou(void)
{
  char *str;

    // Fetch the pointer argument (index 0)
  if(argptr(0, &str, sizeof(char*)) < 0){
      return -1;
  }

  cprintf("%s", str);

  return 0;
}

int
sys_hello(void)
{
  cprintf("Hello");

  return 0;
}

int sys_getSibling(void){
  
  find_siblings(); //defined in proc.c (because ptable is defined in proc.c)
  return 0;
}

int sys_welcomeFunction(){
  void (*func)();
  if (argptr(0, (void*)&func, sizeof(func)) < 0){
    return -1;
  }
  
  struct proc *curprocess = myproc();
  curprocess->welcome_func = func;

  return 0;
}


int sys_welcomeDone(){
  struct proc *curprocess = myproc();
  
  if (curprocess->parent == 0){
    return -1;
  }

  curprocess->tf->eip = curprocess->eip_temp;

  return 0;
}

int sys_is_proc_valid(){

  int pid;
  if (argint(0, &pid) < 0){
    return -1;
  }

  return check_valid(pid); //defined in proc.c (because ptable is defined in proc.c)

}

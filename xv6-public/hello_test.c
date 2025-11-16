#include "types.h"
#include "stat.h"
#include "user.h"

void test_is_proc_valid(){
    // Test is_proc_valid
    int pid = getpid(); 
    int valid1 = is_proc_valid(1);
    int valid2 = is_proc_valid(2);
    int valid3 = is_proc_valid(pid);
    int valid4 = is_proc_valid(10000);
    
    printf(1,"\n_______TESTING is_proc_valid(pid)_______\n");
    printf(1, "is_proc_valid(%d): %d\n", 1, valid1);
    printf(1, "is_proc_valid(%d): %d\n", 2, valid2);
    printf(1, "is_proc_valid(%d): %d\n", pid, valid3);
    printf(1, "is_proc_valid(%d): %d\n", 10000, valid4);
}

void test_get_num_syscall(){
    int pid = getpid();
    int num_syscalls1 = get_num_syscall(pid);
    sleep(1);
    int num_syscalls2 = get_num_syscall(pid);
    
    printf(1,"\n_______TESTING get_num_syscall(pid)_______\n");
    printf(1, "get_num_syscall(%d): %d\n", pid, num_syscalls1);
    printf(1, "get_num_syscall(%d) [after sleep syscall]: %d\n", pid, num_syscalls2);
}

void test_proc_name(){
    printf(1,"\n_______TESTING fill_proc_name(pid) and get_proc_name(pid)_______\n");

    int pid = getpid(); 
    char* buf = malloc(16);
    if (buf == 0) {
        printf(1, "Memory allocation failed\n");
        exit();
    }
    buf = "hello world!";
    int fill_status1 = fill_proc_name(pid, buf);
    printf(1, "fill_proc_name(%d): %s (Status: %d)\n", pid, buf, fill_status1);

    int fill_status2 = fill_proc_name(10000, buf);
    printf(1, "fill_proc_name(%d): %s (Status: %d)\n", 10000, buf, fill_status2);

    char name[16];
    if (get_proc_name(pid, name, sizeof(name)) > 0)
    printf(1, "Process with pid (%d) has name: %s\n",pid, name);
    else
    printf(1, "Process not found\n");

    if (get_proc_name(10000, name, sizeof(name)) > 0)
    printf(1, "Process with pid (%d) has name: %s\n",10000, name);
    else
    printf(1, "Process with pid (%d) was not found\n", 10000);
}

void test_proc_state()
{
    printf(1,"\n_______TESTING get proc state(pid)_______\n");
    int pid = getpid();
    char state[16];
    if (get_proc_state(1, state, sizeof(state)) > 0)
        printf(1, "Process with pid (%d) has state: %s\n", 1, state);
    else
        printf(1, "Process not found\n");
    if (get_proc_state(2, state, sizeof(state)) > 0)
        printf(1, "Process with pid (%d) has state: %s\n", 2, state);
    else
        printf(1, "Process not found\n");
    if (get_proc_state(pid, state, sizeof(state)) > 0)
        printf(1, "Process with pid (%d) has state: %s\n", pid, state);
    else
        printf(1, "Process not found\n");
    if (get_proc_state(10000, state, sizeof(state)) > 0)
        printf(1, "Process with pid (%d) has state: %s\n", 10000, state);
    else
        printf(1, "Process not found\n");
}

void test_get_num_timer_interrupts(){
    int pid = getpid();

    printf(1,"\n_______TESTING get_num_timer_interrupts(pid)_______\n");
    printf(1, "get_num_timer_interrupts(%d): %d\n", pid, get_num_timer_interrupts(pid));
    for(double i = 0; i < 10e6; i++);
    printf(1, "get_num_timer_interrupts(%d) [after long for loop]: %d\n", pid,  get_num_timer_interrupts(pid));
}

void children(){
  for(int i = 0; i < 3; i++){
        if(fork() == 0){
            exit();
        }
    }
    getChildren();  
    for(int i = 0; i < 3; i++){
        wait();
    }
}

void sibling(){
  for(int i = 0; i < 3; i++){
        if(fork() == 0){
            exit();
        }
    }
    
    int child_pid = fork();
    if (child_pid == 0){
        getSibling();
        exit();
    }

    else{
        sleep(3);
        wait();
    }


    for(int i = 0; i < 3; i++){
        wait();
    }
}

void ps_tree(){
  int pid = getpid();
    for(int i = 0; i < 2; i++){
        fork();
    }
    if (getpid() != pid) {sleep(20);}
    else{
        sleep (10);
        pstree();
    }
    for(int i = 0; i < 4; i++){
        wait();
    }
}

int str_eq(const char *a, const char *b) {
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }
    return *a == *b;
}

void welcome(void)
{
  printf(1, "I am child in welcome function\n");
  welcomeDone();
}

void welcome_fork(){
  int ret1 = fork();
  if(ret1 == 0)
    {
      printf(1, "I am child with no welcome\n"); 
    }
  else if (ret1 > 0)
    {
      wait();
      printf(1, "Parent reaped first child\n");
     
      welcomeFunction(&welcome);
      
      int ret2 = fork();
      if (ret2 == 0)
	{
	  printf(1, "I have returned from welcome function\n");
	  exit();
	}
      else if (ret2 > 0)
	{
	  wait();
	  printf(1, "Parent reaped second child\n");
	}
    }
}

int main(int argc, char *argv[]) {

//for (int i = 1; i < argc; i++) {
//        if (str_eq(argv[i], "-vv")) {
//            printf(1,"saw the flag vv");
//        }
//    }

// hello();

// helloYou("I am hello you\n");

// children();

// sibling();

// ps_tree();

// test_is_proc_valid();

test_proc_state();

test_proc_name();

// test_get_num_syscall();

// test_get_num_timer_interrupts();

// welcome_fork();

//printf(1, "hello() returned\n");
exit();

}

// make qemu-nox QEMU=/home/yuvraj/qemu/build/qemu-system-i386
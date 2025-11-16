#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{

    int e_flag = 0;
    if (argc > 1 && strcmp(argv[1], "-e") == 0) {
        e_flag = 1;
    }   
    if (!e_flag)
    {   int pid = getpid();

        printf(1, "PID\tNAME\tSTATE\tSYS\tINT\n");
	fill_proc_name(pid, "ps");

        char statebuf[15];
        char namebuf[30];

        get_proc_state(pid, statebuf, sizeof(statebuf));
        get_proc_name(pid, namebuf, sizeof(namebuf));

        int num_sys = get_num_syscall(pid);
        int num_int = get_num_timer_interrupts(pid);
	printf(1,"%d\t%s\t%s\t%d\t%d\n",
                       pid, namebuf, statebuf, num_sys, num_int);
    }
    else 
    {
        printf(1, "PID\tSTATE\tSYS\tINT\n"); 
        char statebuf[15];

        // scan all possible xv6 pids (1..NPROC)
        for(int p = 1; p < 64; p++) {
            if(is_proc_valid(p)) {

                get_proc_state(p, statebuf, sizeof(statebuf));

                int num_sys = get_num_syscall(p);
                int num_int = get_num_timer_interrupts(p);

                printf(1,"%d\t%s\t%d\t%d\n",
                       p, statebuf, num_sys, num_int);
            }
        }
    }
    exit();
}
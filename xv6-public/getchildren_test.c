#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
    printf(1, "Testing getchildren syscall...\n");

    int pid1 = fork();
    if(pid1 == 0){
        sleep(100);   // keep child alive
        exit();
    }

    int pid2 = fork();
    if(pid2 == 0){
        sleep(100);   // keep child alive
        exit();
    }

    // Parent process: call getchildren while children are still running
    sleep(10);        // give time for children to start
    getchildren();

    wait();
    wait();

    printf(1, "Test complete.\n");
    exit();
}


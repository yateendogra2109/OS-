#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
    char buf[16];
    int r;

    printf(1, "_______TESTING get_proc_state(pid)_______\n");

    // Test for a few pids
    for (int pid = 1; pid <= 3; pid++) {
        r = get_proc_state(pid, buf, sizeof(buf));
        if (r)
            printf(1, "Process with pid (%d) has state: %s\n", pid, buf);
        else
            printf(1, "Process with pid (%d) not found\n", pid);
    }

    // Test for a non-existing pid
    r = get_proc_state(10000, buf, sizeof(buf));
    if (r)
        printf(1, "Process with pid (10000) has state: %s\n", buf);
    else
        printf(1, "Process not found\n");

    exit();
}

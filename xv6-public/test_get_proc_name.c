#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
    char buf[16];
    int r;

    printf(1, "_______TESTING fill_proc_name() and get_proc_name()_______\n");

    // give a name to pid 3
    r = fill_proc_name(3, "process3");
    printf(1, "fill_proc_name(3): process3 (Status: %d)\n", r);

    // retrieve the name
    memset(buf, 0, sizeof(buf));
    r = get_proc_name(3, buf, sizeof(buf));
    printf(1, "get_proc_name(3): %s (Status: %d)\n", buf, r);

    // test with invalid PID
    memset(buf, 0, sizeof(buf));
    r = get_proc_name(9999, buf, sizeof(buf));
    printf(1, "get_proc_name(9999): %s (Status: %d)\n", buf, r);

    exit();
}

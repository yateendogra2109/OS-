#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
    int r;
    r = fill_proc_name(3, "hello");
    printf(1, "fill_proc_name(3): hello (Status: %d)\n", r);

    r = fill_proc_name(30000, "Operating System");
    printf(1, "fill_proc_name(30000): Operating System (Status: %d)\n", r);

    exit();
}

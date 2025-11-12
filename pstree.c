#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  printf(1, "Process tree:\n");
  pstree();
  exit();
}

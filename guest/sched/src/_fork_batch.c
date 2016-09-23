#include <lib.h>
#include <unistd.h>

PUBLIC int fork_batch(void)
{
  message m;
  return (_syscall(PM_PROC_NR,FORK_BATCH,&m));
}

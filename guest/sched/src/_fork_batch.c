#include <lib.h>
#include <unistd.h>

PUBLIC pid_t fork_batch()
{
  message m;
  return (_syscall(MM, FORK_BATCH, &m));
}

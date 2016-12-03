#include <lib.h>
#define lsr	_lsr

#if _ANSI
PUBLIC int lsr(const char *name)
#else
PUBLIC int lsr(name)
_CONST char *name;
#endif
{
  message m;
	_loadname(name, &m);
  return (_syscall(FS, LSR, &m));
}

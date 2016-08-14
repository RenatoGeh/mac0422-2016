#ifndef _BUILTIN_H_
#define _BUILTIN_H_

#include "args.h"

/* Checks if cmd is a builtin command. */
int builtin_contains(args_t *cmd);

/* Execute cmd. If cmd is not a builtin command, return -1. */
int builtin_exec(args_t *cmd);

#endif /* _BUILTIN_H_ */

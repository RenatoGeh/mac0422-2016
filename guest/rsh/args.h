#ifndef _ARGS_H_
#define _ARGS_H_

#include "ustring.h"

/* Arguments struct. */
typedef struct {
  /* String values. First alue is always the command. The rest are arguments to the first value. */
  string_t **s;
  /* Argument count. */
  int c;
} args_t;

/* Creates an argument struct given command cmd. */
args_t *create_args(string_t *cmd);

/* Adds argument e to args_t* a. */
args_t *args_add(args_t *a, string_t *s);

/* Frees memory from args_t a. */
void free_args(args_t *a);

#endif /* _ARGS_H_ */

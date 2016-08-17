#include "args.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

args_t *create_args(string_t *cmd) {
  int c, i, j, n, l;
  char *ptr;
  args_t *args;

  n = cmd->len;
  l = 0;
  /* Count number of tokens. */
  for (i = c = 0; i < n; ++i)
    if (cmd->str[i] == ' ' && l) {
      ++c;
      l = 0;
    } else l = 1;
  ++c;
  /* Create new args_t. */
  args = (args_t*) malloc(sizeof(args_t));
  args->c = c;
  args->s = (string_t**) malloc(c * sizeof(string_t*));
  /* Copy tokens as string_ts. */
  ptr = strtok(cmd->str, " ");
  for (i = l = 0; ptr != NULL; ++i) {
    for (j = 0; ptr[j] != '\0'; ++j);
    args->s[i] = copy_string(ptr, j+1);
    ptr = strtok(NULL, " ");
  }

  return args;
}

args_t *args_add(args_t *a, string_t *s) {
  int i, old;
  string_t **vals;

  old = a->c++;
  vals = (string_t**) malloc(a->c * sizeof(string_t*));

  for (i = 0; i < old; ++i)
    vals[i] = a->s[i];
  vals[old] = s;

  free(a->s);
  a->s = vals;

  return a;
}

args_t *args_pop(args_t *a) {
  string_t **new_s;
  int i, n;

  n = a->c - 1;
  new_s = (string_t**) malloc(n * sizeof(string_t*));

  for (i = 1; i < a->c; ++i)
    new_s[i-1] = a->s[i];
  free_string(a->s[0]);
  free(a->s);
  a->s = new_s;
  --a->c;

  return a;
}

args_t *args_pop_back(args_t *a) {
  string_t **new_s;
  int i;

  a->c--;
  new_s = (string_t**) malloc(a->c * sizeof(string_t*));

  for (i = 0; i < a->c; ++i)
    new_s[i] = a->s[i];
  free_string(a->s[a->c]);
  free(a->s);
  a->s = new_s;

  return a;
}

args_t *args_push(args_t *a, string_t *s) {
  string_t **new_s;
  int i;

  ++a->c;
  new_s = (string_t**) malloc(a->c * sizeof(string_t*));

  for (i = 1; i < a->c; ++i)
    new_s[i] = a->s[i-1];
  new_s[0] = s;
  free(a->s);
  a->s = new_s;

  return a;
}

args_t *args_push_back(args_t *a, string_t *s) {
  string_t **new_s;
  int i;

  new_s = (string_t**) malloc((a->c+1) * sizeof(string_t*));

  for (i = 0; i < a->c; ++i)
    new_s[i] = a->s[i];
  new_s[a->c++] = s;
  free(a->s);
  a->s = new_s;

  return a;
}

void free_args(args_t *a) {
  free(a->s);
  free(a);
}

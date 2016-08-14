#include "args.h"

#include <stdlib.h>
#include <string.h>

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
  /* Create new args_t. */
  args = (args_t*) malloc(sizeof(args_t));
  args->c = c;
  args->s = (string_t**) malloc(c * sizeof(string_t*));
  /* Copy tokens as string_ts. */
  ptr = strtok(cmd->str, " ");
  for (i = l = 0; ptr != NULL; ++i) {
    for (j = 0; ptr[j] != '\0'; ++j);
    args->s[i] = copy_string(ptr, j);
    ptr = strtok(NULL, " ");
  }

  return args;
}

void free_args(args_t *a) {
  free(a->s);
  free(a);
}

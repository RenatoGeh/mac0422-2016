#include "prompt.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>

#include "utils.h"
#include "ustring.h"
#include "args.h"
#include "builtin.h"
#include "proc.h"

#define MIN_PROMPT_LEN 8
#define MAX_MEM 1024
#define MIN_MEM MIN_PROMPT_LEN

/* Last exit result. */
static int _lres = 0;

prompt_t *create_prompt(void) {
  prompt_t *rp;

  rp = (prompt_t*) malloc(sizeof(prompt_t));
  rp->len = 0;

  prompt_update(rp);
  return rp;
}

void free_prompt(prompt_t *p) {
  free(p->str);
  free(p);
}

int prompt_update(prompt_t *p) {
  GET_PWD(p->str);
  p->len = strlen(p->str);
  return 0;
}

int prompt_readline(prompt_t *p) {
  string_t *cmd;
  args_t *args;
  char *line;
  int res;

  line = (char*) malloc(BUFFER_SIZE * sizeof(char));
  if (fgets(line, BUFFER_SIZE, stdin) == NULL) {
    puts("Line too long for buffer!");
    return 1;
  }
  cmd = copy_string(line, strlen(line));
  args = create_args(cmd);

  res = builtin_exec(args);
  if (res < 0)
    res = proc_exec(args);

  free(line);
  free_args(args);
  free_string(cmd);

  return _lres = res;
}

void prompt_print(prompt_t *p) {
  prompt_update(p);
  printf("[%d] %s $> ", _lres, p->str);
}

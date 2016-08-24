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
  char line[BUFFER_SIZE];
  int len, res, i;
  char *errline;

  errline = fgets(line, BUFFER_SIZE, stdin);
  if (errline == NULL) {
    if (feof(stdin)) {
      putchar('\n');
      exit(0);
    } else {
      puts("Line too long for buffer!");
      return _lres = 1;
    }
  }
  if (line[0] == '\n' || line[0] == '\0')
    return _lres = 0;

  len = strlen(line) - 1;

  for (res = i = 0; i < len; ++i)
    if (line[i] != ' ')
      res = 1;
  if (!res)
    return _lres = 0;

  if (len < 0)
    return _lres = 0;
  line[len] = '\0';
  cmd = copy_string(line, len+1);
  args = create_args(cmd);

  res = builtin_exec(args);
  if (res < 0)
    res = proc_exec(args);

  free_args(args);
  free_string(cmd);

  return _lres = res;
}

void prompt_print(prompt_t *p) {
  prompt_update(p);
  printf("[%d] %s $> ", _lres, p->str);
}

void prompt_send_status(int s) {
  _lres = s;
}

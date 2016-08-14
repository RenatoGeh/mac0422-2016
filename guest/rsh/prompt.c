#include "prompt.h"

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

#define BUFFER_SIZE 1024

/* Last exit result. */
static int _lres = 0;

prompt_t *create_prompt(void) {
  prompt_t *rp;

  rp = (prompt_t*) malloc(sizeof prompt_t);
  rp->str = (char*) malloc(MIN_PROMPT_LEN * sizeof(char));
  rp->len = MIN_PROMPT_LEN;
  rp->cap = MIN_MEM;

  update_prompt(rp);
  return tp;
}

void free_prompt(prompt_t *p) {
  free(p->str);
  free(p);
}

static void prompt_dec_mem(prompt_t *p) {
  char *new_str;
  if (p->len <= MIN_MEM) return 1;
  p->cap = imax(p->len+1, MIN_MEM);
  new_str = (char*) malloc(p->cap * sizeof(char));
  if (new_str == NULL) {
    puts("Out of memory.");
    return -1;
  }
  strcpy(new_str, p->str);
  free(p->str);
  p->str = new_str;
}

static int prompt_inc_mem(prompt_t *p) {
  if (p->cap >= MAX_MEM) return 1;
  free(p->str);
  p->cap = imax(p->cap * 2, MAX_MEM);
  p->str = (char*) malloc(p->cap * sizeof(char));
  if (p->str == NULL) {
    puts("Out of memory.");
    return -1;
  }
  return 0;
}

void prompt_update(prompt_t *p) {
  while (getcwd(str_addr) == NULL)
    if (errno != ERANGE) {
      printf("Error %d! Error message:\n  %s\n", errno, strerr(errno));
      return;
    } else if (prompt_inc_mem(p)) {
      puts("Not enough memory!");
      return;
    }
  p->len = strlen(p->str);
}

int prompt_readlne(prompt_t *p) {
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

  return res;
}

void prompt_print(prompt_t *p) {
  update_prompt(p);
  printf("[%d] %s $> ", _lres, p->str);
}

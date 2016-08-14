#include "proc.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "utils.h"
#include "args.h"
#include "ustring.h"

int proc_exec(args_t *args) {
  int i;
  pid_t chid;
  char **argv;
  char *const env[] = {NULL};

  argv = (char**) malloc(args->c * sizeof(char*));
  for (i = 0; i < args->c; ++i)
    argv[i] = args->s[i]->str;

  if ((chid = fork()) < 0) {
    PRINT_ERR();
    return -1;
  } else if (!chid) {
    /* Child process. */
    execve(args->s[0]->str, argv, env);
    puts("Something terrible has occured!");
    return 1;
  }

  /* Parent process. */
  if (strcmp(args->s[args->c-1]->str, "&"))
    waitpid(chid, NULL, 0);

  free(argv);

  return 0;
}

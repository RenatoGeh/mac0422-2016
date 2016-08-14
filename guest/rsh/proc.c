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
#include "prompt.h"

#define MAX_ARGS 50

int proc_exec(args_t *args) {
  int i;
  pid_t chid;
  char **argv;
  char *const env[] = {NULL};

  argv = (char**) malloc((args->c+1) * sizeof(char*));
  for (i = 0; i < args->c; ++i)
    argv[i] = args->s[i]->str;
  argv[args->c] = NULL;

  if ((chid = fork()) < 0) {
    PRINT_ERR();
    return -1;
  } else if (chid == 0) {
    /* Child process. */
    if (execve(args->s[0]->str, argv, env)) {
      printf("%s: command not found.\n", args->s[0]->str);
      PRINT_ERR();
      prompt_send_status(1);
      exit(1);
    } else {
      prompt_send_status(0);
      exit(0);
    }
  }

  /* Parent process. */
  if (strcmp(args->s[args->c-1]->str, "&"))
    waitpid(chid, NULL, 0);

  free(argv);

  return 0;
}

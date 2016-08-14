#include "builtin.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <dirent.h>

#include "args.h"
#include "ustring.h"

#define BUFFER_SIZE 1024

/* Stores pwd in str. If an error occurs, prints it out. */
#define GET_PWD(str) if (getcwd((str), BUFFER_SIZE) == NULL) {\
  if (errno != ERANGE)\
    printf("Error %d! Error message:\n  %s\n", errno, strerr(errno));\
  else\
    puts("Line too long for buffer size!");\
  return errno;}

#define SIZE_LIST_CMDS 4;
const char *_list_cmds[] = {
  "cd", "ls", "pwd", "exit",
}

static int builtin_cd(args_t *args) {
  return 1;
}

static int builtin_pwd(args_t *args) {
  char pwd[BUFFER_SIZE];
  GET_PWD(pwd);
  puts(pwd);
  return 0;
}

static int builtin_ls(args_t *args) {
  char path[BUFFER_SIZE];
  DIR *dir;
  struct dirent *dent;

  if (args->c < 2 || !strcmp(args->s[1], "."))
    GET_PWD(path);
  dir = opendir(path);
  if (dir == NULL) {
    puts("Failed to read directory.");
    return 1;
  }
  while ((dent = readdir(dir)) != NULL)
    printf("%s\n", dent->d_name);
  closedir(dir);

  return 0;
}

static int builtin_exit(args_t *args) {
  int arg = 0;
  if (args->c > 1)
    arg = atoi(args->s[1]);
  exit(arg);
  return arg;
}

int builtin_contains(args_t *args) {
  char *name;
  int i;
  name = args->s[0];
  for (i = 0; i < SIZE_LIST_CMDS; ++i)
    if (!strcmp(name, _list_cmds[i]))
      return i;
  return -1;
}

int (*_list_funcs[SIZE_LIST_CMDS])(args_t *args) = {
  builtin_cd, builtin_ls, builtin_pwd, builtin_exit,
};

int builtin_exec(args_t *args0) {
  int index;
  index = builtin_contains(args);
  if (index < 0)
    return -1;
  return (*_list_funcs[index])(args);
}

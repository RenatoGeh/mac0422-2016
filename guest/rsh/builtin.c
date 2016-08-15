#include "builtin.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "utils.h"
#include "args.h"
#include "ustring.h"
#include "proc.h"

#define SIZE_LIST_CMDS 10
const char *_list_cmds[] = {
  "cd", "ls", "pwd", "exit", "true", "false",
  "protegepracaramba", "liberageral", "rodeveja", "rode",
};

static int builtin_protegepracaramba(args_t *args) {
  if (args->c < 2)
    puts("Usage: protegepracaramba filename\n  Sets permissions to 000.");

  if (chmod(args->s[0]->str, 0000) < 0) {
    PRINT_ERR();
    return 1;
  }

  return 0;
}

static int builtin_liberageral(args_t *args) {
  if (args->c < 2)
    puts("Usage: liberageral filename\n  Sets permissions to 777.");

  if (chmod(args->s[0]->str, 0777) < 0) {
    PRINT_ERR();
    return 1;
  }

  return 0;
}

static int builtin_rodeveja(args_t *args) {
  int res;
  res = proc_exec(args);
  printf("=> programa '%s' retornou com codigo %d.\n", args->s[0]->str, res);
  return res;
}

static int builtin_rode(args_t *args) {
  args_add(args, copy_string("&", 1));
  return proc_exec(args);
}

static int builtin_true(args_t *args) { return 0; }
static int builtin_false(args_t *args) { return 1; }

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

  if (args->c < 2 || !strcmp(args->s[1]->str, ".")) {
    GET_PWD(path);
  } else
    strcpy(path, args->s[1]->str);

  dir = opendir(path);
  if (dir == NULL) {
    puts("Failed to read directory.");
    return 1;
  }

  while ((dent = readdir(dir)) != NULL)
    if (strcmp(dent->d_name, ".") && strcmp(dent->d_name, ".."))
      printf("%s\n", dent->d_name);

  closedir(dir);

  return 0;
}

static int builtin_exit(args_t *args) {
  int arg = 0;
  if (args->c > 1)
    arg = atoi(args->s[1]->str);
  exit(arg);
  return arg;
}

int builtin_contains(args_t *args) {
  char *name;
  int i;
  name = args->s[0]->str;
  for (i = 0; i < SIZE_LIST_CMDS; ++i)
    if (!strcmp(name, _list_cmds[i]))
      return i;
  return -1;
}

int (*_list_funcs[SIZE_LIST_CMDS])(args_t *args) = {
  builtin_cd, builtin_ls, builtin_pwd, builtin_exit, builtin_true, builtin_false,
  builtin_protegepracaramba, builtin_liberageral, builtin_rodeveja, builtin_rode,
};

int builtin_exec(args_t *args) {
  int index;
  index = builtin_contains(args);
  if (index < 0)
    return -1;
  return (*_list_funcs[index])(args);
}

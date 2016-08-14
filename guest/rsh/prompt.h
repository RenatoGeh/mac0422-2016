#ifndef _PROMPT_H_
#define _PROMPT_H_

#include "utils.h"

/* Prompt type. */
typedef struct {
  char str[BUFFER_SIZE];
  int len;
} prompt_t;

/* Creates a prompt_t with the current pwd. */
prompt_t *create_prompt(void);

/* Frees memory from target prompt_t. */
void free_prompt(prompt_t *p);

/* Updates prompt_t p with the current pwd. */
int prompt_update(prompt_t *p);

/* Reads a line and runs it. */
int prompt_readline(prompt_t *p);

/* Prints the prompt. */
void prompt_print(prompt_t *p);

/* Sends last exit result status. */
void prompt_send_status(int s);

#endif /* _PROMPT_H_ */

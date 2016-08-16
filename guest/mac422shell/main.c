#include <stdio.h>

#include "prompt.h"

int main(int argc, char *args[]) {
  prompt_t *pmt;

  pmt = create_prompt();

  while (1) {
    prompt_print(pmt);
    prompt_readline(pmt);
  }

  free_prompt(pmt);

  return 0;
}

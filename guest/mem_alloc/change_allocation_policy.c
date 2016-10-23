#include <stdio.h>
#include <unistd.h>

int main(int argc, char *args[]) {
  int pol;
  char *str;

  if (argc != 1) {
    printf("Usage:\n  %s policy\nArguments:\n"
        "  policy - Indicates which policy to use:\n"
        "    first_fit, worst_fit, best_fit, random_fit\n", args[0]);
    return 1;
  }

  str = args[1];
  if (!strcmp(str, "first_fit")) {
    pol = FIRST_FIT;
  } else if (!strcmp(str, "worst_fit")) {
    pol = WORST_FIT;
  } else if (!strcmp(str, "best_fit")) {
    pol = BEST_FIT;
  } else if (!strcmp(str, "random_fit")) {
    pol = RANDOM_FIT;
  } else {
    puts("Argument invalid.");
    return 2;
  }

  alloc_algorithm(pol);

  return 0;
}

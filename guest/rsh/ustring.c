#include "ustring.h"

#include <stdlib.h>
#include <string.h>

string_t *create_string(char *str, int len) {
  string_t *s;
  s = (string_t*) malloc(sizeof(string_t));
  s->str = str;
  s->len = len;
  return s;
}

string_t *copy_string(char *str, int len) {
  string_t *s;
  s = (string_t*) malloc(sizeof(string_t));
  s->str = (char*) malloc(len * sizeof(char));
  strcpy(s->str, str);
  s->len = len;
  return s;
}

void free_string(string_t *str) {
  free(str->str);
  free(str);
}

void free_only_string(string_t *str) {
  free(str);
}

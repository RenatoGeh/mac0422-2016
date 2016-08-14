#ifndef _USTRING_H_
#define _USTRING_H_

/* Struct string_t is only a utility struct. This means it doesn't allocate a new char* unless
 * explicitly specified. It only stores the pointer. */
typedef struct {
  char *str;
  int len;
} string_t;

/* Creates a new string_t. */
string_t *create_string(char *str, int len);

/* Creates a new string_t and copies the new content to it. */
string_t *copy_string(char *str, int len);

/* Frees memory from string_t. Freeing str also frees its content. */
void free_string(string_t *str);

/* Frees string_t but doesn't free its content. */
void free_only_string(string_t *str);

#endif /* _USTRING_H_ */

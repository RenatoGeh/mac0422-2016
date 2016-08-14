#ifndef _UTILS_H_
#define _UTILS_H_

#include <string.h>

#include <errno.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/* Stores pwd in str. If an error occurs, prints it out. */
#define GET_PWD(str) if (getcwd((str), BUFFER_SIZE) == NULL) {\
  if (errno != ERANGE)\
    printf("Error %d! Error message:\n  %s\n", errno, strerror(errno));\
  else\
    puts("Line too long for buffer size!");\
  return errno;}

/* Preproc max function. */
#define MAX(a, b) (((a)<(b))?(b):(a))

/* Preproc min function. */
#define MIN(a, b) (((a)>(b))?(b):(a))

/* Integer max function. */
inline int imax(int a, int b) { return a < b ? b : a; }

/* Integer min function. */
inline int imin(int a, int b) { return a > b ? b : a; }

#endif /* _UTILS_H_ */

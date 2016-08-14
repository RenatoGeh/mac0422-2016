#ifndef _UTILS_H_
#define _UTILS_H_

/* Preproc max function. */
#define MAX(a, b) (((a)<(b))?(b):(a))

/* Preproc min function. */
#define MIN(a, b) (((a)>(b))?(b):(a))

/* Integer max function. */
inline int imax(int a, int b) { return a < b ? b : a; }

/* Integer min function. */
inline int imin(int a, int b) { return a > b ? b : a; }

#endif /* _UTILS_H_ */

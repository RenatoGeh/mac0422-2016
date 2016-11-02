#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <unistd.h>
#include <sys/svrctl.h>
#include <minix/type.h>
#include <lib.h>

/* Gets system information. */
void getsysinfo(int who, int what, void *where);
/* Gives out the mean, median and standard deviation of all holes.
 * Returns the number of elements in holes. */
int mem_data(struct hole *holes, double *mean, double *median, double *stddev);
/* Prints, in a single line, the state of each hole. */
void print_holes(void);

int main(int argc, char *args[]) {
  int secs;

  if (argc > 2) {
    printf("Usage:\n  %s [secs]\nArguments:\n"
        "  secs - number of seconds %s should run for. If secs < 0, "
        "then %s shall run until SIGKILL. If ommitted, secs = -1 by "
        "default.\n", args[0], args[0], args[0]);
    return 1;
  }

  if (argc == 2) secs = atoi(args[1]);
  else secs = -1;

  if (secs < 0) {
    while (1) {
      print_holes();
      sleep(1);
    }
  } else {
    int i;
    for (i = 0; i < secs; ++i) {
      print_holes();
      sleep(1);
    }
  }

  return 0;
}

/*getsysinfo(MM, SI_MEM_ALLOC, &store);*/
void getsysinfo(int who, int what, void *where) {
  message m;
  m.m1_i1 = what;
  m.m1_p1 = where;
  _syscall(who, GETSYSINFO, &m);
}

int cmp_func(const void *lval, const void *rval) {
  return *(int*)lval - *(int*)rval;
}

int mem_data(struct hole *holes, double *mean, double *median, double *stddev) {
  int n, i, t;
  struct hole *it = holes;
  int *ord_chks;
  *mean = *median = *stddev = 0;
  n = 0;
  for (i = 0; i < _NR_HOLES; ++i)
    if (holes[i].h_base && holes[i].h_len) {
      int bytes;
      bytes = holes[i].h_len << CLICK_SHIFT;
      *mean += bytes/1024.;
      ++n;
    }
  if (n == 0) {
    *median = *stddev = 0;
    return n;
  }
  *mean /= (double) n;
  ord_chks = (int*) malloc(n*sizeof(int));
  for (t = i = 0; i < _NR_HOLES; ++i)
    if (holes[i].h_base && holes[i].h_len) {
      int bytes;
      bytes = holes[i].h_len << CLICK_SHIFT;
      ord_chks[t++] = bytes;
    }
  t = n/2;
  qsort(ord_chks, n, sizeof(int), cmp_func);
  *median = ord_chks[t]/1024.;
  free(ord_chks);
  for (i = 0; i < _NR_HOLES; ++i)
    if (holes[i].h_base && holes[i].h_len) {
      int bytes;
      double k;
      bytes = holes[i].h_len << CLICK_SHIFT;
      k = (double) bytes/1024. - *mean;
      *stddev += k*k;
    }
  *stddev = sqrt(*stddev/n);
  return n;
}

void print_holes(void) {
  int n;
  double mean, median, stddev;
  static struct pm_mem_info store;

  getsysinfo(MM, SI_MEM_ALLOC, &store);
  n = mem_data(store.pmi_holes, &mean, &median, &stddev);

  printf("%d\t%.3f kB\t%.3f kB\t%.3f kB\n", n, mean, median, stddev);
}

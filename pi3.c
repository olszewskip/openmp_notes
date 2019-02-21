// copyright: Tim Mattson (Intel), me
#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 2
#define PAD 8

static long num_steps = 100000000;
int main() {
  int nthreads = 0;

  double pi = 0, sum[NUM_THREADS][PAD];

  const double step = 1.0 / (double)num_steps;

  omp_set_num_threads(NUM_THREADS);
  double time0 = omp_get_wtime();

  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    int nthrds = omp_get_num_threads();
    if (id == 0) nthreads = nthrds;

    double x;
    sum[id][0] = 0.0;
    for (int i = id; i < num_steps; i += nthrds) {
      x = (i + 0.5) * step;
      sum[id][0] += 4.0 / (1.0 + x * x);
    }
  }
  for (int i = 0; i < nthreads; i++) pi += sum[i][0];
  pi *= step;
  printf("%f\n", pi);

  double timeDiff = omp_get_wtime() - time0;
  printf("Finished in %f sec.\n", timeDiff);
}

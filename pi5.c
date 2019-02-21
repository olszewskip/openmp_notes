// copyright: Tim Mattson (Intel), me
#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 4

static long num_steps = 100000000;
int main() {
  const double step = 1.0 / (double)num_steps;
  double pi = 0.0;
  
  double time0 = omp_get_wtime();
  omp_set_num_threads(NUM_THREADS);
  #pragma omp parallel
  {
  double x;
  #pragma omp for reduction(+ : pi) schedule(static)
  for (int i = 0; i < num_steps; i++) {
    x = (i + 0.5) * step;
    pi += 4.0 / (1.0 + x * x);
  }
  }

  pi *= step;
  printf("%f\n", pi);

  double timeDiff = omp_get_wtime() - time0;
  printf("Finished in %f sec.\n", timeDiff);
}

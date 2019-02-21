// copyright: Tim Mattson (Intel)
#include <omp.h>
#include <stdio.h>

int main() {
    double A[1000];
    omp_set_num_threads(2);
#pragma omp parallel
  {
    int ID = omp_get_thread_num();
    printf("hello world from thread (%d)\n", ID);
  }
}

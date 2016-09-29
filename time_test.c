#include <stdio.h>
#include "computepi.h"

int main(int argc, char const *argv[])
{
    __attribute__((unused)) int N = 400000000;
    double pi = 0.0;

#if defined(BASELINE)
    pi = compute_pi_baseline(N);
#endif

#if defined(LEIBNIZ_BASELINE)
    pi = compute_pi_leibniz_baseline(N);
#endif

#if defined(EULAR_BASELINE)
    pi = compute_pi_eular_baseline(N);
#endif

#if defined(TOSS)
    pi = compute_pi_toss(N);
#endif

#if defined(OPENMP_2)
    pi = compute_pi_openmp(N, 2);
#endif

#if defined(OPENMP_4)
    pi = compute_pi_openmp(N, 4);
#endif

#if defined(OPENMP_8)
    pi = compute_pi_openmp(N, 8);
#endif

#if defined(OPENMP_16)
    pi = compute_pi_openmp(N,16);
#endif

#if defined(AVX)
    pi = compute_pi_avx(N);
#endif

#if defined(AVXUNROLL)
    pi = compute_pi_avx_unroll(N);
#endif
    printf("N = %d , pi = %lf\n", N, pi);

    return 0;
}

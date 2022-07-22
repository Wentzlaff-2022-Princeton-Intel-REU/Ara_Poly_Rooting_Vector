/*--------------------------------------------------------------------*/
/* newton.c                                                           */
/*--------------------------------------------------------------------*/

#include <float.h>
#include <math.h>
#include <riscv_vector.h>
#include <stdlib.h>
#include <stdbool.h>
#include "derivative.h"
#include "horner.h"
#include "longDiv.h"
#include "newton.h"
#include "printf.h"

/*--------------------------------------------------------------------*/

// the compare function for double values
static int compare(const void * a, const void * b) {
  if (*(double*)a > *(double*)b)
    return 1;
  else if (*(double*)a < *(double*)b)
    return -1;
  else
    return 0;  
}

void newton(Polynomial_t poly, double* roots, double convCrit) {
    for (int i = 0; i < poly.degree; i++) {
      roots[i] = DBL_MAX;
    }
    printf("test -1.0\n");

    int guessSize = 8;
    if (poly.degree < 8) {
        guessSize = poly.degree;
    }
    printf("test -1.1\n");

    double xGuess [guessSize];
    // double* oldXGuess [guessSize];
    // double* diff [guessSize];
    // double* oldDiff [guessSize];

    vfloat64m1_t va, vb, vc, vd;
    printf("test -1.2\n");

    for (int i = 0; i < guessSize; i++){
        xGuess[i] = (double) rand() / (double) rand();
        // oldXGuess[i] = 0;
        // diff[i] = xGuess[i];
        // oldDiff[i] = 0;
    }
    printf("test -1.3\n");

    va = vle64_v_f64m1(xGuess, guessSize);
    vb = vfmv_v_f_f64m1(0, guessSize);
    vc = vle64_v_f64m1(xGuess, guessSize);
    vd = vfmv_v_f_f64m1(0, guessSize);
    printf("test -1.4\n");

    // Polynomial_t newPoly = poly;
    Polynomial_t polyDeriv;
    double a_n [poly.degree + 1];
    polyDeriv.coefficients = a_n;
    derivative(poly, &polyDeriv);
    printf("test -1.5\n");

    int i = 0;
    while (poly.degree > 0) {
        printf("test 0\n");
        // bool cond = true;
        long cond1 = 0;
        bool firstLoop = true;
        do {
            printf("test 1\n");
            // bool noRoots = true;
            double polyGuess [guessSize];
            double polyDerivGuess [guessSize];
            horner(poly, xGuess, polyGuess, guessSize);
            horner(polyDeriv, xGuess, polyDerivGuess, guessSize);

            printf("test 2\n");
            vfloat64m1_t ve, vf, ones;
            ones = vfmv_v_f_f64m1(1, guessSize);
            ve = vle64_v_f64m1(polyGuess, guessSize);
            vf = vle64_v_f64m1(polyDerivGuess, guessSize);
            vf = vfdiv_vv_f64m1(ones, vf, guessSize);

            // for (int j = 0; j < 2; j++) {
            //     oldXGuess[j] = xGuess[j];
            //     xGuess[j] -= polyGuess[j] / polyDerivGuess[j];
            //     oldDiff[j] = diff[j];
            //     diff[j] = fabs(xGuess[j] - oldXGuess[j]);
            // }

            vb = vmv_v_v_f64m1(va, guessSize);
            va = vfnmsac_vv_f64m1(va, ve, vf, guessSize);
            vd = vmv_v_v_f64m1(vc, guessSize);
            vc = vfabs_v_f64m1(vfsub_vv_f64m1(va, vb, guessSize), guessSize);

            vse64_v_f64m1(xGuess, va, guessSize);  
            printf("test 3\n");

            // printf("guess: %lf, diff: %lf\n", xGuess, fabs(xGuess - oldXGuess));

            // for (int j = 0; j < 2; j++) {
            //     printf("guess: %lf, oldGuess: %lf, oldDiff: %lf, diff: %lf\n", xGuess[j], oldXGuess[j], oldDiff[j], diff[j]);
            // }

            // for (int j = 0; j < 2; j++) {
            //     noRoots = !firstLoop && diff[j] > oldDiff[j] && fabs(diff[j] - oldDiff[j]) > 1;
            //     if (!noRoots) {
            //         break;
            //     }
            // }

            vbool64_t vb1, vb2, vb3, vb4;

            vb1 = vmfgt_vv_f64m1_b64(vc, vd, guessSize);
            vb2 = vmfgt_vf_f64m1_b64(vfabs_v_f64m1(vfsub_vv_f64m1(vc, vd, guessSize), guessSize), 1, guessSize);
            vb3 = vmand_mm_b64(vb1, vb2, guessSize);
            long noRoots1 = vfirst_m_b64(vmnot_m_b64(vb3, guessSize), guessSize);

            printf("test 4\n");
            if (!firstLoop && noRoots1 == -1) {
                printf("exit to early\n");
                qsort(roots, poly.degree, sizeof(double), compare);
                return;
            }

            // cond = diff[0] > convCrit && diff[1] > convCrit;

            vfloat64m1_t crit;
            crit = vfmv_v_f_f64m1(convCrit, guessSize);
            vb4 = vmfgt_vv_f64m1_b64(vc, crit, guessSize);
            cond1 = vfirst_m_b64(vmnot_m_b64(vb4, guessSize), guessSize);

            firstLoop = false;
        } while (cond1 == -1);

        printf("test 5\n");
        for (int j = 0; j < guessSize; j++) {
            int degree = poly.degree;
            longDiv(&poly, a_n, xGuess[j], convCrit);

            if (degree != poly.degree) {
                printf("test 6\n");
                roots[i] = xGuess[j];
                i++;
            }
        }
        printf("test 7\n");
        derivative(poly, &polyDeriv);
    }
    qsort(roots, poly.degree, sizeof(double), compare);
}
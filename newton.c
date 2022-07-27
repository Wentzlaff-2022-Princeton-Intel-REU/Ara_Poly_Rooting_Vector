/*--------------------------------------------------------------------*/
/* newton.c                                                           */
/*--------------------------------------------------------------------*/

#include <float.h>
#include <math.h>
#include <riscv_vector.h>
// #include <stdio.h>
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
    int n = poly.degree;
    for (int i = 0; i < n; i++) {
      roots[i] = DBL_MAX;
    }
    // printf("test -1.0\n");

    size_t guessSize = vsetvlmax_e32m1();
    // printf("test -1.1\n");

    double guesses[guessSize];
    for (size_t i = 0; i < guessSize; i++) {
        guesses[i] = (rand() % 11) - 5;
    }
    // double* oldXGuess[guessSize];
    // double* diff[guessSize];
    // double* oldDiff[guessSize];

    // printf("test -1.2\n");

    vfloat64m1_t vGuesses, vOldGuesses, vDiff, vOldDiff;
    // printf("test -1.2.1\n");
    // vuint64m1_t test = vid_v_u64m1(guessSize);
    // vfloat64m1_t test2 = vreinterpret_v_u64m1_f64m1(test);
    // printf("test -1.2.1.1\n");
    vGuesses = vle64_v_f64m1(guesses, guessSize);
    // printf("test -1.2.2\n");
    vOldGuesses = vfmv_v_f_f64m1(0, guessSize);
    // printf("test -1.2.3\n");
    vDiff = vGuesses;
    // printf("test -1.2.4\n");
    vOldDiff = vOldGuesses;
    // printf("test -1.3\n");

    Polynomial_t polyDeriv;
    double a_n[n + 1];
    polyDeriv.coefficients = a_n;
    // printf("test -1.4\n");
    derivative(poly, &polyDeriv);

    int rootIndex = 0;
    // printf("test -1.5\n");
    while (poly.degree > 0) {
        // printf("test 0\n");
        // bool cond = true;
        // long cond = 0;
        bool firstLoop = true;
        // printf("test -1.6\n");
        do {
            // printf("test 1\n");
            // bool noRoots = true;

            // printf("test 2\n");
            vfloat64m1_t polyGuess, polyDerivGuess;
            // printf("test -1.7\n");
            polyGuess = horner(poly, vGuesses, guessSize);
            // printf("test -1.8\n");
            polyDerivGuess = horner(polyDeriv, vGuesses, guessSize);
            // printf("test -1.9\n");

            // for (int j = 0; j < 2; j++) {
            //     oldXGuess[j] = xGuess[j];
            //     xGuess[j] -= polyGuess[j] / polyDerivGuess[j];
            //     oldDiff[j] = diff[j];
            //     diff[j] = fabs(xGuess[j] - oldXGuess[j]);
            // }

            vOldGuesses = vGuesses;
            vGuesses = vfsub_vv_f64m1(vGuesses, vfdiv_vv_f64m1(polyGuess, polyDerivGuess, guessSize), guessSize);
            vOldDiff = vmv_v_v_f64m1(vDiff, guessSize);
            vDiff = vfabs_v_f64m1(vfsub_vv_f64m1(vGuesses, vOldGuesses, guessSize), guessSize);
            // printf("test -1.10\n");

            // printf("test 3\n");

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

            vbool64_t greaterDiff, greaterThan1;
            greaterDiff = vmfgt_vv_f64m1_b64(vDiff, vOldDiff, guessSize);
            greaterThan1 = vmfgt_vf_f64m1_b64(vfabs_v_f64m1(vfsub_vv_f64m1(vDiff, vOldDiff, guessSize), guessSize), 1, guessSize);
            long noMoreRoots = vfirst_m_b64(vmnand_mm_b64(greaterDiff, greaterThan1, guessSize), guessSize);

            if (poly.degree % 2 == 0 && !firstLoop && noMoreRoots == -1) {
                // printf("exit to early\n");
                qsort(roots, rootIndex + 1, sizeof(double), compare);
                return;
            }

            // cond = diff[0] > convCrit && diff[1] > convCrit;

            long diffGreaterThanConvCrit = vfirst_m_b64(vmnot_m_b64(vmfgt_vf_f64m1_b64(vDiff, convCrit, guessSize), guessSize), guessSize);
            long oldDiffGreaterThanConvCrit = vfirst_m_b64(vmnot_m_b64(vmfgt_vf_f64m1_b64(vOldDiff, convCrit, guessSize), guessSize), guessSize);
            // long diffGreaterThanConvCrit = vfirst_m_b64(vmfle_vf_f64m1_b64(vDiff, convCrit, guessSize), guessSize);
            // long oldDiffGreaterThanConvCrit = vfirst_m_b64(vmfle_vf_f64m1_b64(vOldDiff, convCrit, guessSize), guessSize);

            // cond1 = vfirst_m_b64(vmnot_m_b64(vb4, guessSize), guessSize);
            if (diffGreaterThanConvCrit != -1 && oldDiffGreaterThanConvCrit != -1) {
                break;
            }

            firstLoop = false;
        } while (true);

        // printf("test 5\n");
        vse64_v_f64m1(guesses, vGuesses, guessSize);
        bool notFinite = false;
        for (size_t j = 0; j < guessSize; j++) {
            int degree = poly.degree;
            longDiv(&poly, a_n, guesses[j], convCrit);

            if (degree != poly.degree) {
                roots[rootIndex] = guesses[j];
                rootIndex++;
            }
            else if (!isfinite(guesses[j])) {
                notFinite = true;
                guesses[j] = (rand() % 11) - 5;
            }
        }
        // for (int j = 0; j < i; j++) {
        //     printf("Roots: %.3f\n", roots[j]);
        // }

        // printf("test 7\n");
        derivative(poly, &polyDeriv);
        if (notFinite) {
            vGuesses = vle64_v_f64m1(guesses, guessSize);
        }
    }
    qsort(roots, n, sizeof(double), compare);
}
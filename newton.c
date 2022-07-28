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
    int n = poly.degree;
    for (int i = 0; i < n; i++) {
      roots[i] = DBL_MAX;
    }

    size_t guessSize = vsetvlmax_e64m1();

    double guesses[64];
    for (size_t i = 0; i < guessSize; i++) {
        guesses[i] = (rand() % 11) - 5;
    }
    // double* oldXGuess[guessSize];
    // double* diff[guessSize];
    // double* oldDiff[guessSize];


    vfloat64m1_t vGuesses, vOldGuesses, vDiff, vOldDiff;
    vGuesses = vle64_v_f64m1(guesses, guessSize);
    vOldGuesses = vfmv_v_f_f64m1(0, guessSize);
    vDiff = vGuesses;
    vOldDiff = vOldGuesses;

    Polynomial_t polyDeriv;
    double a_n[n + 1];
    polyDeriv.coefficients = a_n;

    int rootIndex = 0;
    while (poly.degree > 0) {
        // derivative(poly, &polyDeriv);
        // pointers for the resulting coefficients (after taking the derivative) and the
        // original coefficients
        polyDeriv.degree = poly.degree - 1;
        double* results = polyDeriv.coefficients;
        double* coeffs = poly.coefficients + 1; // the constant at index 0 is not included in the derivative

        // array that just holds 1 to n, where n is the degree of the original polynomial.
        // this represents the exponents of the polynomial
        double indices[poly.degree];
        for(int i = 0; i < poly.degree; i++){
            indices[i] = i + 1;
        }

        //active vector length is the degree of the original polynomial
        size_t avl = poly.degree;
        // declare vector registers
        vfloat64m1_t vCoeffs, vIndices, vResults;

        for (size_t vl; (vl = vsetvl_e64m1(avl)) > 0; avl -= vl) {
            // load in original coefficients into vCoeffs
            vCoeffs = vle64_v_f64m1(coeffs, vl);
            // load in array of exponents
            vIndices = vle64_v_f64m1(indices, vl);
            // multiply the two and put the result in vResults
            vResults = vfmul_vv_f64m1(vCoeffs, vIndices, vl);
            // store the resulting coefficients into our differentiated polynomial
            vse64_v_f64m1(results, vResults, vl);

            // move the pointers
            coeffs += vl;
            *indices += vl;
            results += vl;
        }
        bool firstLoop = true;
        do {
            vfloat64m1_t polyGuess, polyDerivGuess;
            // polyGuess = horner(poly, vGuesses, guessSize);
            // polyDerivGuess = horner(polyDeriv, vGuesses, guessSize);
            vfloat64m1_t currCoeff, currCoeffDeriv;

            // filling the vector solutions with the coefficient of the high degree
            polyGuess = vfmv_v_f_f64m1(poly.coefficients[poly.degree], guessSize);
            polyDerivGuess = vfmv_v_f_f64m1(poly.coefficients[poly.degree], guessSize);

            for (int i = poly.degree; i > 0; i--){
                /* moves g one of the polynomial's coefficients
                (starting with the coefficient of the second high degree and
                moving to that of the lowest degree) to a vector */
                currCoeff = vfmv_v_f_f64m1(poly.coefficients[i-1], guessSize);
                currCoeffDeriv = vfmv_v_f_f64m1(poly.coefficients[i-1], guessSize);
                // solutions += vGuesses * currCoeff
                polyGuess = vfmadd_vv_f64m1(polyGuess, vGuesses, currCoeff, guessSize);
                polyDerivGuess = vfmadd_vv_f64m1(polyGuess, vGuesses, currCoeff, guessSize);
            }

            double solutions[64];
            double solutionsDeriv[64];
            vse64_v_f64m1(solutions, polyGuess, guessSize);
            vse64_v_f64m1(solutionsDeriv, polyDerivGuess, guessSize);

            double quotient[64];
            for (size_t i = 0; i < guessSize; i++) {
                quotient[i] = solutions[i] / solutionsDeriv[i];
            }
            vfloat64m1_t vQuotient = vle64_v_f64m1(quotient, guessSize);

            // for (int j = 0; j < 2; j++) {
            //     oldXGuess[j] = xGuess[j];
            //     xGuess[j] -= polyGuess[j] / polyDerivGuess[j];
            //     oldDiff[j] = diff[j];
            //     diff[j] = fabs(xGuess[j] - oldXGuess[j]);
            // }

            vOldGuesses = vGuesses;
            vGuesses = vfsub_vv_f64m1(vGuesses, vQuotient, guessSize);
            vOldDiff = vmv_v_v_f64m1(vDiff, guessSize);
            vDiff = vfabs_v_f64m1(vfsub_vv_f64m1(vGuesses, vOldGuesses, guessSize), guessSize);

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

            // vbool64_t greaterDiff, greaterThan1;
            // greaterDiff = vmfgt_vv_f64m1_b64(vDiff, vOldDiff, guessSize);
            // greaterThan1 = vmfgt_vf_f64m1_b64(vfabs_v_f64m1(vfsub_vv_f64m1(vDiff, vOldDiff, guessSize), guessSize), 1, guessSize);
            // long noMoreRoots = vfirst_m_b64(vmnand_mm_b64(greaterDiff, greaterThan1, guessSize), guessSize);

            double diff[64];
            double oldDiff[64];
            vse64_v_f64m1(diff, vDiff, guessSize);
            vse64_v_f64m1(oldDiff, vOldDiff, guessSize);
            if (poly.degree % 2 == 0 && !firstLoop) {
                bool noMoreRoots = true;

                for (size_t i = 0; i < guessSize; i++) {
                    if (diff[i] <= oldDiff[i] || fabs(diff[i] - oldDiff[i]) <= 1) {
                        noMoreRoots = false;
                        break;
                    }
                }
                if (noMoreRoots) {
                    qsort(roots, rootIndex + 1, sizeof(double), compare);
                    return;
                }
            }

            // cond = diff[0] > convCrit && diff[1] > convCrit;

            // long diffGreaterThanConvCrit = vfirst_m_b64(vmnot_m_b64(vmfgt_vf_f64m1_b64(vDiff, convCrit, guessSize), guessSize), guessSize);
            // long oldDiffGreaterThanConvCrit = vfirst_m_b64(vmnot_m_b64(vmfgt_vf_f64m1_b64(vOldDiff, convCrit, guessSize), guessSize), guessSize);
            bool diffGreaterThanConvCrit = true;
            bool oldDiffGreaterThanConvCrit = true;
            for (size_t i = 0; i < guessSize; i++) {
                if (!(diffGreaterThanConvCrit || oldDiffGreaterThanConvCrit)) {
                    break;
                }
                if (diffGreaterThanConvCrit && !isnan(diff[i]) && diff[i] <= convCrit) {
                    diffGreaterThanConvCrit = false;
                }
                if (oldDiffGreaterThanConvCrit && !isnan(oldDiff[i]) && oldDiff[i] <= convCrit) {
                    oldDiffGreaterThanConvCrit = false;
                }
            }
            if (!(diffGreaterThanConvCrit || oldDiffGreaterThanConvCrit)) {
                break;
            }
            // if (diffGreaterThanConvCrit != -1 && oldDiffGreaterThanConvCrit != -1) {
            //     break;
            // }

            firstLoop = false;
        } while (true);

        vse64_v_f64m1(guesses, vGuesses, guessSize);
        bool notFinite = false;
        for (size_t j = 0; j < guessSize; j++) {
            int degree = poly.degree;
            // longDiv(&poly, a_n, guesses[j], convCrit);
            a_n[poly.degree - 1] = poly.coefficients[poly.degree];
            for (int i = poly.degree - 1; i > 0; i--) {
                a_n[i - 1] = poly.coefficients[i] + guesses[j] * a_n[i];
            }

            bool isRoot = true;
            // printf("guesses[j]: %.16lf, convCrit: %.16lf\n", guesses[j], fabs(poly.coefficients[0] + guesses[j] * a_n[0]));
            if (!isfinite(guesses[j]) || fabs(poly.coefficients[0] + guesses[j] * a_n[0]) > convCrit) {
                isRoot = false;
            }

            if (isRoot) {
                poly.degree -= 1;
                for (int i = poly.degree; i >= 0; i--) {
                    poly.coefficients[i] = a_n[i];
                }
            }

            if (degree != poly.degree) {
                roots[rootIndex] = guesses[j];
                rootIndex++;
            }
            else if (!isfinite(guesses[j])) {
                notFinite = true;
                guesses[j] = (rand() % 11) - 5;
            }
        }
        if (notFinite) {
            vGuesses = vle64_v_f64m1(guesses, guessSize);
        }
    }
    qsort(roots, n, sizeof(double), compare);
}
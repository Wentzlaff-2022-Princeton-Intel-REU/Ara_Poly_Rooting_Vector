/*--------------------------------------------------------------------*/
/* horner.c                                                           */
/*--------------------------------------------------------------------*/

#include <riscv_vector.h>
// #include <stdio.h>
#include "horner.h"
#include "printf.h"

/*--------------------------------------------------------------------*/

void horner(Polynomial_t poly, double* guesses, double* solutions, int guessSize) {
    // declare vector registers
    vfloat64m1_t va, vb, vSolutions;

    size_t avl = guessSize;

    for (size_t vl; (vl = vsetvl_e32m1(avl)) > 0; avl -= vl) {
        // Filling the vector vSolutions with the highest coefficient(s)
        vSolutions = vfmv_v_f_f64m1(poly.coefficients[poly.degree], vl);

        // This is the vector with our guesses (guesses vector).
        vb = vle64_v_f64m1(guesses, vl); 

        for (int i = poly.degree; i > 0; i--){

            // We are moving one of the polynomial's coefficients (starting with the degree largest one - 1 and moving to the degree lowest) to a vector.
            va = vfmv_v_f_f64m1(poly.coefficients[i-1], vl); 

            // We are multiply-adding this along with the guessesd vector (our guesses).
            vSolutions = vfmadd_vv_f64m1(vSolutions, vb, va, vl); 
        }

        // We are storing our results in the solutions array.
        vse64_v_f64m1(&solutions[guessSize - avl], vSolutions, vl);
    }
}




/*--------------------------------------------------------------------*/
/* newton.c                                                           */
/*--------------------------------------------------------------------*/

#include "printf.h"
#include "printPoly.h"

/*--------------------------------------------------------------------*/

void printPoly(Polynomial_t poly) {
    for (int i = poly.degree; i > 0; i--) {
        printf("%.1f * x^%d + ", poly.coefficients[i], i);
    }
    printf("%.1f\n\n", poly.coefficients[0]);
}
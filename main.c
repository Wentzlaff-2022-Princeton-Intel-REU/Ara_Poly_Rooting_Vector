/*--------------------------------------------------------------------*/
/* main.c                                                             */
/*--------------------------------------------------------------------*/

#include <float.h>
#include "newton.h"
#include "printf.h"
#include "printPoly.h"
#include "runtime.h"

/*--------------------------------------------------------------------*/

int main() {
    Polynomial_t poly;
    poly.degree = 7;
    double arr[] = {-5666.749, -2184.648, 2796.725, 1146.026, -271.885, -111.673, 6.821, 2.876};
    poly.coefficients = arr;

    double roots[poly.degree];
    double crit_conversion = 1e-10;

    // printf("Polynomial:\n");
    // printPoly(poly);

    start_timer();
    newton(poly, roots, crit_conversion);
    stop_timer();
    int64_t cycle_time = get_timer();

    // if (poly.degree == 0 || roots[0] == DBL_MAX) {
    //     printf("Your polynomial has no real roots.\n");
    // }
    // else {
    //     for (int i = 0; i < poly.degree; i++) {
    //         if (roots[i] == DBL_MAX) {
    //             break;
    //         }
    //         printf("The root approximation is: %.18f\n", roots[i]);
    //     }
    // }

    printf("\nRuntime (cycles): %d\n", cycle_time);

    return 0;
}

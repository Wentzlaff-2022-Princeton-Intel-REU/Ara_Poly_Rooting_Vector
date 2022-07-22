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
    double crit_conversion = 1e-14;
    
    Polynomial_t poly;
    poly.degree = 5;
    double arr[] = {120, 94, -51, -23, 3, 1};
    poly.coefficients = arr;

    printf("Polynomial:\n");
    printPoly(poly);

    double roots [poly.degree];
    start_timer();
    newton(poly, roots, crit_conversion);
    end_timer();
    int64_t cycle_time = get_timer()

    if (roots[0] == DBL_MAX) {
        printf("Your polynomial has no real roots.\n");
    }
    else {
        for (int i = 0; i < poly.degree; i++) {
            if (roots[i] == DBL_MAX) {
                break;
            }
            printf("The root approximation is: %.3f \n", roots[i]);
        }
    }

    printf("\nRuntime (cycles): %d\n", cycle_time);

    return 0;
}

/*--------------------------------------------------------------------*/
/* main.c                                                             */
/*--------------------------------------------------------------------*/

#include <float.h>
#include "newton.h"
#include "printf.h"
#include "printPoly.h"
#include "runtime.h"

/*--------------------------------------------------------------------*/

int main(int argc, char *argv[]) {
    double crit_conversion = 1e-14;
    
     Polynomial_t poly;
    poly.degree = 5;
    double arr[] = {120, 94, -51, -23, 3, 1};
    poly.coefficients = arr;

printf("Polynomial:\n");
    printPoly(poly);

    start_timer();
    double* roots = newton(poly, crit_conversion);
    end_timer();

    if (roots[0] == DBL_MAX) {
        printf("Your polynomial has no roots.\n");
    }
    else {
        for (int i = 0; i < poly.degree; i++) {
            if (roots[i] == DBL_MAX) {
                break;
            }
            printf("The root approximation is: %.14lg \n", roots[i]);
        }
    }
        printf("\nRuntime (cycles): %d\n", cycle_time);

    
    // for (int i = 0; i <= polyd.degree; i++) {
    //     printf("%lf \n", polyd.coefficients[i]);
    // }

    return 0;
}

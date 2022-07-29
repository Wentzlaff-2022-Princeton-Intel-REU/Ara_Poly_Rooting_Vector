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
    poly.degree = 2;
    double arr[] = {-0, 1, -2};
    poly.coefficients = arr;

for (int i = 2; i <= 20; i++){
        
        if (i == 2) {
            poly.degree = 2;
            double inForArr[] = {0, 1, -2};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n %d th degree Runtime (cycles): %d\n", i, cycleTime);
        }
        

        else if (i == 3) {
            poly.degree = 3;
            double inForArr[] = {68, 56, 16, 1};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n %d th degree Runtime (cycles): %d\n", i, cycleTime);
        }

        else if (i == 4) {
            poly.degree = 4;
            double inForArr[] = {0, -1, 6, 3, -1};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n %d th degree Runtime (cycles): %d\n", i, cycleTime);
        }

        else if (i == 5) {
            poly.degree = 5;
            double inForArr[] = {1523, 1888, 675, 10, -34, -4};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n %d th degree Runtime (cycles): %d\n", i, cycleTime);
        }

        else if (i == 6) {
            poly.degree = 6;
            double inForArr[] = {-0, -2, 10, -3, -26, -16, -2};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n %d th degree Runtime (cycles): %d\n", i, cycleTime);
        }

        else if (i == 7) {
            poly.degree = 7;
            double inForArr[] = {-0, 4, -9, 4, 8, -8, -1, 2};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n %d th degree Runtime (cycles): %d\n", i, cycleTime);
        }
        else if (i == 8) {
            poly.degree = 8;
            double inForArr[] = {17, 109, 108, -264, -84, 94, 19, -8, -2};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n %d th degree Runtime (cycles): %d\n", i, cycleTime);
        }
        else if (i == 9) {
            poly.degree = 9;
            double inForArr[] = {385, 398, -1473, -61, 958, 16, -232, -20, 20, 3};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n %d th degree Runtime (cycles): %d\n", i, cycleTime);
        }
        else if (i == 10) {
            poly.degree = 10;
            double inForArr[] = {2, -31, 92, 240, -1064, 1164, -364, -111, 67, 1, -2};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n %d th degree Runtime (cycles): %d\n", i, cycleTime);
        }

        else if (i == 11) {
            poly.degree = 11;
            double inForArr[] = {3293, -19534, 3515, 20414, -12265, -2174, 3636, -842, -128, 88, -14, 1};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n 11 th degree Runtime (cycles): %d\n", cycleTime);
        }

        else if (i == 12) {
            poly.degree = 12;
            double inForArr[] = {3931, -34988, -46295, 43863, 51022, -21318, -19968, 4714, 3102, -370, -190, 9, 4};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n 12 th degree Runtime (cycles): %d\n", cycleTime);
        }
        else if (i == 13) {
            poly.degree = 13;
            double inForArr[] = {7015, -15928, -22801, 47562, 43198, -41872, -43736, 857, 8589, 1003, -596, -96, 14, 2};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n 13 th degree Runtime (cycles): %d\n", cycleTime);
        }

        else if (i == 14) {
            poly.degree = 14;
            double inForArr[] = {-264630, 551249, 58812, -678920, 299093, 158705, -112782, -10828, 16175, -259, -1130, 52, 40, -1, -1};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n 14 th degree Runtime (cycles): %d\n", cycleTime);
        }

        else if (i == 15) {
            poly.degree = 15;
            double inForArr[] = {350394, -1743475, 2019339, 691788, -1657561, 73441, 507844, -78739, -77574, 15952, 6281, -1468, -256, 64, 4, -1};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n 15 th degree Runtime (cycles): %d\n", cycleTime);
        }


        else if (i == 16) {
            poly.degree = 16;
            double inForArr[] = {-27, 334, -423, -4391, 6413, 20424, -11729, -43246, -12006, 21861, 13908, -797, -2526, -512, 72, 33, 3};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n 16 th degree Runtime (cycles): %d\n", cycleTime);
        }

        else if (i == 17) {
            poly.degree = 17;
            double inForArr[] = {-1289, -60, 16027, -17794, -37415, 63689, 14014, -61168, 9519, 22474, -4872, -4179, 708, 405, -40, -19, 1, 0};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n 17 th degree Runtime (cycles): %d\n", cycleTime);
        }

        else if (i == 18) {
            poly.degree = 18;
            double inForArr[] = {-26099, -25191, 312744, -193094, -799923, 1075242, 260045, -1231299, 694193, 91504, -228937, 68658, 11137, -10674, 1800, 223, -122, 17, -1};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n 18 th degree Runtime (cycles): %d\n", cycleTime);
        }

        else if (i == 19) {
            poly.degree = 19;
            double inForArr[] = {3187, -54027, -1036681, -107944, 2209456, 319004, -1928760, -277945, 892434, 123518, -237036, -32198, 36666, 5120, -3210, -477, 145, 23, -3, -0};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n 19 th degree Runtime (cycles): %d\n", cycleTime);
        }

        else if (i == 20) {
            poly.degree = 20;
            double inForArr[] = {-110302, -1029451, 41402983, 7646761, -114224450, 6263551, 112705234, -26008572, -48130156, 16665257, 9689459, -4411060, -894303, 578364, 23975, -39417, 1627, 1331, -118, -18, 2};
            poly.coefficients = inForArr;
            double roots[poly.degree];
            double convCrit = 1e-14;

            start_timer();
            newton(poly, roots, convCrit);
            stop_timer();
            int64_t cycleTime = get_timer();

            printf("\n 20 th degree Runtime (cycles): %d\n", cycleTime);
        }

    }

    return 0;
}

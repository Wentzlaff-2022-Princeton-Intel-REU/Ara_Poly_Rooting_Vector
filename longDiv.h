#pragma once
/*------------------------------------------------------------*/
/* longDiv.h                                                   */
/*------------------------------------------------------------*/

#include "polynomial.h"

/*------------------------------------------------------------*/

/* performs long division on a polynomial dividend and a linear
polynomial divisor and returns a polynomial quotient */
void longDiv(Polynomial_t* poly, double* a_n, double root, double diff);

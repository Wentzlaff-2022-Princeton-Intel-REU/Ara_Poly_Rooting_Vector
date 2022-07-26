#pragma once
/*------------------------------------------------------------*/
/* newton.h                                                   */
/*------------------------------------------------------------*/

#include "polynomial.h"

/*------------------------------------------------------------*/

/* Uses Newton's method to produce successively better
approximations to the roots (or zeroes) of a real-valued
function. Creates an array of all the real roots of the given
polynomial. */
void newton(Polynomial_t poly, double* roots, double convCrit);
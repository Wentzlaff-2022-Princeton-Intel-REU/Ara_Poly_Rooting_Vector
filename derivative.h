#pragma once
/*------------------------------------------------------------*/
/* derivative.h                                               */
/*------------------------------------------------------------*/

#include "polynomial.h"

/*------------------------------------------------------------*/

/* The derivative function takes in a Polynomial_t
object as input and set differentiatedPoly to its derivative. */
void derivative(Polynomial_t myPoly, Polynomial_t* differentiatedPoly);


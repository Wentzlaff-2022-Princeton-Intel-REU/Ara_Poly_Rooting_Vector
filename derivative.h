#pragma once
/*------------------------------------------------------------*/
/* derivative.h                                               */
/*------------------------------------------------------------*/

#include "polynomial.h"

/*------------------------------------------------------------*/

/* The differentiatePoly function takes in a Polynomial_t
object as input, differentiates it, and returns a differentiated
Polynomial_t object as output. */
void derivative(Polynomial_t myPoly, Polynomial_t* differentiatedPoly);


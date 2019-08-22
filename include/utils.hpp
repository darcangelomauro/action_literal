#ifndef UTILS_HPP
#define UTILS_HPP

#include "derivative.hpp"

Derivative compute_B4(const int&, const int&, const int&, const int&, int*);
Derivative compute_B2(const int&, const int&, int*);
Derivative compute_B(const int&, int*);
Derivative der_dirac4(const int&, int*, const int&);
Derivative der_dirac2(int*, const int&);


#endif

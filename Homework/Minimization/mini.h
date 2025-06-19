// #ifndef HAVE_SPLINE_H
// #define HAVE_SPLINE_H

#include"matrix.h"
// #include"vector.h"
#include<exception>
#include<cmath>

vector newton(const std::function<double(double)>& f, vector x, double acc=1e-3);
vector gradient(const std::function<double(double)>& f, vector x);
matrix hessian(const std::function<double(double)>& f, vector x);


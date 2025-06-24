// #ifndef HAVE_SPLINE_H
// #define HAVE_SPLINE_H

#include"matrix.h"
#include"vector.h"
#include"QR.h"
#include<exception>
#include<functional>
#include<cmath>

vector newton(const std::function<vector(vector)>& f, vector x, double acc=1e-5, vector δx=vector(0));
matrix hessian(const std::function<vector(vector)>& f, vector x, vector fx=vector(0), vector δx=vector(0));


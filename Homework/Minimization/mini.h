// #ifndef HAVE_SPLINE_H
// #define HAVE_SPLINE_H

#include"matrix.h"
#include"vector.h"
#include"QR.h"
#include<exception>
#include<functional>
#include<cmath>

std::tuple<vector, int> newton(const std::function<double(vector)>& f, vector x, double acc=1e-5);
std::tuple<vector, int> newton2(const std::function<double(vector)>& f, vector x, double acc=1e-5);
vector gradient(const std::function<double(vector)>& f, vector x);
matrix hessian(const std::function<double(vector)>& f, vector x);
std::tuple<vector, matrix> GH2(const std::function<double(vector)>& f, vector x);


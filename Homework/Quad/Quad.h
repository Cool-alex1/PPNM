#ifndef HAVE_QUAD_H
#define HAVE_QUAD_H

#include<exception>
#include<functional>
#include<vector>
#include<tuple>
#include"vector.h"

std::tuple<double, double, int> integrate(
    const std::function<double(double)>& f,
    double a, double b,
    double acc, 
    double eps,
    double f2=NAN, double f3=NAN,
    int n=1);

std::tuple<double, double, int> integrate_CC(
    const std::function<double(double)>& f,
    double a, double b,
    double acc, 
    double eps);

#endif
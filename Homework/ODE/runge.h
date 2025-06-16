#ifndef HAVE_RUNGE_H
#define HAVE_RUNGE_H

#include<exception>
#include<functional>
#include<vector>
#include<tuple>
#include"vector.h"
#include"matrix.h"

std::tuple<vector, vector> rkstep12(
    std::function<vector(double, vector)> f,
    double x, 
    vector y, 
    double h);

std::tuple<vector, std::vector<vector>> rkdriver(
    std::function<vector(double, vector)> f,
    double a, double b,
    vector yinit,
    double h0 = 0.125,
    double acc = 0.01, 
    double eps = 0.01);

#endif
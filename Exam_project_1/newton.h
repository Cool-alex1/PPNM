#include"Helper/vector.h"
#include"Helper/matrix.h"
#include<iostream>
#include<string>
#include<cmath>

vector gradient(const std::function<double(vector)>& f, vector v, matrix H, double R);
double findMin(const std::function<double(vector)>& f, double a0, double aStep, vector v, vector Δv, double acc);
vector newton(const std::function<double(vector)>& f, vector v, matrix H, double acc, std::string p = "n");

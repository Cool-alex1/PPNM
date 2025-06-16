#include<iostream>
#include<functional>
#include<tuple>
#include<cmath>
#include"vector.h"
#include"Quad.h"

std::function<double(double)> erfh1 = [](double x) {return std::exp(-x*x);};
std::function<double(double)> erfh2(double z) {
    std::function<double(double)> f = [=](double t) {
        return std::exp(-std::pow(z+(1-t)/t, 2))/t/t;
    };
    return f;};
double erf(double z, double acc) {if(z<0) return -erf(-z);
                      else if(0 <= z && z <= 1) return 2/std::sqrt(M_PI)*std::get<0>(integrate(erfh1, 0, z, acc, 0));
                      return 1-2/std::sqrt(M_PI)*std::get<0>(integrate(erfh2(z), 0, 1, acc, 0));};

int main(int argc, char** argv) {
    std::string acc = "";
    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];
        if(arg == "-acc" && i+1<argc) acc = argv[i + 1];
    }
    double a = std::pow(2, -stod(acc));

    double erf_v = std::abs(0.84270079294971486934 - erf(1, a));
    std::cout << a << ", " << erf_v << std::endl;

    
    return 0;
}
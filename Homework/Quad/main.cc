#include<iostream>
#include<functional>
#include<tuple>
#include<cmath>
#include"vector.h"
#include"Quad.h"

std::function<double(double)> func = [](double x) {return x;};
std::function<double(double)> func1 = [](double x) {return std::sqrt(x);};
std::function<double(double)> func2 = [](double x) {return 1/std::sqrt(x);};
std::function<double(double)> func3 = [](double x) {return std::sqrt(1-x*x);};
std::function<double(double)> func4 = [](double x) {return std::log(x)/std::sqrt(x);};
std::function<double(double)> func5 = [](double x) {return 1/(x*x*x);};

std::function<double(double)> erfh1 = [](double x) {return std::exp(-x*x);};
std::function<double(double)> erfh2(double z) {
    std::function<double(double)> f = [=](double t) {
        return std::exp(-std::pow(z+(1-t)/t, 2))/t/t;
    };
    return f;};

double erf(double z) {if(z<0) return -erf(-z);
                      else if(0 <= z && z <= 1) return 2/std::sqrt(M_PI)*std::get<0>(integrate(erfh1, 0, z, 0.0001, 0.0001));
                      return 1-2/std::sqrt(M_PI)*std::get<0>(integrate(erfh2(z), 0, 1, 0.0001, 0.0001));};



std::function<double(double)> f_gauss = [](double x) {return 1/std::sqrt(2*M_PI)*std::exp(-0.5*x*x);};

int main(int argc, char** argv) {
    double a, b;
    double acc, eps;
    double I;
    double err;
    int eval;
    double Iana;
    acc = 0.0001, eps = 0.0001;
    
    
    std::cout << "A)" << std::endl;
    std::cout << "f(x) = x" << std::endl;
    a = 0, b = 1;
    auto integral1 = integrate(func, a, b, acc, eps);
    I = std::get<0>(integral1);
    err = std::get<1>(integral1);
    eval = std::get<2>(integral1);
    std::cout << I << " +- " << err << "   eval: " << eval << std::endl;
    std::cout << "Expected: " << "1/2" << std::endl;
    
    std::cout << "\nf(x) = √​​x" << std::endl;
    a = 0, b = 1;
    auto integral2 = integrate(func1, a, b, acc, eps);
    I = std::get<0>(integral2);
    err = std::get<1>(integral2);
    eval = std::get<2>(integral2);
    std::cout << I << " +- " << err << "   eval: " << eval << std::endl;
    std::cout << "Expected: " << "2/3" << std::endl;
    
    std::cout << "\nf(x) = 1/√​​x" << std::endl;
    a = 0, b = 1;
    auto integral3 = integrate(func2, a, b, acc, eps);
    I = std::get<0>(integral3);
    err = std::get<1>(integral3);
    eval = std::get<2>(integral3);
    std::cout << I << " +- " << err << "   eval: " << eval << std::endl;
    std::cout << "Expected: " << "2" << std::endl;
    
    std::cout << "\nf(x) = √(1-x^2)" << std::endl;
    a = 0, b = 1;
    auto integral4 = integrate(func3, a, b, acc, eps);
    I = std::get<0>(integral4);
    err = std::get<1>(integral4);
    eval = std::get<2>(integral4);
    std::cout << I << " +- " << err << "   eval: " << eval << std::endl;
    std::cout << "Expected: " << "π/4 = 0,785398" << std::endl;
    
    std::cout << "\nf(x) = ln(x)/√x" << std::endl;
    a = 0, b = 1;
    auto integral5 = integrate(func4, a, b, acc, eps);
    I = std::get<0>(integral5);
    err = std::get<1>(integral5);
    eval = std::get<2>(integral5);
    std::cout << I << " +- " << err << "   eval: " << eval << std::endl;
    std::cout << "Expected: " << "-4" << std::endl;
    
    
    
    std::cout << "\n\nError function:" << std::endl;
    double integral = erf(1);
    std::cout << integral << std::endl;
    
    
    
    std::cout << "\n\nB)" << std::endl;
    std::cout << "Clenshaw–Curtis" << std::endl;
    std::cout << "f(x) = 1/√​​x" << std::endl;
    a = 0, b = 1;
    auto integral6 = integrate_CC(func2, a, b, acc, eps);
    I = std::get<0>(integral6);
    err = std::get<1>(integral6);
    eval = std::get<2>(integral6);
    std::cout << I << " +- " << err << "   eval: " << eval << " (Scipy: 231)" << std::endl;
    std::cout << "Expected: " << "2" << std::endl;
    
    std::cout << "\nf(x) = ln(x)/√x" << std::endl;
    a = 0, b = 1;
    auto integral7 = integrate_CC(func4, a, b, acc, eps);
    I = std::get<0>(integral7);
    err = std::get<1>(integral7);
    eval = std::get<2>(integral7);
    std::cout << I << " +- " << err << "   eval: " << eval << " (Scipy: 315)" <<std::endl;
    std::cout << "Expected: " << "-4" << std::endl;
    
    
    
    
    std::cout << "\n\nIninit limits" << std::endl;
    std::cout << "f(x) = 1/x^3" << std::endl;
    a = 1, b = std::numeric_limits<double>::infinity();
    auto integral8 = integrate_CC(func5, a, b, acc, eps);
    I = std::get<0>(integral8);
    err = std::get<1>(integral8);
    eval = std::get<2>(integral8);
    Iana = 0.5;
    std::cout << I << " +- " << err << "   eval: " << eval << " (Scipy: 15)"  << std::endl;
    std::cout << "Expected: " << "1/2" << std::endl;
    std::cout << "err estimate and actual err: " << err << " ~ " << std::abs(I - Iana) << std::endl;
    
    
    std::cout << "\nf(x) = 1/√(2π)*e^(-1/2*x^2)" << std::endl;
    a = -std::numeric_limits<double>::infinity(), b = std::numeric_limits<double>::infinity();
    auto integral9 = integrate_CC(f_gauss, a, b, acc, eps);
    I = std::get<0>(integral9);
    err = std::get<1>(integral9);
    eval = std::get<2>(integral9);
    Iana = 1;
    std::cout << I << " +- " << err << "   eval: " << eval << " (Scipy: 150)"  << std::endl;
    std::cout << "Expected: " << 1 << std::endl;
    std::cout << "err estimate and actual err: " << err << " ~ " << std::abs(I - Iana) << std::endl;

    
    return 10;
}
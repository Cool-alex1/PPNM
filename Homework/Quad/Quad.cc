#include<cmath>
#include<string>
#include<iostream>
#include<vector>
#include<functional>
#include"vector.h"


std::tuple<double, double, int> integrate(
    const std::function<double(double)>& f,
    double a, double b,
    double acc, 
    double eps,
    double f2=NAN, double f3=NAN,
    int n=1)
    {
        double h = b - a;

        if(std::isnan(f2)) {f2 = f(a+2*h/6), f3 = f(a+4*h/6);}

        double f1 = f(a+h/6);
        double f4 = f(a+5*h/6);

        double Q = (2*f1 + f2 + f3 + 2*f4) / 6 * h;
        double q = (  f1 + f2 + f3 + f4) / 4 * h;

        double err = std::abs(Q-q);
        if(err <= acc+eps*std::abs(Q)){
            return std::make_tuple(Q, err, n);
        }
        else {
            auto I1 = integrate(f, a, (a+b)/2, acc/std::sqrt(2), eps, f1, f2);
            auto I2 = integrate(f, (a+b)/2, b, acc/std::sqrt(2), eps, f3, f4);
            double I = std::get<0>(I1) + std::get<0>(I2);
            double Ierr = std::sqrt(std::pow(std::get<1>(I1),2) + std::pow(std::get<1>(I2),2));
            int In = n + std::get<2>(I1) + std::get<2>(I2);
            return std::make_tuple(I, Ierr, In);
        }
    }

std::tuple<double, double, int> integrate_CC(
    const std::function<double(double)>& f,
    double a, double b,
    double acc, 
    double eps)
    {
        // std::function<double(double)> f2;
        if(a == b){return std::make_tuple(0.0, 0.0, 0);}
        else if(std::isinf(a) && std::isinf(b)){
            std::function<double(double)> f2 = [=](double Θ) {
                return f(std::cos(Θ)/std::sin(Θ)/std::sin(Θ)) * (1 + std::cos(Θ)*std::cos(Θ))/std::pow(std::sin(Θ),3);
            };
            return integrate(f2, 0, M_PI, acc, eps);
        }
        else if(std::isinf(b)){
            std::function<double(double)> f2 = [=](double Θ) {
                return f(a + (1 + std::cos(Θ))/(1 - std::cos(Θ))) * 2*std::sin(Θ)/std::pow(1 - std::cos(Θ),2);
            };
            return integrate(f2, 0, M_PI, acc, eps);
        }
        else {
            std::function<double(double)> f2 = [=](double Θ) {
                return f((a+b)/2 + (b-a)/2*std::cos(Θ))*std::sin(Θ)*(b-a)/2;
            };
            return integrate(f2, 0, M_PI, acc, eps);
        }
    }
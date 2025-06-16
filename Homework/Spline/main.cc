#include<iostream>
#include<functional>
#include<tuple>
#include<cmath>
#include"spline.h"
#include"vector.h"

int main(int argc, char** argv) {
    std::string mode = "";
    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];
        if(arg == "-mode" && i+1<argc) mode = argv[i + 1];
    }

    int N = 20;
    vector xs(N), ys(N);
    for(int i = 0; i < N; ++i) {
        xs[i] = 10.0/N * i;
        ys[i] = std::cos(xs[i]);
        // std::cout << xs[i] << ", " << ys[i] << std::endl;
    }
    std::cout << "Linear spline:\n";
    std::cout << "Integral of linear spline of cos(x) from 0 to 2pi: " << linterpInteg(xs, ys, 3.1415296 * 2) << " expected approx: 0\n";
    std::cout << "Integral of linear spline of cos(x) from 0 to 0.5: " << linterpInteg(xs, ys, 0.5) << " expected exactly: " << 0.25*(1 + 1 + 0.5*(std::cos(1) - 1)) << " by explicit calcualtion\n"; //assuming there is no sample point between 0 and 0.5
    std::cout << "Integral of linear spline of cos(x) from 0 to 9: " << linterpInteg(xs, ys, 9) << "\n";
    std::cout << "\n\n" << std::endl;


    std::cout << "\nQuadratic spline:\n";
    vector ys1(N), ys2(N), ys3(N);
    for(int i = 0; i < N; ++i) {xs[i] = i; ys1[i] = 1; ys2[i] = i; ys3[i] = i*i;}
    qSpline inter1(xs, ys1);
    std::cout << "Coefficients for constant function f(x) = 1:\n";
    inter1.b.print("b = ");
    inter1.c.print("c = ");
    std::cout << "Expected b_i = 0, c_i = 0 for all i\n";
    
    qSpline inter2(xs, ys2);
    std::cout << "\nCoefficients for linear function f(x) = x:\n";
    inter2.b.print("b = ");
    inter2.c.print("c = ");
    std::cout << "Expected b_i = 1, c_i = 0 for all i\n";
    
    qSpline inter3(xs, ys3);
    std::cout << "\nCoefficients for quadratic function f(x) = x^2:\n";
    inter3.b.print("b = ");
    inter3.c.print("c = ");
    std::cout << "Expected b = [1,1,5,5,9,9,...] and c = [0,2,0,2,...]\n";


    if(mode != ""){
        //Target func
        for(int i = 0; i < 100; ++i) {
            double x = 10.0/100 * i;
            double y = std::cos(x);
            std::cout << x << ", " << y << std::endl;
        }
        std::cout << "\n\n" << std::endl;
        //Target func int
        for(int i = 0; i < 100; ++i) {
            double x = 10.0/100 * i;
            double y = std::sin(x);
            std::cout << x << ", " << y << std::endl;
        }
        std::cout << "\n\n" << std::endl;
    }
    
    if(mode == "lin"){
        for(int i = 0; i < N; ++i) {
            double x = xs[i];
            double y = linterpInteg(xs, ys, x);
            std::cout << x << ", " << y << std::endl;
        }
        std::cout << "\n\n" << std::endl;
    }
    
    if(mode == "quard"){
        //Quard spline
        qSpline qS(xs, ys);
        
        //Integral
        for(int i = 0; i < N; ++i) {
            double x = xs[i];
            double y = qS.integral(x);
            std::cout << x << ", " << y << std::endl;
        }
        std::cout << "\n\n" << std::endl;
        
        //Spline
        for(int i = 0; i < 100; ++i) {
            double x = 9.5/100 * i;
            double y = qS(x);
            std::cout << x << ", " << y << std::endl;
        }
        std::cout << "\n\n" << std::endl;

        //d/dx
        for(int i = 0; i < N; ++i) {
            double x = xs[i];
            double y = qS.deriv(x);
            std::cout << x << ", " << y << std::endl;
        }
        std::cout << "\n\n" << std::endl;
    }
    
    



    return 9;
}
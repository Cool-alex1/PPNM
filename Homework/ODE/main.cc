#include<iostream>
#include<functional>
#include<tuple>
#include<cmath>
#include"vector.h"
#include"runge.h"
#include"matrix.h"

std::function<vector(double, vector)> harm = [](double x, const vector& y) {
    /* y'' = -y */
    vector res(2);
    res[0] = y[1];
    res[1] = -y[0];
    return res;
};
std::function<vector(double, vector)> diffFunc = [](double x, const vector& y) {
    /* y'' = y' + x */
    vector res(2);
    res[0] = y[1];
    res[1] = y[1] + x;
    return res;
};

std::function<vector(double, vector)> scipy1 = [](double x, const vector& y) {
    /* theta''(t) = - b*theta'(t) - c*sin(theta(t)) */
    vector res(2);
    res[0] = y[1];
    res[1] = - 2*y[1] - 15*sin(y[0]);
    return res;
};


std::function<vector(double, vector)> plaOrbit(double ε){
    std::function<vector(double, vector)> f = [=](double φ, const vector& u) {
        /* u''(φ) + u(φ) = 1 + εu(φ)^2 */
        vector res(2);
        res[0] = u[1];
        res[1] = 1 + ε*u[0]*u[0] - u[0];
        return res;
    };
    return f;
}

int main(int argc, char** argv) {
    std::string mode = "";
    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];
        if(arg == "-mode" && i+1<argc) mode = argv[i + 1];
    }

    vector y0(2);
    double a, b;
    double acc, eps;
    vector xlist;
    std::vector<vector> ylists;


    std::cout << "Hereunder are the generated solutions for the six plots in order:\n" 
              << " - plot.harm.svg (A)\n"
              << " - plot.diffharm.svg (A)\n"
              << " - plot.scipy1.svg (A)\n"
              << " - plot.PO1.svg (B)\n"
              << " - plot.PO2.svg (B)\n"
              << " - plot.PO3.svg (B)\n";



    // y'' = -y
    y0[0] = 1.0; y0[1] = 0.0;
    a = 0.0, b = 5;
    acc = 0.001, eps = 0.001;
    auto res_d1 = rkdriver(harm, a, b, y0, 0.125, acc, eps);
    xlist = std::get<0>(res_d1);
    ylists = std::get<1>(res_d1);
    
    std::cout << "\n\n";
    for(int i = 0; i < xlist.len; ++i) std::cout << xlist[i] << ", " << ylists[i][0] << "\n";
    

    // y'' = y' + x
    y0[0] = 1.0; y0[1] = 1.0;
    a = 0.0, b = 5;
    acc = 0.001, eps = 0.001;
    auto res_d2 = rkdriver(diffFunc, a, b, y0, 0.125, acc, eps);
    xlist = std::get<0>(res_d2);
    ylists = std::get<1>(res_d2);
    
    std::cout << "\n\n";
    for(int i = 0; i < xlist.len; ++i) std::cout << xlist[i] << ", " << ylists[i][0] << "\n";
    



    //scipy 1
    y0[0] = 1.0; y0[1] = 0.0;
    a = 0.0, b = 10;
    acc = 0.001, eps = 0.001;
    auto res_s1 = rkdriver(scipy1, a, b, y0, 0.125, acc, eps);
    xlist = std::get<0>(res_s1);
    ylists = std::get<1>(res_s1);
    
    std::cout << "\n\n";
    for(int i = 0; i < xlist.len; ++i) std::cout << xlist[i] << ", " << ylists[i][0] << "\n";
    




    //Planetary orbit 1
    y0[0] = 1.0; y0[1] = 0.01;
    a = 0.0, b = 25;
    acc = 0.001, eps = 0.001;
    auto res_p1 = rkdriver(plaOrbit(0), a, b, y0, 0.125, acc, eps);
    xlist = std::get<0>(res_p1);
    ylists = std::get<1>(res_p1);
    
    std::cout << "\n\n";
    for(int i = 0; i < xlist.len; ++i) std::cout << xlist[i] << ", " << ylists[i][0] << "\n";
    
    
    //Planetary orbit 2
    y0[0] = 1.0; y0[1] = -0.5;
    a = 0.0, b = 25;
    acc = 0.001, eps = 0.001;
    auto res_p2 = rkdriver(plaOrbit(0), a, b, y0, 0.125, acc, eps);
    xlist = std::get<0>(res_p2);
    ylists = std::get<1>(res_p2);
    
    std::cout << "\n\n";
    for(int i = 0; i < xlist.len; ++i) std::cout << xlist[i] << ", " << ylists[i][0] << "\n";
    
    
    //Planetary orbit 3
    y0[0] = 1.0; y0[1] = -0.5;
    a = 0.0, b = 25;
    acc = 0.001, eps = 0.001;
    auto res_p3 = rkdriver(plaOrbit(0.1), a, b, y0, 0.125, acc, eps);
    xlist = std::get<0>(res_p3);
    ylists = std::get<1>(res_p3);
    
    std::cout << "\n\n";
    for(int i = 0; i < xlist.len; ++i) std::cout << xlist[i] << ", " << ylists[i][0] << "\n";
    
    

    
    
    return 0;
}
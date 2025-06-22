#include<cmath>
#include<string>
#include<iostream>
#include<vector>
#include<functional>
#include"vector.h"
#include"matrix.h"

std::tuple<vector, vector> rkstep12(
    std::function<vector(double, vector)> f, 
    double x, 
    vector y, 
    double h) {

    vector k0 = f(x, y);
    vector k1 = f(x+h/2, y+k0*h/2);
    vector yh = y + k1*h;
    vector δy = (k1-k0)*h;

    return std::make_tuple(yh, δy);
}


std::tuple<vector, std::vector<vector>> rkdriver(
    std::function<vector(double, vector)> f,
    double a, double b,
    vector yinit,
    double h0 = 0.125,
    double acc = 0.01, 
    double eps = 0.01)
    {
        double x = a;
        double h = h0;
        vector y = yinit;

        vector xlist(0); xlist.append(a);
        std::vector<vector> ylist; ylist.push_back(yinit);

        while(true){
            if(x >= b){return std::make_tuple(xlist, ylist);}
            if(x+h > b){h = b-x;}
            
            auto res = rkstep12(f, x, y, h);
            vector newy = std::get<0>(res); //New y-value
            vector erry = std::get<1>(res); //Error estimate
            
            double tol = (acc + eps*newy.norm()) * sqrt(h/(b-a));
            double err = erry.norm();
            
            if(err <= tol){
                x += h; y = newy;
                xlist.append(x);
                ylist.push_back(y);
            }
            if(err > 0){h *= std::min(pow(tol/err, 0.25)*0.95, 2.0);}
            else {h *= 2;}
        }
    }
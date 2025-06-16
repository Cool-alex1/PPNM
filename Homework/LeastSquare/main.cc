#include<iostream>
#include<vector>
#include<functional>
#include<tuple>
#include<cmath>
#include"lsFit.h"
#include"matrix.h"

int main() {
    // std::vector<double> t = {1,2,3,4,5,6,7,8,9,10},
    //                     y = {4,6,8,12,13,15,24,23,27,31},
    //                     dy= {2,1,2,3,4,5,3,2,1,2};
    
    // // eq. ax + b
    // std::vector<std::function<double(double)>> f = {
    //     [](double t) {return t;},
    //     [](double t) {return 1.0;}
    // };

    std::vector<double> t = {1,  2,  3, 4, 6, 9,   10,  13,  15},
                        y = {117,100,88,72,53,29.5,25.2,15.2,11.1},
                        dy= {6,5,4,4,4,3,3,2,2};
    
    // eq. ae^(-λt) -> ln(y)=ln(a)-λt
    std::vector<std::function<double(double)>> f = {
        [](double t) {return 1.0;},
        [](double t) {return -t;}
    };

    std::vector<double> lny(y.size()),
                        lndy(y.size());

    for(int i=0; i<(int)y.size(); i++){
        lny[i] = std::log(y[i]);
        lndy[i] = dy[i]/y[i];
    }

    auto res =  lsfit(f, t, lny, lndy);
    matrix par = std::get<0>(res);
    matrix cov = std::get<1>(res);

    std::cout << "Optimal parameters (a, lambda):\n";
    par.print("par = ");
    cov.print("cov = ");
    std::cout << "parameter errors: " << std::sqrt(cov(0,0)) << ", " << std::sqrt(cov(1,1)) << "\n\n";
    double half_life = std::log(2)/par(1,0);
    double half_life_err = std::log(2)/par(1,0)/par(1,0) * std::sqrt(cov(1,1));
    std::cout << "ThX has measured half life : " << half_life << " ± " << half_life_err << " days\n";
    std::cout << "224Ra has half life : 3.6319 days" << "\n";
    std::cout << "The experimental data is " << (half_life - 3.6319)/half_life_err << " standard deviations from the modern value\n";
    
    std::cout << "\n\n";
    for(int i = 0; i < (int)t.size() ; ++i) std::cout << t[i] << " " << y[i] << " " << dy[i] << "\n";
    
    
    return 10;
}
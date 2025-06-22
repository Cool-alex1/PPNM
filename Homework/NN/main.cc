#include<iostream>
#include<functional>
#include<tuple>
#include<cmath>
#include<fstream>
#include"nn.h"

std::function<double(double)> f_test = [](double x){return x*x;};
std::function<double(double)> f_GW = [](double x){return x*std::exp(-x*x);};
std::function<double(double)> f_cos = [](double x){return std::cos(x);};
std::function<double(double)> f_1 = [](double x){return std::cos(5*x-1)*std::exp(-x*x);};
// std::function<double(double)> f_1 = [](double x){return ;};
// std::function<double(vector)> f_himmel = [](vector x){return std::pow(x[0]*x[0] + x[1]-11, 2) + std::pow(x[0] + x[1]*x[1]-7, 2);};
// std::function<double(vector)> f_beale = [](vector x){return std::pow(1.5-x[0]+x[0]*x[1],2) + std::pow(2.25 - x[0] + x[0]*x[1]*x[1],2) + std::pow(2.625 - x[0] + x[0]*x[1]*x[1]*x[1],2);}; //Minimum at (4,-9)*





int main(int argc, char** argv) {
    // std::string infile = " ";
    // std::string out = " ";
    for(int i = 0; i < argc ; ++i) {
        std::string arg = argv[i];
        // if(arg == "--input" && i+1 < argc) infile = argv[i + 1];
        // if(arg == "--output" && i+1 < argc) out = argv[i + 1];
    }
    
    
    std::function<double(double)> f = f_1;


    // Make training data
    int points = 600;
    double xmax=1, xmin=-1;
    matrix data(0, 2);
    for(int i=0; i<points; i++){
        matrix temp(1, 2);
        temp(0,0) = (xmax - xmin)/(points-1)*i+xmin;
        temp(0,1) = f(temp(0,0));
        data = data.append(temp, 1);
    }
    vector xs, ys;
    xs = toVector(data.getCol(0));
    ys = toVector(data.getCol(1));
    
    // xs.print("xs = ");
    // (data.getCol(0)).print("x ");



    nn test(3);
    test.train_ana(xs, ys, 3);

    std::cout << test.eval(3) << std::endl;

    test.p.print("p = ");
    std::cout << test.eval(3) << std::endl;
    
    
    std::cout << "\n\n" << std::endl;
    for(int i=0; i<points; i++){std::cout << xs[i] << " " << ys[i] << std::endl;}
    std::cout << "\n\n" << std::endl;
    for(int i=0; i<points; i++){std::cout << xs[i] << " " << test.eval(xs[i]) << std::endl;}
    
    return 0;
}
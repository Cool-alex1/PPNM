#include<iostream>
#include<functional>
#include<tuple>
#include<cmath>
#include<fstream>
#include"nn.h"

std::function<double(double)> f_test = [](double x){return x*x;};
std::function<double(double)> f_GW = [](double x){return x*std::exp(-x*x);};
std::function<double(double)> f_cos = [](double x){return std::cos(x);};
std::function<double(double)> f_A = [](double x){return std::cos(5*x-1)*std::exp(-x*x);};
std::function<double(double)> f_q = [](double x){return x*5;};
// std::function<double(double)> f_q = [](double x){return x*x;};
// std::function<double(double)> f_q = [](double x){return x*x - x/3 - 0.5;};





int main(int argc, char** argv) {
    std::string opg = "";
    // std::string out = " ";
    for(int i = 0; i < argc ; ++i) {
        std::string arg = argv[i];
        if(arg == "--opg" && i+1 < argc) opg = argv[i + 1];
        // if(arg == "--output" && i+1 < argc) out = argv[i + 1];
    }
    

    
    
    if(opg == "Ap" || opg == ""){
        
        // Make training data
        int points = 1000;
        double xmax=1, xmin=-1;
        std::function<double(double)> f = f_A;
    
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
        
        
        
        std::cout << "A)" << std::endl;
        std::cout << "Gaussian wavelet:" << std::endl;
        int n = 8;
        std::cout << "Number of neurons : " << n << std::endl;
        nn nnGaussW(n, "gauss wave");
        nnGaussW.train_ana(xs, ys, 5);
        nnGaussW.p.print("Optimal p = ");
        
        
        
        std::cout << "\nWavelet:" << std::endl;
        std::cout << "Number of neurons : " << n << std::endl;
        nn nnWave(n, "wave");
        nnWave.train_ana(xs, ys, 5);
        nnWave.p.print("Optimal p = ");
        std::cout << "\n\n" << std::endl;
        
        if(opg == "Ap"){
            for(int i=0; i<points; i++){std::cout << xs[i] << " " << ys[i] << " " << nnGaussW.eval(xs[i]) << " " << nnWave.eval(xs[i]) << std::endl;}
        }
    }









    if(opg == "Bp" || opg == "B" || opg == ""){
        int points = 1000;
        double xmax=1, xmin=-1;
        std::function<double(double)> f = f_q;
    
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
 


        std::cout << "B)" << std::endl;
        std::cout << "Gaussian wavelet:" << std::endl;
        int n = 30;
        std::cout << "Number of neurons : " << n << std::endl;
        nn nnGaussW(n, "gauss wave");
        nnGaussW.train_ana(xs, ys, 5);
        nnGaussW.p.print("Optimal p = ");
        std::cout << "\nA approx fit can be seen on Plot.nnFitB.svg." <<
            "\nThe fit, the derivatives, and the anti-derivative" <<
            "\nlookes to be pretty accurate, whereas the double derivative" <<
            "\nseems to be around 0, but is oscillating." << std::endl;
        std::cout << "\n\n" << std::endl;

        if(opg == "Bp"){
            for(int i=0; i<points; i++){
                vector res = nnGaussW.evalB(xs[i]);
                std::cout << xs[i] << " " << ys[i] << " " << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << std::endl;}
        }
    }

    return 0;
}
#include<iostream>
#include<functional>
#include<tuple>
#include<cmath>
#include<fstream>
#include"mini.h"

std::function<double(vector)> f_rosen = [](vector x){return (1-x[0])*(1-x[0]) + 100*std::pow(x[1] - x[0]*x[0], 2);};
std::function<double(vector)> f_himmel = [](vector x){return std::pow(x[0]*x[0] + x[1]-11, 2) + std::pow(x[0] + x[1]*x[1]-7, 2);};
std::function<double(vector)> f_beale = [](vector x){return std::pow(1.5-x[0]+x[0]*x[1],2) + std::pow(2.25 - x[0] + x[0]*x[1]*x[1],2) + std::pow(2.625 - x[0] + x[0]*x[1]*x[1]*x[1],2);}; //Minimum at (4,-9)*


// std::function<double(vector)> f_BW(double E) {
//     std::function<double(vector)> f = [=](vector p) {
//         return p[2] / ((E-p[0])*(E-p[0]) + p[1]*p[1]/4);
//     };
//     return f;};

// std::function<double(vector)> df_BW(vector E, vector s, vector ds) {
//     std::function<double(vector)> f = [=](vector p) {
//         double val = 0;
//         for (int i=0; i<len(E); i++){
//             val += std::pow((f_BW(E[i])(p) - s[i]) / ds[i], 2);
//         }
//         return val;
//     };
//     return f;};





int main(int argc, char** argv) {
    std::string infile = " ";
    for(int i = 0; i < argc ; ++i) {
        std::string arg = argv[i];
        if(arg == "--input" && i+1 < argc) infile = argv[i + 1];
    }
    std::cout << "infile = " << infile << "\n";

    double Ei, si, dsi;
    vector E, s, ds;
    std::ifstream instream(infile);
    while(instream >> Ei >> si >> dsi) {
        // std::cout << Ei << std::endl;
        std::cout << s << std::endl;
        // std::cout << ds << std::endl;
        E.append(Ei);
        s.append(si);
        ds.append(dsi);
    }
    E.print("E =");
    // int n;



    // std::function<double(double,vector)> f_BW = [](double e, vector p){return p[2]/ (std::pow(e - p[0],2) + p[1]*p[1]/4);};
    // std::function<double(vector)> df_BW = [=](vector p){
    //     double d = 0;
    //     for(int i = 0; i < E.len ; ++i) d += std::pow((f_BW(E[i], p) - s[i]) / ds[i], 2);
    //     return d;
    // };


    // vector start(2);

    // std::cout << "Rosenbrock function:" << std::endl;
    // start[0] = 0;
    // start[1] = 0;
    // std::tuple<vector, int> newRosen = newton(f_rosen, start);
    // vector minRosen = std::get<0>(newRosen);
    // int n = std::get<1>(newRosen);
    // minRosen.print("min = ");
    // std::cout << "Expected min (1, 1)" << std::endl;
    // std::cout << "From (" << start[0] << ", " << start[1] << ") to min in " << n << " steps\n\n" << std::endl;
    // // std::cout << "\n\n" << std::endl;
    
    
    
    // std::cout << "Himmelblau's function:" << std::endl;
    // start[0] = 2;
    // start[1] = 4;
    // std::tuple<vector, int> newHimmel = newton(f_himmel, start);
    // vector minHimmel = std::get<0>(newHimmel);
    // n = std::get<1>(newHimmel);
    // minHimmel.print("min = ");
    // std::cout << "Expected min (3, 2)" << std::endl;
    // std::cout << "From (" << start[0] << ", " << start[1] << ") to min in " << n << " steps\n\n" << std::endl;
    // // std::cout << "\n\n" << std::endl;
    
    
    // std::cout << "Beale function:" << std::endl;
    // start[0] = 1;
    // start[1] = 0;
    // std::tuple<vector, int> newBeale = newton(f_beale, start);
    // vector minBeale = std::get<0>(newBeale);
    // n = std::get<1>(newBeale);
    // minBeale.print("min = ");
    // std::cout << "Expected min (3, 0.5)" << std::endl;
    // std::cout << "From (" << start[0] << ", " << start[1] << ") to min in " << n << " steps\n\n\n" << std::endl;
    
    

    // vector start2(3);
    
    // start2[0] = 2;
    // start2[1] = 1;
    // start2[2] = 1;
    // std::cout << "Breit-Wigner function: " << df_BW(start2)<< std::endl;
    // // std::tuple<vector, int> newBW = newton(df_BW(E, s, ds), start2);
    // std::tuple<vector, int> newBW = newton(df_BW, start2);
    // vector minBW = std::get<0>(newBW);
    // n = std::get<1>(newBW);
    // minBW.print("min = ");
    // std::cout << "Expected min (3, 0.5)" << std::endl;
    // std::cout << "From (" << start2[0] << ", " << start2[1] << ", " << start2[2] << ") to min in " << n << " steps\n\n" << std::endl;
    // std::cout << "\n\n" << std::endl;



    
    return 9;
}
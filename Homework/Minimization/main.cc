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
    std::string out = " ";
    for(int i = 0; i < argc ; ++i) {
        std::string arg = argv[i];
        if(arg == "--input" && i+1 < argc) infile = argv[i + 1];
        if(arg == "--output" && i+1 < argc) out = argv[i + 1];
    }
    
    
    int n;
    
    
    
    
    if(out == "0"){
        vector start(2);
        
        std::cout << "A) and C)" << std::endl;
        std::cout << "Rosenbrock function:" << std::endl;
        start[0] = 0;
        start[1] = 0;
        std::tuple<vector, int> newRosen = newton(f_rosen, start);
        vector minRosen = std::get<0>(newRosen);
        n = std::get<1>(newRosen);
        minRosen.print("min = ");
        std::cout << "Expected min (1, 1)" << std::endl;
        std::cout << "With forward diff: From (" << start[0] << ", " << start[1] << ") to min in " << n << " steps" << std::endl;
        
        newRosen = newton2(f_rosen, start);
        n = std::get<1>(newRosen);
        std::cout << "With central diff: From (" << start[0] << ", " << start[1] << ") to min in " << n << " steps\n\n" << std::endl;
        // std::cout << "\n\n" << std::endl;
        



        std::cout << "Himmelblau's function:" << std::endl;
        start[0] = 2;
        start[1] = 4;
        std::tuple<vector, int> newHimmel = newton(f_himmel, start);
        vector minHimmel = std::get<0>(newHimmel);
        n = std::get<1>(newHimmel);
        minHimmel.print("min = ");
        std::cout << "Expected min (3, 2)" << std::endl;
        std::cout << "With forward diff: From (" << start[0] << ", " << start[1] << ") to min in " << n << " steps" << std::endl;
        
        newHimmel = newton2(f_himmel, start);
        n = std::get<1>(newHimmel);
        std::cout << "With central diff: From (" << start[0] << ", " << start[1] << ") to min in " << n << " steps\n\n" << std::endl;
        // std::cout << "\n\n" << std::endl;




        std::cout << "Beale function:" << std::endl;
        start[0] = 1;
        start[1] = 0;
        std::tuple<vector, int> newBeale = newton(f_beale, start);
        vector minBeale = std::get<0>(newBeale);
        n = std::get<1>(newBeale);
        minBeale.print("min = ");
        std::cout << "Expected min (3, 0.5)" << std::endl;
        std::cout << "With forward diff: From (" << start[0] << ", " << start[1] << ") to min in " << n << " steps" << std::endl;
        
        newBeale = newton2(f_beale, start);
        n = std::get<1>(newBeale);
        std::cout << "With central diff: From (" << start[0] << ", " << start[1] << ") to min in " << n << " steps\n\n\n" << std::endl;
        
        
    }
    
    
    
    if(infile != " ") {
        if(out == "0"){
            std::cout << "B) and C)" << std::endl;
            std::cout << "Breit-Wigner function: " << std::endl;
            std::cout << "infile = " << infile << "\n";
        }
        
        double Ei, si, dsi;
        matrix EM(1,1);
        matrix sM(1,1);
        matrix dsM(1,1);
        std::ifstream instream(infile);
        while(instream >> Ei >> si >> dsi) {
            matrix please(1,1);
            please(0,0) = Ei;
            if(EM(0,0) == 0) {EM(0,0) = Ei;}
            else {EM = EM.append(please);}
            
            please(0,0) = si;
            if(sM(0,0) == 0) {sM(0,0) = si;}
            else {sM = sM.append(please);}
            
            please(0,0) = dsi;
            if(dsM(0,0) == 0) {dsM(0,0) = dsi;}
            else {dsM = dsM.append(please);}
        }
        vector E = toVector(EM);
        vector s = toVector(sM);
        vector ds = toVector(dsM);
        
        // E.print("E = ");
        // s.print("s = ");
        // ds.print("ds = ");
        
        
        
        std::function<double(double,vector)> f_BW = [](double e, vector p){return p[2] / (std::pow(e - p[0],2) + p[1]*p[1]/4);};
        std::function<double(vector)> df_BW = [=](vector p){
            double d = 0;
            for(int i = 0; i < E.len ; ++i) d += std::pow((f_BW(E[i], p) - s[i]) / ds[i], 2);
            return d;
        };
        
        
        vector start2(3);
        
        // start2 = {125, 4, 15};
        start2[0] = 125;
        start2[1] = 4;
        start2[2] = 15;
        // std::tuple<vector, int> newBW = newton(df_BW(E, s, ds), start2);
        std::tuple<vector, int> newBW = newton(df_BW, start2);
        vector minBW = std::get<0>(newBW);
        n = std::get<1>(newBW);
        if(out == "0"){
            minBW.print("min = ");
            std::cout << "With forward diff: From (" << start2[0] << ", " << start2[1] << ", " << start2[2] << ") to min in " << n << " steps" << std::endl;
            
            std::tuple<vector, int> newBW = newton2(df_BW, start2);
            n = std::get<1>(newBW);
            std::cout << "With central diff: From (" << start2[0] << ", " << start2[1] << ", " << start2[2] << ") to min in " << n << " steps\n\n" << std::endl;
        }
        
        if(out == "higgs"){
            int n = 5000;
            double dx = (E[-1] - E[0])/n;
            double e = E[0];
            for(int i = 0; i < n ; ++i) {
                std::cout << e << " " << f_BW(e, minBW) << std::endl;
                e += dx;
            }
        }
    }
    
    
    
    
    return 0;
}
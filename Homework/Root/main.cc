#include<iostream>
#include<functional>
#include<tuple>
#include<cmath>
#include<fstream>
#include"root.h"
#include"runge.h"





std::function<vector(vector)> f_lin = [](vector x){return x-1;}; //root at x = 0
std::function<vector(vector)> f_lin2 = [](vector x){return x*6-2;}; //root at x = 0
std::function<vector(vector)> f_q = [](vector x){return vector({x[0]*x[0], x[1]*x[1]});}; //root at x = 0
std::function<vector(vector)> f_sphere = [](vector x){
    double val = x.norm();
    return vector({val,val});
}; //root at x = 0 (all elements)
std::function<vector(vector)> f_rosen = [](vector x){
    double gx = 2 * (x[0]-1) - 400 * (x[1] - x[0]*x[0]) * x[0];
    double gy = 200 * (x[1] - x[0]*x[0]);
    return vector({gx, gy});
};
std::function<vector(vector)> f_himmel = [](vector x){
    double gx = 4 * (x[0]*x[0]+x[1]-11)*x[0] + 2*(x[0]+x[1]*x[1]-7);
    double gy = 2 * (x[0]*x[0]+x[1]-11) + 4*(x[0]+x[1]*x[1]-7)*x[1];
    return vector({gx, gy});
};




int main(int argc, char** argv) {
    std::string mode = "";
    // std::string out = " ";
    for(int i = 0; i < argc ; ++i) {
        std::string arg = argv[i];
        if(arg == "--mode" && i+1 < argc) mode = argv[i + 1];
        // if(arg == "--output" && i+1 < argc) out = argv[i + 1];
    }
    
    
    // std::cout << "So it begins" << std::endl;
    
    
    vector a, res;
    
    if(mode == ""){
        std::cout << "A)" << std::endl;
        std::cout << "f(x)=x*6-2:" << std::endl;
        a = vector({5});
        res = newton(f_lin2, a, 0.001);
        std::cout << "Start: [" << a[0] << "]" << std::endl;
        std::cout << "Expected root: [" << 1.0/3.0 << "]" << std::endl;
        res.print("res = ");
        
        std::cout << "\n\nf(x)=x-1 (2D):" << std::endl;
        a = vector({0.5, 0.5});
        res = newton(f_lin, a, 0.000001);
        std::cout << "Start: [" << a[0] << ", " << a[1] << "]" << std::endl;
        std::cout << "Expected root: [" << 1 << ", " << 1 << "]" << std::endl;
        res.print("res = ");
        
        std::cout << "\n\nf(x) = x^2 + y^2:" << std::endl;
        a = vector({1, 1});
        res = newton(f_q, a, 0.000001);
        std::cout << "Start: [" << a[0] << ", " << a[1] << "]" << std::endl;
        std::cout << "Expected min: [" << 0 << ", " << 0 << "]" << std::endl;
        res.print("res = ");
        

        std::cout << "\n\nRosenbrock function:" << std::endl;
        a = vector({2.5, 2.5});
        res = newton(f_rosen, a, 0.0001);
        std::cout << "Start: [" << a[0] << ", " << a[1] << "]" << std::endl;
        std::cout << "Expected min: [" << 1 << ", " << 1 << "]" << std::endl;
        res.print("res = ");
        
        std::cout << "\n\nHimmelblau's function:" << std::endl;
        a = vector({4.0, 4.0});
        res = newton(f_himmel, a, 0.0001);
        std::cout << "Start: [" << a[0] << ", " << a[1] << "] and [" << -a[0] << ", " << a[1] << "] and [" << a[0] << ", " << -a[1] << "] and [" << -a[0] << ", " << -a[1] << "]"  << std::endl;
        std::cout << "Expected min: [" << 3 << ", " << 2 << "]" << std::endl;
        std::cout << "Expected min: [" << -2.80512 << ", " << 3.13131 << "]" << std::endl;
        std::cout << "Expected min: [" << 3.58443 << ", " << -1.84813 << "]" << std::endl;
        std::cout << "Expected min: [" << -3.77931 << ", " << -3.28329 << "]" << std::endl;
        newton(f_himmel, vector({4, 4}), 0.0001).print("res1 = ");
        newton(f_himmel, vector({-4, 4}), 0.0001).print("res2 = ");
        newton(f_himmel, vector({4, -4}), 0.0001).print("res3 = ");
        newton(f_himmel, vector({-4, -4}), 0.0001).print("res4 = ");
        
        
        
        
        
        
        
    }

    // B
    double rmax = 8.0, rmin = 0.1, acc=1e-3, eps=1e-3;
    double E0 = -5;
    vector yrmin({rmin * (1 - rmin), 1 - 2*rmin});

    std::function<vector(vector)> Me = [&](vector E) {
        std::function<vector(double, vector)> f_s = [&](double x, vector y) {
            return vector({y[1], -2*(E[0] + 1.0/x)*y[0]});
        };
    
        auto sol = rkdriver(f_s, rmin, rmax, yrmin, 0.125, acc, eps);
        std::vector<vector> ys = std::get<1>(sol);
        return vector({ys[ys.size()-1][0]});
    };


    if(mode == ""){
        std::cout << "\n\n\nB)" << std::endl;

        
        
        std::cout << "Schroedinger equation:" << std::endl;
        std::cout << "Using\nr_min = " << rmin << "\nr_max = " << rmax << "\n";
        std::cout << "Using acc = " << acc << "\neps = " << eps << "\n";
        res = newton(Me, vector({E0}), acc);
        std::cout << "\nOptimal energy: " << res[0] << std::endl;
    }
    
    


    double E_opt;
    vector rs;
    std::vector<vector> fx;
    
    if(mode == "p1"){
        rmin = 0.001;
        yrmin = vector({rmin * (1 - rmin), 1 - 2*rmin});
        vector rmaxs({1, 2, 4, 8, 16});
        
        for(int i=0; i<rmaxs.len; i++){
            rmax = rmaxs[i];
            E_opt = newton(Me, vector({E0}), acc)[0];
            
            std::function<vector(double, vector)> f_s = [=](double x, vector y) {
                return vector({y[1], -2*(E_opt + 1.0/x)*y[0]});
            };
            
            
            auto sol = rkdriver(f_s, rmin, rmax, yrmin, 0.125, acc, eps);
            rs = std::get<0>(sol);
            fx = std::get<1>(sol);
            for(int j=0; j<rs.len; j++) std::cout << rs[j] << " "  << fx[j][0] << std::endl;
            std::cout << "\n\n" << std::endl;
        }
    }
    
    if(mode == "p2"){
        std::cout << "\n\n" << std::endl;
        rmax = 8;
        vector rmins({0.001, 0.01, 0.1, 0.25, 0.5});
        
        for(int i=0; i<rmins.len; i++){
            rmin = rmins[i];
            yrmin = vector({rmin * (1 - rmin), 1 - 2*rmin});
            E_opt = newton(Me, vector({E0}), acc)[0];
            
            std::function<vector(double, vector)> f_s = [=](double x, vector y) {
                return vector({y[1], -2*(E_opt + 1.0/x)*y[0]});
            };
            
            
            auto sol = rkdriver(f_s, rmin, rmax, yrmin, 0.125, acc, eps);
            rs = std::get<0>(sol);
            fx = std::get<1>(sol);
            for(int j=0; j<rs.len; j++) std::cout << rs[j] << " "  << fx[j][0] << std::endl;
            std::cout << "\n\n" << std::endl;
        }
    }
    
    

    
    if(mode == "p3"){
        std::cout << "\n\n" << std::endl;
        rmin = 0.0001;
        yrmin = vector({rmin * (1 - rmin), 1 - 2*rmin});
        vector accs({1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1});
        
        for(int i=0; i<accs.len; i++){
            acc = accs[i];
            E_opt = newton(Me, vector({E0}), acc)[0];
            
            std::function<vector(double, vector)> f_s = [=](double x, vector y) {
                return vector({y[1], -2*(E_opt + 1.0/x)*y[0]});
            };
            
            
            auto sol = rkdriver(f_s, rmin, rmax, yrmin, 0.125, acc, eps);
            rs = std::get<0>(sol);
            fx = std::get<1>(sol);
            for(int j=0; j<rs.len; j++) std::cout << rs[j] << " "  << fx[j][0] << std::endl;
            std::cout << "\n\n" << std::endl;
        }
    }



    if(mode == "p4"){
        acc = 0.001;
        yrmin = vector({rmin * (1 - rmin), 1 - 2*rmin});
        vector epss({1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1});
        
        for(int i=0; i<epss.len; i++){
            eps = epss[i];
            E_opt = newton(Me, vector({E0}), acc)[0];
            
            std::function<vector(double, vector)> f_s = [=](double x, vector y) {
                return vector({y[1], -2*(E_opt + 1.0/x)*y[0]});
            };
            
            
            auto sol = rkdriver(f_s, rmin, rmax, yrmin, 0.125, acc, eps);
            rs = std::get<0>(sol);
            fx = std::get<1>(sol);
            for(int j=0; j<rs.len; j++) std::cout << rs[j] << " " << fx[j][0] << std::endl;
            std::cout << "\n\n" << std::endl;
        }
    }


    
    
    
    
    
    return 0;
}
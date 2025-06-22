#include<cmath>
#include<string>
#include<iostream>
#include"nn.h"
#include"mini.h"
#define SELF (*this)


double nn::eval(double x){
    double s=0;
    double a, b, w;
    for(int i=0; i<n; i++){
        a = p(0,i);
        b = p(1,i);
        w = p(2,i);
        s += f_neuron(x, a, b, w);
    }
    return s;
}



void nn::train(const vector& xs, const vector& ys){

    std::function<double(vector)> cost_func = [&](vector p_flat){
        double c = 0;
        for(int i = 0; i<xs.len ; ++i){
            double s = 0;
            for(int j=0; j<n; j++){ s += f_neuron(xs[i], p_flat[j], p_flat[j + n], p_flat[j + n*2]);};
            c += std::pow(s - ys[i], 2);
        };
        // std::cout << "\n" << std::endl;
        return c;
    };
    // vector v1(3);
    // v1[0] = 0;
    // v1[1] = 0;
    // v1[2] = 1;

    // vector v2(3);
    // v2[0] = 0;
    // v2[1] = 10;
    // v2[2] = 1;
    // std::cout << cost_func(v1) << ", " << cost_func(v2) << std::endl;
    // std::cout << f_neuron(0, 0, 1, 1) << ", " << f_neuron(0, 1, 1, 1) << std::endl;


    std::tuple<vector, int> minimized = newton(cost_func, toVector(p.reshape(1, 3*n)));
    std::cout << "n = " << std::get<1>(minimized) << std::endl;

    p = toMatrix(std::get<0>(minimized)).reshape(3, n);
}

void nn::train_ana(const vector& xs, const vector& ys, const int& epoch){
    std::function<double(vector)> cost_func = [&](vector p_flat){
        double c = 0;
        for(int i = 0; i<xs.len ; ++i){
            double s = 0;
            for(int j=0; j<n; j++){ s += f_neuron(xs[i], p_flat[j], p_flat[j + n], p_flat[j + n*2]);};
            c += std::pow(s - ys[i], 2);
        };
        return c;
    };
    // std::function<double(vector,vector,int)> dC_daj = [&](vector p_flat, vector ak, int j){
    //     double c = 0;
    //     for(int k = 0; k<xs.len ; ++k){
    //         c += ak[k] * acc_df((xs[k]-p_flat[j])/p_flat[j+n]) / (-p_flat[j+n]);
    //     };
    //     return c * 2 * p_flat[j+2*n];
    // };
    // std::function<double(vector,vector,int)> dC_dbj = [&](vector p_flat, vector ak, int j){
    //     double c = 0;
    //     for(int k = 0; k<xs.len ; ++k){
    //         c += ak[k] * acc_df((xs[k]-p_flat[j])/p_flat[j+n]) * (-(xs[k]-p_flat[j])/std::pow(p_flat[j+n],2));
    //     };
    //     return c * 2 * p_flat[j+2*n];
    // };
    // std::function<double(vector,vector,int)> dC_dwj = [&](vector p_flat, vector ak, int j){
    //     double c = 0;
    //     for(int k = 0; k<xs.len ; ++k){
    //         c += ak[k] * acc_f((xs[k]-p_flat[j])/p_flat[j+n]);
    //     };
    //     return c * 2;
    // };
    
    // std::function<double(double,double,vector)> ak = [&](double x, double y, vector p_flat){
    //     double a = 0;
    //     for(int i=0; i<n ; ++i){
    //         a += acc_f((x-p_flat[i])/p_flat[i+n])*p_flat[i+n*2];
    //     };
    //     return a - y;};
    // std::function<double(double, double, vector)> dC_daj = [&](double x, double y, vector p_s){return -2 * ak(x,y) * p_s[2]/p_s[1] * acc_df((x - p_s[0])/p_s[1]);};
    // std::function<double(double, double, vector)> dC_dbj = [&](double x, double y, vector p_s){return -2 * ak(x,y) * p_s[2]/p_s[1]/p_s[1] * acc_df((x - p_s[0])/p_s[1]) * (x - p_s[0]);};
    // std::function<double(double, double, vector)> dC_dwj = [&](double x, double y, vector p_s){return 2 * ak(x,y) * acc_f((x - p_s[0])/p_s[1]);};

    double lr = 0.01;
    int N = 0;
    vector p_vec = toVector(p.reshape(1, 3*n));
    vector p_im = vector(n*3)+1;
    vector g(n*3);
    vector ak_v(xs.len);
 
    vector best_p(n*3);
    double best_cost = 10000000;
    double cost = 0;
    
    
    std::uniform_real_distribution<double> unif(-1,1);
    std::default_random_engine re(0);
    
    for (int e=0; e<epoch; e++){
        for(int j = 0; j < n ; ++j){
            p_vec[j] = unif(re)*2;
            p_vec[j + n] = unif(re)*2;
            p_vec[j + n*2] = unif(re)*2;
        }
        
        
        // while(1e-9 < std::abs(cost_func(p_im) - cost_func(p_vec)) && N<200000){
        while(N < 10000){
            if(N != 0) p_vec = p_im.copy();
            
            for (int k=0; k<xs.len; k++){
                double a = 0;
                for(int j=0; j<n ; ++j){
                    a += acc_f((xs[k]-p_vec[j])/p_vec[j+n])*p_vec[j+n*2];
                };
                ak_v[k] = a - ys[k];
            }
                
            // ak_v.print("ak = ");
            
            for (int j=0; j<n; j++){
                vector p_small({p_vec[j], p_vec[j+n], p_vec[j+n*2]});
                
                for (int k=0; k<xs.len; k++){
                    g[j] += dC_daj(xs[k], ak_v[k], p_small);
                    g[j + n] += dC_dbj(xs[k], ak_v[k], p_small);
                    g[j + 2*n] += dC_dwj(xs[k], ak_v[k], p_small);
                }
            }
            g /= g.norm();
                    
                    
            // toMatrix(g).reshape(3, n).T().print("g = ");

            p_im = p_vec - lr*g;
            

            cost = cost_func(p_im);
            if(cost < best_cost){
                best_cost = cost;
                best_p = p_im.copy();
            }

            
            N += 1;
            // if(N % 10000 == 0) std::cout << cost_func(p_im) << std::endl;
        }
        if(e % 1000 == 0) std::cout << "epoch = " << e << std::endl;
    }
    // std::cout << "n = " << N << std::endl;

    p = toMatrix(best_p).reshape(3, n);
}
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
        a = p(0,i); b = p(1,i); w = p(2,i);
        s += f_neuron(x, a, b, w);
    }
    return s;
}

vector nn::evalB(double x){
    //It has only been implimentet for the gaussian wavelet
    vector res(4);
    res[0] = eval(x);
    double a, b, w, u, e;
    for(int j=0; j<n; j++){
        a = p(0,j); b = p(1,j); w = p(2,j);
        u = (x-a)/b;
        e = std::exp(-u*u);
        res[1] += w/b * (1-2*u*u)*e;
        res[2] += w/b/b *2*u * (2*u*u-3)*e;
        res[3] += -w*b/2 * (e - std::exp(-a*a/b/b));
    }
    return res;
}



void nn::train_num(const vector& xs, const vector& ys){

    std::function<double(vector)> cost_func = [&](vector p_flat){
        double c = 0;
        for(int i = 0; i<xs.len ; ++i){
            double s = 0;
            for(int j=0; j<n; j++){ s += f_neuron(xs[i], p_flat[j], p_flat[j + n], p_flat[j + n*2]);};
            c += std::pow(s - ys[i], 2);
        };
        return c;
    };


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

    double lr = 1.0/128;
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
        // toMatrix(p_vec).reshape(3, n).T().print("p0 = ");
        
        
        // while(1e-9 < std::abs(cost_func(p_im) - cost_func(p_vec)) && N<200000){
        while(1e-9 < std::abs(cost_func(p_im) - cost_func(p_vec)) && N < 1000){
            if(N != 0) p_vec = p_im.copy();
            g = vector(3*n);
            
            /*Calculating useful values*/
            for (int k=0; k<xs.len; k++){
                double a = 0;
                for(int j=0; j<n ; ++j){a += acc_f((xs[k]-p_vec[j])/p_vec[j+n])*p_vec[j+n*2];};
                ak_v[k] = a - ys[k];
            }
            

            for (int j=0; j<n; j++){
                vector p_small({p_vec[j], p_vec[j+n], p_vec[j+n*2]});
                
                for (int k=0; k<xs.len; k++){
                    g[j] += dC_daj(xs[k], ak_v[k], p_small);
                    g[j + n] += dC_dbj(xs[k], ak_v[k], p_small);
                    g[j + 2*n] += dC_dwj(xs[k], ak_v[k], p_small);
                }
            }
            g /= g.norm();

            p_im = p_vec - lr*g;

            cost = cost_func(p_im);
            if(cost < best_cost){
                best_cost = cost;
                best_p = p_im.copy();
            }

            
            N += 1;
            // if(N % 10000 == 0) std::cout << cost_func(p_im) << std::endl;
        }
        // if(e % 1000 == 0) std::cout << "epoch = " << e << std::endl;
        // toMatrix(best_p).reshape(3, n).T().print("best_p = ");
    }
    // std::cout << "n = " << N << std::endl;

    std::cout << "Lowest found cost: " << best_cost << std::endl;

    p = toMatrix(best_p).reshape(3, n);
}
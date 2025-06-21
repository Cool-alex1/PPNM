#include<cmath>
#include<string>
#include<iostream>
#include"AI.h"
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
        for(int i = 0; i<n ; ++i){
            int s = 0;
            for(int j=0; j<n; j++){ s += f_neuron(xs[j], p_flat[j*3], p_flat[j*3+1], p_flat[j*3+2]);};
            c += std::pow(s - ys[i], 2);
        };
        return c;
    };

    std::tuple<vector, int> minimized = newton(cost_func, toVector(p.reshape(1, 3*n)));
    vector p_trained = std::get<0>(minimized);
    p_trained.print("p_trained = ");
    std::cout << "n = " << std::get<1>(minimized) << std::endl;

    p = toMatrix(std::get<0>(minimized)).reshape(3, n);
}
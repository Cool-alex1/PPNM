#ifndef HAVE_NN_H
#define HAVE_NN_H
#include<iostream>
#include<functional>
#include<string>
#include<random>
#include"matrix.h"

class nn{
    public: 
        int n;
        // std::function<double(double)> acc_f = [](double x){return std::exp(-x*x);}; //Activation function used in hidden neurons
        std::function<double(double)> acc_f = [](double x){return x*std::exp(-x*x);}; //Activation function used in hidden neurons
        std::function<double(double)> acc_df = [](double x){return std::exp(-x*x)*(1 - 2*x*x);}; //Activation function used in hidden neurons
        std::function<double(double,double,double,double)> f_neuron = [&](double x, double a, double b, double w) {return acc_f((x - a)/b)*w;}; //neuron activation function
        std::function<double(double,double)> ak;
        std::function<double(double,double,vector)> dC_daj, dC_dbj, dC_dwj; //Derivatives of loss functio
        matrix p;

	nn(const int& nNeurons): n(nNeurons) {
        p = matrix(3, nNeurons);
        std::uniform_real_distribution<double> unif(0,1);
        std::default_random_engine re;
        for(int j = 0; j < nNeurons ; ++j){for(int i = 0; i < 3; ++i) {p(i,j) = unif(re)*2;}}

        // p(0,0) = -0.56322;
        // p(1,0) = 0.422293;
        // p(2,0) = -1.50649;
        // p(0,1) = -0.26047;
        // p(1,1) = 0.483302;
        // p(2,1) = 1.35875;
        // p(0,2) = 0.464469;
        // p(1,2) = 0.363566;
        // p(2,2) = -1.28471;

        // ak = [&](double x, double y){
        //     double a = 0;
        //     for(int i=0; i<n ; ++i){
        //         a += acc_f((x-p(0,i))/p(1,i))*p(2,i);
        //     };
        //     return a - y;};
        dC_daj = [&](double x, double ak, vector p_s){return -2 * ak * p_s[2]/p_s[1] * acc_df((x - p_s[0])/p_s[1]);};
        dC_dbj = [&](double x, double ak, vector p_s){return -2 * ak * p_s[2]/p_s[1]/p_s[1] * acc_df((x - p_s[0])/p_s[1]) * (x - p_s[0]);};
        dC_dwj = [&](double x, double ak, vector p_s){return 2 * ak * acc_f((x - p_s[0])/p_s[1]);};

    }

	nn()=default;
	nn(const nn&)=default;
	nn(nn&&)=default;
	~nn()=default;

	nn& operator=(const nn&)=default;
	nn& operator=(nn&&)=default;


	double eval(double);
	void train(const vector& xs, const vector& ys);
	void train_ana(const vector& xs, const vector& ys, const int& epoch);
};

#endif
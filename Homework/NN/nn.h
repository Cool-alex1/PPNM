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
        matrix p;

	nn(const int& nNeurons): n(nNeurons) {
        p = matrix(3, nNeurons);
        std::uniform_real_distribution<double> unif(0,1);
        std::default_random_engine re;
        for(int j = 0; j < nNeurons ; ++j){
            // p(0,j) = 0;
            // p(1,j) = 10;
            // p(2,j) = 2;
            for(int i = 0; i < 3; ++i) {p(i,j) = unif(re)*2;}
        }
        // p(0,0) = -0.7;
        // p(1,0) = 0.5;
        // p(2,0) = -1;
        // p(0,1) = -0.2;
        // p(1,1) = 0.5;
        // p(2,1) = 1.5;
        // p(0,2) = 0.5;
        // p(1,2) = 0.5;
        // p(2,2) = -0.7;

        // p(0,0) = -0.56322;
        // p(1,0) = 0.422293;
        // p(2,0) = -1.50649;
        // p(0,1) = -0.26047;
        // p(1,1) = 0.483302;
        // p(2,1) = 1.35875;
        // p(0,2) = 0.464469;
        // p(1,2) = 0.363566;
        // p(2,2) = -1.28471;
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
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
        std::function<double(double)> acc_f = [](double x){return x*std::exp(-x*x);}; //Activation function used in hidden neurons
        std::function<double(double,double,double,double)> f_neuron = [&](double x, double a, double b, double w) {return acc_f((x - a)/b)*w;}; //neuron activation function
        matrix p;

	nn(const int& nNeurons): n(nNeurons) {
        p = matrix(3, nNeurons);
        std::uniform_real_distribution<double> unif(0,1);
        std::default_random_engine re;
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < nNeurons ; ++j) p(i,j) = unif(re);
        }
    }

	nn()=default;
	nn(const nn&)=default;
	nn(nn&&)=default;
	~nn()=default;

	nn& operator=(const nn&)=default;
	nn& operator=(nn&&)=default;


	double eval(double);
	void train(const vector& xs, const vector& ys);
};

#endif
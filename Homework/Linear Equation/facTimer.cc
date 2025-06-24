
#include"matrix.h"
#include"QR.h"
#include<iostream>
#include<string>
#include<assert.h>
#include<random>

int main(int argc, char** argv) {
    int n = 3;

    std::uniform_real_distribution<double> unif(0,1);
    std::default_random_engine re;

    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];
        if(arg == "-n" && i+1<argc) n = std::stoi(argv[i + 1]);
    }

    matrix A(n,n);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n ; ++j) A(i,j) = unif(re);
    }
    QR fac(A);
    fac.decomp();

    return 0;
}

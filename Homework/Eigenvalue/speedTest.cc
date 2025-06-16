#include<iostream>
#include<iomanip>
#include<cmath>
#include<random>
#include<vector>
#include"matrix.h"
#include"eigenD.h"

int main(int argc, char** argv) {
    int n = 0;

    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];
        if(arg == "-n" && i+1<argc) n = std::stod(argv[i + 1]);
    }

    matrix a(n,n);
    std::uniform_real_distribution<double> unif(0,1);
    std::default_random_engine re;

    for(int i = 0; i < n; ++i) for(int j = 0; j < i + 1 ; ++j) {
        double val = unif(re);
        a(i,j) = val; 
        a(j,i) = val;
    }
    
    EigenD E(a);
    E.cyclic();

    return 0;
}

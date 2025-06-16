#include<iostream>
#include<iomanip>
#include<cmath>
#include<random>
#include"matrix.h"
#include"eigenD.h"


int main(){
    int n = 4;
    matrix a(n,n);
    std::uniform_real_distribution<double> unif(0,1);
    std::default_random_engine re;

    std::cout << "A matrix with shape (" << n << "x" << n << ") with numers within [0,1]:" << std::endl;
    for(int i = 0; i < n; ++i) for(int j = 0; j < i + 1 ; ++j) {
        double val = unif(re);
        a(i,j) = val; 
        a(j,i) = val;
    }
    a.print("A = ");
    
    EigenD E(a);
    E.cyclic();
    
    std::cout << "\n\nThe decomposed D and V matrix:" << std::endl;
    E.D.print("D = ");
    std::cout << std::endl;
    E.V.print("V = ");


    std::cout << "\n\nTests for D and V:" << std::endl;
    std::cout << "VV^T = I: " << approx(E.V*E.V.T(), I(n)) << std::endl;
    std::cout << "V^TV = I: " << approx(E.V.T()*E.V, I(n)) << std::endl;
    std::cout << "VDV^T = A: " << approx(E.V * E.D * E.V.T(), a) << std::endl;
    std::cout << "V^TAV = D: " << approx(E.V.T() * a * E.V, E.D) << std::endl;    
    return 10;
}
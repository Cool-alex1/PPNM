#include"matrix.h"
#include"QR.h"
#include<iostream>
#include<string>
#include<assert.h>
#include<random>

int main(int argc, char** argv) {
    int n = 3,
        m = 2;

    std::uniform_real_distribution<double> unif(0,1);
    std::default_random_engine re;

    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];

        if(arg == "-n" && i+1<argc) n = std::stoi(argv[i + 1]);
        if(arg == "-m" && i+1<argc) m = std::stoi(argv[i + 1]);
    }
    
    std::cout << "matrix of shape (" << n << ", " << m << ") with uniform random values [0,1]:\n";
    matrix A(n,m);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m ; ++j) A(i,j) = unif(re);
    }
    A.print("A = ");
    std::cout << std::endl;
    
    QR fac(A);

    std::cout << "QR factorization of A:\n";
    fac.decomp();
    fac.Q.print("Q = ");
    fac.R.print("R = ");
    std::cout << std::endl;
    
    matrix Q2 = fac.Q.T() * fac.Q;
    std::cout << "Check if Q^TQ = I:\n";
    // Q2.print("Q^TQ = ");
    // matrix I = I(m);
    std::cout << "Q^TQ ?= I : " << approx(Q2, I(m)) << "\n";
    std::cout << "QR ?= A : " << approx(fac.Q*fac.R, A) << "\n";
    std::cout << std::endl;
    std::cout << std::endl;
    
    n = 4;
    matrix A2(n, n);
    matrix b(n, 1);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n ; ++j) A2(i,j) = unif(re);
        b(i, 0) = unif(re);
    }
    A2.print("A = ");
    b.print("b = ");
    
    QR fac2(A2);
    fac2.decomp();
    
    matrix x = fac2.solve(b);
    std::cout << "Solution to system of linear equations Ax = b is:\n";
    x.print("x = ");
    
    matrix Ax = A2 * x;
    Ax.print("Ax = ");
    std::cout << "Ax ?= b : " << approx(Ax, b) << "\n";
    std::cout << "\n\n" << std::endl;
    



    std::cout << "Inverse of A:\n";
    fac2.inversQR();
    A2.print("A = ");
    fac2.B.print("B = ");
    std::cout << "AB ?= I : " << approx(A2*fac2.B, I(n)) << "\n";
    std::cout << "\n\n" << std::endl;
    


    return 10;
}
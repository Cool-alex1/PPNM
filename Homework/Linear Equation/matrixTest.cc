#include<iostream>
#include<iomanip>
#include<cmath>
#include<random>
#include"matrix.h"
#include"QR.h"


int main(){
    int n = 4, m = 3;
    matrix b(4,1);
    matrix a(4,3);
    // a = a - 1;
    // b = 2 + b;
    // a.print("a = ");
    // b.print("b = ");
    // matrix c = a + b;
    // c.print("c = ");
    // a = a - 1;
    // b = b + 1;
    // b = -b;
    // int n = 0;
    // for(int i=0; i<a.nRow; i++){
    //     for(int j=0; j<a.nCol; j++){
    //         a(i,j) = n;
    //         b(i,0) = n;
    //         n++;
    //     }
    // }
    std::uniform_real_distribution<double> unif(0,1);
    std::default_random_engine re;

    
    std::cout << "matrix of shape " << n << "," << m << " with uniform random values (0,1):\n";
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m ; ++j) a(i,j) = unif(re);
    }
    // a(0,0) = 12;
    // a(1,0) = 6;
    // a(2,0) = -4;
    // a(0,1) = -51;
    // a(1,1) = 167;
    // a(2,1) = 24;
    // a(0,2) = 4;
    // a(1,2) = -68;
    // a(2,2) = -41;
    // b.getRow(2,2).print("b = ");
    // matrix I = invers(b);
    // I.print("I = ");
    // matrix s = solve(b);
    // s.print("s = ");
    // std::cout << b.det << std::endl;

    // b -= b;
    a.print("a = ");
    // b.print("b = ");
    // // matrix c = b.reshape(3, 1);
    // matrix c = b * invers(b);
    // c.print("c = ");
    // matrix c = a - b;
    // c.print("c = ");

    // matrix d = a * b;
    // d.print("d = ");

    // matrix e = a * 4;
    // e.print("e = ");

    // matrix f = 5 * a;
    // f.print("f = ");

    // matrix g = a/0.4;
    // g.print();
    // matrix d = a;
    // a(0,0) = 10;
    // a.print();
    // d.print();

    // matrix d = T(b);
    // d.print("d = ");

    // matrix e(5,3);
    // e = e + 1;
    // a = append(a, e, 1);
    // // a.print();
    // a(1,1) = 2;
    // matrix f = a.swapCol(1, 2);
    // f.print();

    // a.setRow(0, b);
    // a.print("a = ");

    // std::cout << length(b) << std::endl;
    // (invers(a)*b).print("x = ");
    // std::cout << invers(a).det << std::endl;
    
    
    QR qr(a);
    qr.decomp();
    (qr.Q).print("Q = ");
    (qr.R).print("R = ");
    (qr.Q.T() * qr.Q).print("I = ");

    for(int i = 0; i < n; ++i) {
        b(i,0) = unif(re);
    }
    b.print("b = ");
    (qr.solve(b)).print("x = ");
    // std::cout << invers(qr.R).det << std::endl;
    // (a).print("b = ");



    qr.inversQR();
    (qr.B * a).print("AB = ");
    


    return 0;
}
#include<cmath>
#include<string>
#include<iostream>
#include<vector>
#include<functional>
#include"matrix.h"
#include"QR.h"

std::tuple<matrix, matrix> lsfit(const std::vector<std::function<double(double)>>& f, const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& dy) {
    matrix A(x.size(), f.size());
    matrix b(y.size(), 1);
    for(int i = 0; i < (int)x.size() ; ++i) {
        for(int j = 0; j < (int)f.size() ; ++j) {
            A(i,j) = f[j](x[i])/dy[i];
        }
        b(i,0) = y[i]/dy[i];
    }

    QR qr(A);
    qr.decomp();
    matrix para = qr.solve(b);

    qr.inversQR();
    matrix cov = qr.B * qr.B.T();

    return std::make_tuple(para, cov);
}
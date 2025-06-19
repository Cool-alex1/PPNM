#include<cmath>
#include<string>
#include<iostream>
#include"matrix.h"
#include"QR.h"
#define SELF (*this)

void QR::decomp(){
    for(int j=0; j<Q.nCol; j++){
        matrix col = A.getCol(j);
        matrix a = col.copy();

        for(int k=0; k<j; k++){
            R(k, j) = (a.T() * Q.getCol(k))(0,0);
            col -= R(k, j) * Q.getCol(k);
        }
        R(j,j) = length(col);
        col /= R(j,j);
        Q.setCol(j, col);
    }
}

matrix QR::solve(const matrix& b) const {return invers(R)*Q.T()*b;}
matrix QR::solve(const vector& b) const {
    matrix b2(len(b), 1);
    for (int i=0; i<len(b); i++) b2(i,0) = b[i];
    return invers(R)*Q.T()*b;}

void QR::inversQR(){
    B = invers(R)*Q.T();
}

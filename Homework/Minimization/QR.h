#ifndef HAVE_QR_H
#define HAVE_QR_H
#include<iostream>
#include<string>
#include"matrix.h"

class QR{
    public: 
        matrix Q, R;
        matrix& A;
        matrix B;
        matrix Rinv;

	QR(matrix& a): A(a) {
        Q = a.copy();
        R = matrix(a.nCol, a.nCol);
        Rinv = I(a.nRow);
    }

	QR()=default;
	QR(const QR&)=default;
	QR(QR&&)=default;
	~QR()=default;

	QR& operator=(const QR&)=default;
	QR& operator=(QR&&)=default;


	void decomp();
	void inversQR();
	matrix solve(const matrix&) const;
	matrix solve(const vector&) const;

};

#endif
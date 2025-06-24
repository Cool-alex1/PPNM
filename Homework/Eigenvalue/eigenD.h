#ifndef HAVE_eigenD_H
#define HAVE_eigenD_H
#include<iostream>
#include<string>
#include"matrix.h"

class EigenD{
    public: 
        matrix& M;
		matrix V, D;

	EigenD(matrix& a): M(a) {
        D = a.copy();
        V = I(a.nCol);
    }

	EigenD()=default;
	EigenD(const EigenD&)=default;
	EigenD(EigenD&&)=default;
	~EigenD()=default;
	EigenD& operator=(const EigenD&)=default;
	EigenD& operator=(EigenD&&)=default;


	void timesJ(matrix&, int, int, double);
	void Jtimes(matrix&, int, int, double);
	void cyclic();

};

#endif
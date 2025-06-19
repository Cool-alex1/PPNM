#ifndef HAVE_VEC_H
#define HAVE_VEC_H
#include"vector.h"
#include<iostream>
#include<string>
#include<vector>

class matrix{
    public: std::vector<double> mat;
    public: 
        int nRow; 
        int nCol;
		double det;

	matrix(int row, int col): mat(row * col){
        nRow = row;
        nCol = col;
		det = 0;
    }
	matrix() = default;
	matrix(const matrix&)=default;
	matrix(matrix&&)=default;
	~matrix()=default;

	matrix& operator=(const matrix&)=default;
	matrix& operator=(matrix&&)=default;
	matrix& operator+=(const matrix&);
	matrix& operator-=(const matrix&);
	matrix& operator+=(double);
	matrix& operator-=(double);
	matrix& operator*=(double);
	matrix& operator/=(double);

	double& operator()(int r, int c) {
		if(r < nRow && c < nCol){return mat[r*nCol + c];}
		throw std::invalid_argument("Matrix call out of bounce: (" + std::to_string(r) + "," + std::to_string(c) + ")");}
	double operator()(int r, int c) const {
		if(r < nRow && c < nCol){return mat[r*nCol + c];}
		throw std::invalid_argument("Matrix call out of bounce: (" + std::to_string(r) + "," + std::to_string(c) + ")");}

	void print(std::string s="") const;
	matrix getCol(int, int n=1) const;
	matrix getRow(int, int n=1) const;
	void setCol(int, const matrix&);
	void setRow(int, const matrix&);
	matrix swapCol(int, int) const;
	matrix swapRow(int, int) const;
	matrix copy() const;
	matrix append(const matrix&, int axis=0) const;
	matrix reshape(int, int) const;
	matrix T() const;
	// matrix append(const matrix, int axis=0);
	
	friend std::ostream& operator<<(std::ostream& os, const matrix& v);
};
matrix operator-(const matrix&, const matrix&);
matrix operator-(const matrix&, double);
matrix operator-(const matrix&);
matrix operator+(const matrix&, const matrix&);
matrix operator+(const matrix&, double);
matrix operator+(double, const matrix&);
matrix operator*(const matrix&, const matrix&);
matrix operator*(const matrix&, double);
matrix operator*(double, const matrix&);
matrix operator/(const matrix&, double);
matrix T(const matrix&);

matrix I(int);
matrix compPro(const matrix&, const matrix&);
matrix solve(const matrix&);
matrix invers(const matrix&);
matrix proj(const matrix&, const matrix&);
vector toVector(const matrix&);
double length(const matrix&);
bool approx(const matrix&, const matrix&, double acc=1e-6,double eps=1e-6);
#endif
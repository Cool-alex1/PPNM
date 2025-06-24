#ifndef HAVE_VEC_H
#define HAVE_VEC_H
#include<iostream>
#include<string>
#include<vector>
// #include"matrix.h"

class vector{
    public: std::vector<double> vec;
    public: 
        int len;

	vector(int n): vec(n){
        len = n;
    }
	vector() = default;
	vector(const vector&)=default;
	vector(vector&&)=default;
	~vector()=default;

	vector(std::initializer_list<double> list) : vec(list.begin(),list.end()) {len = list.size();}
	vector& operator=(const vector&)=default;
	vector& operator=(vector&&)=default;
	vector& operator+=(const vector&);
	vector& operator-=(const vector&);
	vector& operator+=(double);
	vector& operator-=(double);
	vector& operator*=(double);
	vector& operator/=(double);

	inline double& operator[](int i) {
		if(i < len && 0 <= i){return vec[i];}
		if(-i < len && 0 >= i){return vec[vec.size()+i];}
		throw std::invalid_argument("Vector call out of bounce: (" + std::to_string(i) + ")");}
	inline double operator[](int i) const {
		if(i < len && 0 <= i){return vec[i];}
		if(-i < len && 0 >= i){return vec[vec.size()+i];}
		throw std::invalid_argument("Vector call out of bounce: (" + std::to_string(i) + ")");}

	void print(std::string s="") const;
	vector swap(int, int) const;
	vector copy() const;
	bool isZero() const;
	vector diff() const;
	vector unit(int) const;
	double norm() const;
	void append(const vector&);
	void append(const double&);
	
	friend std::ostream& operator<<(std::ostream& os, const vector& v);
};
vector operator-(const vector&, const vector&);
vector operator-(const vector&, double);
vector operator-(const vector&);
vector operator+(const vector&, const vector&);
vector operator+(const vector&, double);
vector operator+(double, const vector&);
double operator*(const vector&, const vector&);
vector operator*(const vector&, double);
vector operator*(double, const vector&);
vector operator/(const vector&, double);

vector compPro(const vector&, const vector&);
vector proj(const vector&, const vector&);
int len(const vector&);
// matrix toMatrix(const vector&, int axis=0);
bool approx(const vector&, const vector&, double acc=1e-6,double eps=1e-6);
#endif
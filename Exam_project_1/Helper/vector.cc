#include<cmath>
#include<string>
#include<iostream>
// #include"matrix.h"
#include"vector.h"
#define SELF (*this)

vector& vector::operator+=(double n){
	for (int i=0; i < len; i++){vec[i] += n;}
	return *this;
}
vector& vector::operator-=(double n){
	*this += -n;
	return *this;
}
vector& vector::operator*=(double n){
	for (int i=0; i < len; i++){vec[i] *= n;}
	return *this;
}
vector& vector::operator/=(double n){
	*this *= 1/n;
	return *this;
}
vector& vector::operator+=(const vector& a){
	vector m(a.len);
	if(SELF.len == a.len){
		for (int i=0; i < m.len; i++){vec[i] += a[i];}
		return *this;
	} else {
		throw std::invalid_argument( "Shapes of the matrisies does not match: (" + std::to_string(SELF.len) + ") != (" + std::to_string(a.len) + ")");
	}
}
vector& vector::operator-=(const vector& a){
	*this += -a;
	return *this;
}

vector operator+(const vector& mOri, double a){
	vector m(mOri.len);
	for (int i=0; i < m.len; i++){m[i] = mOri[i] + a;}
	return m;
}
vector operator+(const vector& a, const vector& b){
	vector m(a.len);
	if(a.len == b.len){
		for (int i=0; i < m.len; i++){m[i] = a[i] + b[i];}
		return m;
	} else {
		throw std::invalid_argument( "Shapes of the vectors does not match: (" + std::to_string(a.len) + ") != (" + std::to_string(b.len) + ")");
	}
}
vector operator+(double a, const vector& mOri){return mOri + a;}
vector operator-(const vector& mOri, double a){
	vector m(mOri.len);
	for (int i=0; i < m.len; i++){m[i] = mOri[i] - a;}
	return m;
}
vector operator-(const vector& a, const vector& b){
	vector m(a.len);
	if(a.len == b.len){
		for (int i=0; i < m.len; i++){m[i] = a[i] - b[i];}
		return m;
	} else {
		throw std::invalid_argument( "Shapes of the vectors does not match: (" + std::to_string(a.len) + ") != (" + std::to_string(b.len) + ")");
	}
}
vector operator-(const vector& mOri){
	vector m(mOri.len);
	return m - mOri;
}
vector operator*(const vector& mOri, double a){
	vector m(mOri.len);
	for (int i=0; i < m.len; i++){m[i] = mOri[i] * a;}
	return m;
}
vector operator*(double a, const vector& mOri){return mOri * a;}
double operator*(const vector& a, const vector& b){
	if(a.len == b.len){
		double l = 0;
		for (int i=0; i < a.len; i++){l += a[i] * b[i];}
		return l;
	} else {
		throw std::invalid_argument( "Shapes of the vectors does not match: (" + std::to_string(a.len) + ") * (" + std::to_string(b.len) + ")");
	}
}
vector operator/(const vector& mOri, double a){
	if(a != 0){
		vector m(mOri.len);
		for (int i=0; i < m.len; i++){m[i] = mOri[i] / a;}
		return m;
	} else {
		throw std::invalid_argument("Dividing with 0");
	}
}

vector compPro(const vector& a, const vector& b){
	vector m(a.len);
	if(a.len == b.len){
		for (int i=0; i < m.len; i++){m[i] = a[i] * b[i];}
		return m;
	} else {
		throw std::invalid_argument( "Shapes of the vectors does not match: (" + std::to_string(a.len) + ") != (" + std::to_string(b.len) + ")");
	}
}

double vector::norm() const {
	if(len == 1){return vec[0];} 
	else {
		double l = 0;
		for (int i=0; i < len; i++){l += std::pow(vec[i],2);}
        return std::sqrt(l);
	}
}
vector vector::diff() const {
	vector v(len - 1);
	for(int i = 0; i < len-1 ; ++i) v[i] = vec[i+1] - vec[i];
	return v;
}
vector proj(const vector& u, const vector& a){
	return (u*a)/u.norm()*u;
}
int len(const vector& a){
    return a.len;
}
double sum(const vector& a){
	double s=0;
	for(int i = 0; i < a.len ; ++i) s += a[i];
    return s;
}


void vector::append(const vector& b) {
	// vector m(SELF.len + b.len);
    for (int i=0; i < b.len; i++){
		vec.push_back(b[i]);
		len += 1;
		// if(i < SELF.len) {m[i] = vec[i];}
        // else {m[i] = b[i-SELF.len];}
    }
    // return m;
}
void vector::append(const double& b) {
	vec.push_back(b);
	len += 1;
    // vector m(SELF.len + b.len);
    // for (int i=0; i < m.len; i++){
    //     if(i < SELF.len) {m[i] = vec[i];}
    //     else {m[i] = b[i-SELF.len];}
    // }
    // return m;
}
vector vector::copy() const {
	vector m(len);
	for (int i=0; i < len; i++){
		m[i] = vec[i];
	}
	return m;
}
bool vector::isZero() const {
	if(len == 0) return true;
	for (int i=0; i < len; i++){
		if(vec[i] != 0) return false;
	}
	return true;
}
vector vector::unit(int i) const {
	vector m(len);
	m[i] = vec[i];
	return m;
}
vector vector::swap(int a, int b) const {
	vector m = SELF.copy();
	double temp1 = m[a];
	double temp2 = m[b];
	for (int i=0; i < len; i++){
		m[b] = temp1;
		m[a] = temp2;
	}
	return m;
}



void vector::print(std::string s) const {
	std::cout << s << "[";
	for (int i=0; i < len; i++){
        if(i != len-1){std::cout << vec[i] << ", ";}
        else {std::cout << vec[i];}
    }
	std::cout << "]" << std::endl;
}

bool approx(const vector& A, const vector& B, double acc, double eps){
	for (int i=0; i < A.len; i++){
			double a = A[i];
			double b = B[i];
			if(std::abs(a-b) >= acc) return false;
			if(a > acc && b > acc && std::abs(a-b)/std::max(std::abs(a), std::abs(b)) >= eps) return false;
	}
	return true;
}
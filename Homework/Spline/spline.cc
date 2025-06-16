#include"vector.h"
#include"spline.h"
#include<exception>
#include<cmath>

int binsearch(vector x, double z){
    if( z<x[0] || z>x[x.len-1] ) throw std::invalid_argument("Bad z");;
	int i=0, j=x.len-1;
	while(j-i>1){
		int mid=(i+j)/2;
		if(z>x[mid]) i=mid; else j=mid;
		}
	return i;
}
double linterp(vector x, vector y, double z){
    int i=binsearch(x,z);
    double dx=x[i+1]-x[i]; if(!(dx>0)) throw std::invalid_argument("Why are you going backwords?");;
    double dy=y[i+1]-y[i];
    return y[i]+dy/dx*(z-x[i]);
}

double linterpInteg(vector x, vector y, double z){
    double s=0;
    int iMax = binsearch(x, z);
    for(int i=0; i<iMax; i++){
        s += (x[i+1] - x[i])*(y[i] + y[i+1]) / 2; // area of trapezoid from x[i] to x[i]+Δx
    }
    s += (z - x[iMax])*(y[iMax] + linterp(x, y, z)) / 2; // area of the rest

    return s;
}


void qSpline::buildSpline() {
    vector dx(c.len), p(c.len);
    for(int i = 0; i < x.len - 1 ; ++i) {
        dx[i] = x[i+1] - x[i];
        p[i] = (y[i+1] - y[i])/dx[i];
    }
    for(int i = 0; i<x.len - 2 ; ++i) c[i+1] = 1/dx[i+1] * (p[i+1] - p[i] - c[i]*dx[i]);
    for(int i = x.len - 3; i>=0; --i) c[i] = 0.5 * (c[i] + 1/dx[i]*(p[i+1] - p[i] - c[i+1]*dx[i+1]));
    for(int i = 0; i<c.len; ++i) b[i] = p[i] - c[i]*dx[i];
}

double qSpline::eval(double z) const {
    int i = binsearch(x,z);
    return y[i] + b[i] * (z - x[i]) + c[i] * pow((z - x[i]),2);
}

double qSpline::integral(double z) {
    int iMax = binsearch(x,z);
    double sum = 0;
    for(int i = 0; i < iMax ; ++i) {
        double dx = x[i+1] - x[i];
        sum += (y[i] + 0.5*b[i]*dx + c[i]/3 *dx*dx) * dx;
    }
    double dx = z - x[iMax];
    sum += (y[iMax] + 0.5 * b[iMax]*dx + c[iMax]/3 * dx*dx) * dx;
    return sum;
}

double qSpline::deriv(double z) {
    int i = binsearch(x,z);
    return b[i] + 2*c[i] * (z - x[i]);
}
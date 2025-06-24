// #ifndef HAVE_SPLINE_H
// #define HAVE_SPLINE_H

#include"vector.h"
#include<exception>
#include<cmath>

int binsearch(vector, double);
double linterp(vector, vector, double);
double linterpInteg(vector, vector, double);


class qSpline {
    public:
        vector x,y,b,c;        
        
        qSpline(const vector& x, const vector& y) : x(x), y(y) {
            b = vector(x.len - 1);
            c = vector(x.len - 1);
            buildSpline();
        } // parametrized constructor


        qSpline() = default; // default constructor
        qSpline(const qSpline&)=default; // copy constructor
        qSpline(qSpline&&)=default; // move constructor
        ~qSpline()=default; // destructor
        qSpline& operator=(const qSpline&)=default; // copy assignment
        qSpline& operator=(qSpline&&)=default; // move assignment

        void buildSpline(); //Calculate the quadratic spline and set b and c
        double eval(double) const;
        double integral(double);
        double deriv(double);
        inline double operator()(double z) const {return eval(z);}

};
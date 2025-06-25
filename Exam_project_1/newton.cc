#include<iostream>
#include<iomanip>
#include<cmath>
#include<functional>
#include"newton.h"

/* Calculating the gradient*/
vector gradient(const std::function<double(vector)>& f, vector v, matrix H, double R){
    matrix vm = toMatrix(v).T();
    return 2 * toVector((H*vm - R*vm)) / (v*v);
}

/* My own minimizer method */
// Due to the unique properties of the f(v-α*Δv) function the method below has been developed:
// It works by looking at a startpoint and another point in a chosen direction close by.
// If f(x+δx) is smaller than f(x) (going downhill) it will keep going in the same direction,
// but when f(x+δx) becomes bigger than f(x) a small step forward will be taken,
// then the direction will flip and the stepsize will be halved.
// An analogy for this method is a ball rolling down a hill.
// All the values chosen in this function have been chosen on the basis of testing and optimization.
double findMin(const std::function<double(vector)>& f, double a0, double aStep, vector v, vector Δv, double acc){
    double f1;
    double f2;
    double α = a0;
    bool turn = true;
    while (std::abs(α-a0) < 1){  //Stop if α is to far from a0
        if(turn) f1 = f(v-α*Δv); //Only need to calculate f two times when turning around
        f2 = f(v-(α+aStep)*Δv);
        
        if (std::abs(f1 - f2) < acc) break; //If change is to small a good α has been found

        if((f2 - f1) > 0){   //If the gradient between f(α) and the next value ever becomes positive (uphill)
            α += aStep*0.8;  //Take a smaller step forward and
            aStep /= -2;     //Turn around and reduce the step size
            turn = true;
        } else {
            α += aStep;      //Take a standard step
            f1 = f2;         //The new f(x) has already been calculated
            turn = false;
        }
    }
    return α;
}

/* The main method*/
// This method minimizes the Rayleigh quotient by changing v into a eigenvector for H
// resulting in the lowest eigenvalue (λ_min).
vector newton(const std::function<double(vector)>& f, vector v, matrix H, double acc, std::string p){
    v /= v.norm();       //Normalize v
    int n = 0;           //Counter
    double a = 0.5;      //Start guess for α
    double R_val = f(v); //The Rayleigh quotient
    vector g;            //Gradient
    matrix vm;           //Vector v as a 1xsize(v) matrix (Used for matrix multiplication)
    vector Δv;           //Direction to improve v in

    while (1) {
        /*  Gradient check  */
        // If the gradient for R(v)|_H is small enough then
        // v cannot be improved significantly
        vector g = gradient(f, v, H, R_val);
        if (g.norm() < acc) break;
        
        
        /*  Finding the best α  */
        vm = toMatrix(v).T();
        Δv = toVector((H*vm - R_val*vm));
        
        //My own local minimum finder (See desciption by "findMin"):
        double a1 = findMin(f, -a, 0.05, v, Δv, 1e-26);  //Going towards zero from the left
        double a2 = findMin(f, a, -0.05, v, Δv, 1e-26);  //Going towards zero from the right (I need to look two times because of the properties for f(v-αΔv))
        
        if(f(v-a1*Δv) > f(v-a2*Δv)){a = a2;}   //Set a to either a1 or a2 depending on which resulting in the lowest f(v-αΔv)
        else {a = a1;}
        
        
        /* Update values */
        v -= a*Δv;
        v /= v.norm();
        R_val = f(v);
        n += 1;

        if(p == "R") std::cout << R_val << std::endl;
    }
    if(p == "n") std::cout << "Solved in " << n << " iteration(s)" << std::endl;

    return v;
}
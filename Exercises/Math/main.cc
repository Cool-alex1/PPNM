#include<iostream>
#include<cmath>
#include"sfuns.h"

int main(){
    //Task 1
    double a = std::sqrt(2);
    double b = std::pow(2, 0.2);
    double c = std::exp(M_PI);
    double d = std::pow(M_PI, std::exp(1));
    std::cout << "a="  <<  a  <<  ", b="  <<  b  <<  ", c=" <<  c  <<  ", d=" <<  d  <<std::endl;

    //Task 2
    for(int i=1; i<11; i++){
        std::cout << "Γ(" <<  i  <<  ") = " <<  sfuns::fgamma(i)  <<std::endl;
    }

    //Task 3
    for(int i=1; i<11; i++){
        std::cout << "Γ(" <<  i  <<  ") = " <<  sfuns::lngamma(i)  <<std::endl;
    }
}
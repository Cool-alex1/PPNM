#include<iostream>
#include<cmath>
#include"sfuns.h"
int main(){
    std::cout << "hello again from c++" <<std::endl;
    double x = std::sin(1.0);
    double y = std::cos(1.0);
    double z = sfuns::fgamma(1.0);
    std::cout << "x=" << x << ", y=" << y << ", z=" << z << std::endl;
}
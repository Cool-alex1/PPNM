#include<iostream>
#include"vec.h"
#include<vector>
int main(){
    double x=5;
    double y=x;
    double& z=x;
    int n=3;
    std::vector<double> a(3);
    for(u_long i=0; i<a.size(); i++) a[i]=i+1;
    std::vector<double> b=a;   //With & it copies the references, without it copies the values
    // auto b=a;
    vec v;
    std::cout << v.x << v.y << v.z << "\n";

    return 0;
}
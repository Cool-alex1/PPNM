#include<iostream>
#include<iomanip>
#include<cmath>

static bool approx(double a, double b, double acc=1e-9, double eps=1e-9){
    return std::abs(a - b) <= acc || std::abs(a - b)/std::max(std::abs(a), std::abs(b)) <= eps;
}

int main(){
    //Task Uno
    // int i=1;
    // while(i+1>i) {
    //     i++;
    // }
    // std::cout << "my max int = " << i <<std::endl;

    // i=0;
    // while(i-1<i) {
    //     i--;
    // }
    // std::cout << "my min int = " << i <<std::endl;


    //Task Dos
    double x=1;
    while(1+x != 1) {x /= 2;}
    x *= 2;
    std::cout << "my double increment = " << x <<std::endl;

    float y=1.0;
    while((float)(1.0+y) != 1.0){y /= 2.0;}
    y *= 2.0;
    std::cout << "my float increment = " << y <<std::endl;


    //Task Dres
    double epsilon=x;
    double tiny=epsilon/2;
    double a=1+tiny+tiny;
    double b=tiny+tiny+1;

    bool test1 = a==b;
    bool test2 = a>1;
    bool test3 = b>1;

    std::cout << "a==b ? " << test1 <<std::endl;
    std::cout << "a>1 ? " << test2 <<std::endl;
    std::cout << "b>1 ? " << test3 <<std::endl;


    //Task Quadro
    double d1 = 0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1;
    double d2 = 8*0.1; 

    bool test23 = d1==d2;

    std::cout << std::setprecision(20) << std::fixed;
    std::cout << "d1 = " << d1 <<std::endl;
    std::cout << "d2 =  " << d2 <<std::endl;
    std::cout << "d1==d2 ? => " << test23 <<std::endl;


    //Task ??
    bool testSlut = approx(d1, d2);
    std::cout << "Approx test på d1 og d2 => " << testSlut <<std::endl;

}
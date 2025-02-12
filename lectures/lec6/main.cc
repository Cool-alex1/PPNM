#include<iostream>
#include<cmath>
#include<complex>
#include<string>
#include<functional>

typedef std::complex<double> complex;

template < typename T >
void echo(T arg){
    std::cout << "echo: " << arg << "\n";
}

void fun_of_two(std::function<double(double)> f){std::cout << "f(2) = " << f(2) << "\n";}

int main(){
    echo("string");
    echo(1);
    echo(1.23);
    complex I = std::sqrt((complex)(-1));
    echo(std::sin(std::sqrt(I)));

    std::string s="original string";
    std::function<void(void)> prints = [=, &s](){std::cout << "prints: s = " << s << "\n";};  //[=, &s] betyder at alle varialble der ikke er s gemmes som værdi, imens s gemmes som reference 
    // std::function<void(void)> prints = [=](){std::cout << "prints: s = " << s << "\n";};
    // std::function<void(void)> prints = [&](){std::cout << "prints: s = " << s << "\n";};
    prints();
    s="new string";
    prints();

    std::function<double(double)> f = [](double x){return x*x;};
    fun_of_two(f);
    fun_of_two([](double x){return x*x;});

    return 0;
}
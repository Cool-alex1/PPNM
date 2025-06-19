#include<iostream>
#include<functional>
#include<tuple>
#include<cmath>
#include"mini.h"

std::function<double(vector)> f_rosen = [](vector x){return (1-x[0])*(1-x[0]) + 100*std::pow((x[1] - x[0]*x[0]), 2);};
// std::function<double(vector)> f_himmel = [](vector x){return (1-x[0])*(1-x[0]) + 100*std::pow((x[1] - x[0]*x[0]))}

int main(int argc, char** argv) {
    std::string mode = "";
    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];
        if(arg == "-mode" && i+1<argc) mode = argv[i + 1];
    }

    vector start(2);
    start[0] = 0;
    start[1] = 0;
    vector mini = newton(f_rosen, start);

    mini.print("min = ");

    return 9;
}
#include<iostream>
#include<iomanip>
#include<cmath>
#include<random>
#include<vector>
#include"matrix.h"
#include"eigenD.h"

int main(int argc, char** argv) {
    double rmax = 10,
           dr = 0.3;
    int wf = 0; //Save data for the first wf eigenfunctions, if 0 don't.

    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];

        if(arg == "-rmax" && i+1<argc) rmax = std::stod(argv[i + 1]);
        if(arg == "-dr" && i+1<argc) dr = std::stod(argv[i + 1]);
        if(arg == "-wf" && i+1<argc) wf = std::stoi(argv[i + 1]);
    }

    int N = (int)(rmax/dr)-1;
    std::vector<double> r(N);
    for(int i=0;i<N;i++) r[i]=dr*(i+1);

    matrix H(N, N);
    
    for(int i=0; i<N-1; i++){
        H(i,i)  =-2*(-0.5/dr/dr);
        H(i,i+1)= 1*(-0.5/dr/dr);
        H(i+1,i)= 1*(-0.5/dr/dr);
    }
    H(N-1, N-1) = -2*(-0.5/dr/dr);
    for(int i=0; i<N; i++) H(i,i) += -1/r[i];

    EigenD EH(H);
    EH.cyclic();

    std::cout << rmax << "," << dr << "," << EH.D(0,0) << std::endl;

    if(wf > 0) {
        std::cout << "\n\n";
        for(int k = 0; k < wf; k++) {
            matrix eVec = EH.V.getCol(k)/std::sqrt(dr);
            for(int i = 0; i < N; ++i) {
                std::cout << r[i] << "," << eVec(i,0) << "\n";
            }
            std::cout << "\n\n";
        }
    }
    return 0;
}

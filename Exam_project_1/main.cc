#include<iostream>
#include<iomanip>
#include<cmath>
#include<random>
#include<vector>
#include<functional>
#include<random>
#include"Helper/matrix.h"
#include"newton.h"



// Output for Out.txt
void mode1(){
    std::cout << "--------------------- Project 1 ---------------------\n" 
              << "Eigenvalues with Rayleigh quotient and locally optimized gradient descent\n"
              << "Link: http://212.27.24.106:8080/prog/projex/rayleigh-quotient.htm\n\n"
              << "Ex.nr. 208105\n"
              << "Date: 26/6 - 2025\n\n"
              << std::endl;



    std::cout << "********** Important ***********\n" 
    << "The theory provided in this project has two mistakes.\n"
    << "1)\n"
    << "\tGoing from the gradient to Δv is says\n"
    << "\t2[Hv-Rv]/(v^Tv) ∝ (H-R)v. This is not true since\n"
    << "\tR is a single value and not a matrix. It should probably\n"
    << "\tsay something like 2[Hv-Rv]/(v^Tv) ∝ (Hv-Rv):)\n"
    << "\n2)\n"
    << "\tIt says R(v-αΔv)=(v^THv-2αΔv^THv+α²Δv^THΔv)/(v^Tv+α²Δv^TΔv)\n"
    << "\tThe denominator here is wrong, it is instead (v^Tv-2αΔv^Tv+α²Δv^TΔv)\n\n"
    << std::endl;
    
    std::cout << "--------------- Output ---------------\n" << std::endl;


    vector v0, res;
    matrix H;
    std::function<double(vector)> R = [&](vector v){
        matrix vm = toMatrix(v);                //To make sure v can be a vector in main
        return (vm * H * vm.T())(0,0) / (v*v);  //Since toMatrix([1,1]) --> [[1,1]], vm and vm.T are swapped
    };                                          //matrix * matrix --> matrix, therefore the only element must be exracted, hence "(0,0)"
    

    /* Test */
    H = matrix({{1, 2},
                {2, 1}});
    H.print("H = ");
    res = newton(R, vector({1,0}), H, 1e-5);
    std::cout << "λ_min = " << R(res) << "   Expected: -1" << std::endl;
    res.print("v_min = ");
    std::cout << "Difference between H*v_min and R*v_min:" << std::endl;
    (toVector((H/R(res) * toMatrix(res).T())) - res).print("");
    std::cout << "\n" << std::endl;
    
    H = matrix({{-2, 2, 1},
                {2, 1, 2},
                {1, 2, 6}});
    H.print("H = ");
    res = newton(R, vector({1,0, 0}), H, 1e-5);
    std::cout << "λ_min = " << R(res) << "   Expected: -3" << std::endl;
    res.print("v_min = ");
    std::cout << "Difference between H*v_min and R*v_min:" << std::endl;
    (toVector((H/R(res) * toMatrix(res).T())) - res).print("");
    std::cout << "\n" << std::endl;
    
    
    
    std::default_random_engine re(0);
    std::uniform_real_distribution<double> unif(-1,1);
    
    int N = 100;
    H = matrix(N, N);
    for(int i=0; i<N; i++){
        H(i,i) = unif(re)*2;  //Diagonal
        for(int j=i+1; j<N; j++){
            H(i,j) = unif(re)*2;  //Horisontal
            H(j,i) = H(i,j);  //Down
        }
    }
    v0 = vector(N)+1;
    std::cout << "On a " << N << "x" << N << " symmetric matrix:" << std::endl;
    res = newton(R, v0, H, 1e-5);
    std::cout << "λ_min = " << R(res) << std::endl;
    std::cout << "Norm of the difference between H*v_min and R*v_min: " << (toVector((H/R(res) * toMatrix(res).T())) - res).norm() << std::endl;
    std::cout << "\n" << std::endl;

    std::cout << "The speed at which this method successfully finds the lowest eigenvalue\n" 
              << "for a NxN matrix can be seen on 'Plot.speed.svg'. Since the calculation\n"
              << "of R has a runtime of O(n^2) and the newton function has some scaling\n"
              << "I plotted along with the data a a*x^3 polynomium, which seem to fit quite nicely.\n"
              << "It seems that it is possible to get the lowest eigenvalue for a matrix \n"
              << "of size <200x<200 within a couple of secounds with this method. This result\n"
              << "is however very dependent on how accurate you want the result and how good\n"
              << "your chose of v0 is.\n"
              << std::endl;

    
    
    
    
    
    
    
    /* Hydrogen */ 
    // The making of H
    double rmax = 8,
           dr = 1.0/8;
    
    N = (int)(rmax/dr)-1;
    vector r(N);
    for(int i=0; i<N; i++) r[i] = dr*(i+1);
    
    H = matrix(N, N);
    for(int i=0; i<N-1; i++){
        H(i,i)  =-2*(-0.5/dr/dr);
        H(i,i+1)= 1*(-0.5/dr/dr);
        H(i+1,i)= 1*(-0.5/dr/dr);
    }
    H(N-1, N-1) = -2*(-0.5/dr/dr);
    for(int i=0; i<N; i++) H(i,i) += -1/r[i];
    
    
    
    std::cout << "\n--- Hydrogen atom ---" << std::endl;
    std::cout << "r_max = " << rmax << std::endl;
    std::cout << "r_min = " << dr << std::endl;
    std::cout << "Δr = " << dr << std::endl;
    std::cout << "Size(H) = (" << N << ", " << N << ")\n" << std::endl;
    std::cout << "Ground state:" << std::endl;
    v0 = vector(N)+1;
    res = newton(R, v0, H, 1e-8);
    std::cout << "λ_min = " << R(res) << "    Expected: 0.5" << std::endl;
    std::cout << "Norm of the difference between H*v_min and R*v_min: " << (toVector((H/R(res) * toMatrix(res).T())) - res).norm() << std::endl;
    
    std::cout << "\n" << std::endl;
    

        
    std::cout << "Second smallest eigenvalue:" << std::endl;
    vector v2 = vector(N)+1;
    v2[-1] = 1 - sum(res)/res[-1]; //Making v2 orthogonal to res
    
    std::cout << "Making v0 orthogonal to v_min" << std::endl;
    std::cout << "v_min*v0 = " << res*v2 << "\n" << std::endl;
    
    
    vector res2 = newton(R, v2, H, 1e-3);
    std::cout << "λ_min2 = " << R(res2) << std::endl;
    std::cout << "Norm of the difference between H*v_min2 and R*v_min2: " << (toVector((H/R(res2) * toMatrix(res2).T())) - res2).norm() << std::endl;
    std::cout << "\n" << std::endl;
    
    std::cout << "In the plot 'Plot.hydrogen.svg' you can see the two wavefunctions (v_min and v_min2) found above.\n" << std::endl;

    std::cout << "One must be carefull when calculating the secound smallest eigenvalue.\n" 
              << "Since v0 must be a combination of all the eigenvectors but v_min,\n"
              << "the uncertainty when calculating v_min will not have an immediately impact\n"
              << "on the calculations for λ_min2 but if a too high accuracy is required\n"
              << "the result will look like in the plot 'Plot.R.svg', where the result almost\n"
              << "converges but then falls down to λ_min."
              << std::endl;
}





// Output for Out.data.txt
void plot(){
    vector v0, res;
    matrix H;
    std::function<double(vector)> R = [&](vector v){
        matrix vm = toMatrix(v);                //To make sure v can be a vector in main
        return (vm * H * vm.T())(0,0) / (v*v);  //Since toMatrix([1,1]) --> [[1,1]], vm and vm.T are swapped
    };                                          //matrix * matrix --> matrix, therefore the only element must be exracted, hence "(0,0)"
    
    /* Hydrogen */ 
    // The making of H
    double rmax = 8,
           dr = 1.0/4;
    
    int N = (int)(rmax/dr)-1;
    vector r(N);
    for(int i=0; i<N; i++) r[i] = dr*(i+1);
    
    H = matrix(N, N);
    for(int i=0; i<N-1; i++){
        H(i,i)  =-2*(-0.5/dr/dr);
        H(i,i+1)= 1*(-0.5/dr/dr);
        H(i+1,i)= 1*(-0.5/dr/dr);
    }
    H(N-1, N-1) = -2*(-0.5/dr/dr);
    for(int i=0; i<N; i++) H(i,i) += -1/r[i];
    
    
    v0 = vector(N)+1;
    res = newton(R, v0, H, 1e-8, "R");
    std::cout << "\n" << std::endl;
    
    for(int i=0; i<N; i++){
        std::cout << r[i] << " " << res[i] << std::endl;
    }
    std::cout << "\n" << std::endl;
    
    
    vector v2 = vector(N)+1;
    v2[-1] = 1 - sum(res)/res[-1]; //Making v2 orthogonal to res
    
    
    vector res2 = newton(R, v2, H, 1e-4, "R");
    std::cout << "\n" << std::endl;


    res2 = newton(R, v2, H, 1e-3, "");
    std::cout << "\n" << std::endl;
    
    for(int i=0; i<N; i++){
        std::cout << r[i] << " " << res2[i] << std::endl;
    }
}



// Output for Out.speed.txt
void speed(int N){
    vector v0, res;
    matrix H;
    std::function<double(vector)> R = [&](vector v){
        matrix vm = toMatrix(v);                //To make sure v can be a vector in main
        return (vm * H * vm.T())(0,0) / (v*v);  //Since toMatrix([1,1]) --> [[1,1]], vm and vm.T are swapped
    };                                          //matrix * matrix --> matrix, therefore the only element must be exracted, hence "(0,0)"

    std::default_random_engine re(0);
    std::uniform_real_distribution<double> unif(-1,1);
    
    H = matrix(N, N);
    for(int i=0; i<N; i++){
        H(i,i) = unif(re)*2;  //Diagonal
        for(int j=i+1; j<N; j++){
            H(i,j) = unif(re)*2;  //Horisontal
            H(j,i) = H(i,j);  //Down
        }
    }
    v0 = vector(N)+1;
    res = newton(R, v0, H, 1e-3);
}









int main(int argc, char** argv) {
    std::string mode = "";
    int N_size = 0;
    
    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];
        if(arg == "-mode" && i+1<argc) mode = argv[i + 1];
        if(arg == "-size" && i+1<argc) N_size = std::stod(argv[i + 1]);
    }
    
    if(mode == ""){
        mode1();
    } else if(mode == "plot"){
        plot();
    } else if(mode == "speed"){
        speed(N_size);
    }
    return 0;
}

#include<iostream>
#include<iomanip>
#include<cmath>
#include<random>
#include<vector>
#include<functional>
#include<random>
#include"matrix.h"



// g = [-3.2747, 2.55912, 0.715579]
// dv = [-1.72114, 1.19577, 0.273999]


// g = [0.304975, 0.660621, -0.965066]
// dv = [0.718669, 2.80619, 1.38986]


// g = [0.349823, 0.463546, -1.11634]
// dv = [0.662185, 2.6954, 1.26541]



vector gradient(const std::function<double(vector)>& f, vector v, matrix H, double R){
    matrix vm = toMatrix(v).T();
    return 2 * toVector((H*vm - R*vm)) / (v*v);
    // return 2 * toVector((H - R)*vm) / (v*v);
}
double findMin(const std::function<double(vector)>& f, double a0, double aStep, vector v, vector Δv){
    double f1;
    double f2;
    double α = a0;
    bool turn = true;
    while (std::abs(α-a0) < 1){  //Stop if α is to far from a0
        if(turn) f1 = f(v-α*Δv);
        f2 = f(v-(α+aStep)*Δv);
        // f1 = f(α);
        // f2 = f(α+aStep);
        
        if (std::abs(f1 - f2) < 1e-20) break; //If change is to small a good α has been found

        if((f2 - f1) > 0){   //If the gradient between f(α) and the next value ever becomes positive (uphill)
            α += aStep*0.8;
            aStep /= -2;     //Turn around and take smaller steps
            turn = true;
        } else {
            turn = false;
            f1 = f2;
            α += aStep;
        }
    }
    return α;
}

vector newton(const std::function<double(vector)>& f, vector v, matrix H, double acc){
    int n = 0;
    double a=0.5;
    double R_val = f(v);
    matrix vm = toMatrix(v).T();
    vector Δv;
    matrix Δvm;
    v /= v.norm();

    while (1) {
    // while (1) {
        
        /*  Gradient check  */
        // If the gradient for R(v)|_H is small enough then
        // v cannot be improved significantly
        vector g = gradient(f, v, H, R_val);
        if (g.norm() < acc) break;
        
        
        /*  Finding the best α  */
        vm = toMatrix(v).T();
        Δv = toVector((H* vm - R_val* vm));
        Δvm = toMatrix(Δv).T();
        
        
        //My own local minimum finder:
        // std::function<double(double)> f_α = [=](double α){
        //     // return ((vm-α*Δvm).T() * H * (vm-α*Δvm))(0,0) / ((vm-α*Δvm).T()*(vm-α*Δvm))(0,0);
        //     return (vm.T()*H*vm - 2*α*Δvm.T()*H*vm + α*α*Δvm.T()*H*Δvm)(0,0) / (vm.T()*vm - 2*α*Δvm.T()*vm + α*α*Δvm.T()*Δvm)(0,0);
        // };

        a = 0.5;    //Startguess for α
        double a1 = findMin(f, -a, 0.05, v, Δv);
        double a2 = findMin(f, a, -0.05, v, Δv);
        
        if(f(v-a1*Δv) > f(v-a2*Δv)){a = a2;} 
        else {a = a1;}

        // if(n==29){
        //     std::cout << "\n" << std::endl;
        //     for(double i=-200.0; i<200; i++){
        //             std::cout << i/100 << " " << f_α(i/100) << " " << f(v-(i/100)*Δv) << " " << a << std::endl;
        //             // std::cout << i/100 << " " << f(v-(i/100)*Δv) << " " << a << std::endl;
        //     }
        //     std::cout << "\n" << std::endl;
        // }
        
        
        //Update v
        v -= a*Δv;
        // v /= v.norm();
        R_val = f(v);
        n += 1;
        // std::cout << "g.norm = " << g.norm() << std::endl;
        // std::cout << "α = " << a << std::endl;
        // v.print("v = ");
        // std::cout << "R = " << R_val << std::endl;
        // g.print("g = ");
        // Δv.print("dv = ");
        // std::cout << "\n" << std::endl;
    } 

                    
    std::cout << "n = " << n << std::endl;
    return v;
}




int main(int argc, char** argv) {
    // double rmax = 10,
    
    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];
        // if(arg == "-rmax" && i+1<argc) rmax = std::stod(argv[i + 1]);
    }
    
    // matrix H = matrix(2, 2)+1;
    // matrix H({{2, 2, 4},
    //           {2, 2, 5},
    //           {4, 5, 4}});
    // matrix H({{2, 2},
    //           {2, 3}});
    std::default_random_engine re(0);
    std::uniform_real_distribution<double> unif(-1,1);

    int N = 100;
    matrix H(N, N);
    for(int i=0; i<N; i++){
        H(i,i) = unif(re)*2;  //Diagonal
        for(int j=i+1; j<N; j++){
            H(i,j) = unif(re)*2;  //Horisontal
            H(j,i) = H(i,j);  //Down
        }
    }
    // H.print("H = ");
    // std::cout << "\n" << std::endl;
    
    vector v = vector(N)+1;
    // vector v = vector({1, 1, 1});
    
    std::function<double(vector)> R = [=](vector v){
            matrix vm = toMatrix(v);                //To make sure v can be a vector in main
            return (vm * H * vm.T())(0,0) / (v*v);  //Since toMatrix([1,1]) --> [[1,1]], vm and vm.T are swapped
        };                                          //matrix * matrix --> matrix, therefore the only element must be exracted, hence "(0,0)"
        
    vector n = newton(R, v, H, 1e-5);
    n.print("eigenvector = v_e = ");
    std::cout << "λ_min = " << R(n) << std::endl;
    std::cout << "Difference between (Hv_e) and Rv_e:" << std::endl;
    (toVector((H/R(n) * toMatrix(n).T())) - n).print("");
        
        
        
        

    /* Hydrogen */ 
    // double rmax = 8,
    // dr = 1.0/8;
    
    // int N = (int)(rmax/dr)-1;
    // std::vector<double> r(N);
    // for(int i=0; i<N; i++) r[i]=dr*(i+1);
    
    // matrix H(N, N);
    // for(int i=0; i<N-1; i++){
    //     H(i,i)  =-2*(-0.5/dr/dr);
    //     H(i,i+1)= 1*(-0.5/dr/dr);
    //     H(i+1,i)= 1*(-0.5/dr/dr);
    // }
    // H(N-1, N-1) = -2*(-0.5/dr/dr);
    // for(int i=0; i<N; i++) H(i,i) += -1/r[i];
    
    // std::function<double(vector)> R = [=](vector v){
    //     matrix vm = toMatrix(v);                //To make sure v can be a vector in main
    //     return (vm * H * vm.T())(0,0) / (v*v);  //Since toMatrix([1,1]) --> [[1,1]], vm and vm.T are swapped
    // };                                          //matrix * matrix --> matrix, therefore the only element must be exracted, hence "(0,0)"
    
    // vector v = vector(N)+1;
    // // v[0] = 1;
    // vector n = newton(R, v, H, 1e-5);
    
    
    // n.print("n = ");
    // std::cout << "λ_min = " << R(n) << "\n\n" << std::endl;
    // for(int i=0; i<N; i++){
    //     std::cout << r[i] << " " << n[i] << std::endl;
    // }

    return 0;
}






// To plot α:
// if(n==0){
//     std::cout << "\n" << std::endl;

//     for(double i=-200.0; i<200; i++){
    //         std::cout << i/100 << " " << f_α(i/100) << " " << f(v-(i/100)*Δv) << " " << a << std::endl;
    //         // std::cout << i/100 << " " << f(v-(i/100)*Δv) << " " << a << std::endl;
//     }
//     std::cout << "\n" << std::endl;
// }




// std::function<double(double)> f_α = [=](double α){
//     return ((vm-α*Δvm).T() * H * (vm-α*Δvm))(0,0) / ((vm-α*Δvm).T()*(vm-α*Δvm))(0,0);
//     // return (vm.T()*H*vm - 2*α*Δvm.T()*H*vm - α*Δvm.T()*H*vm + α*α*Δvm.T()*H*Δvm)(0,0) / (vm.T()*vm - 2*α*Δvm.T()*vm + α*α*Δvm.T()*Δvm)(0,0);
// };

// double make_R(matrix H, vector v){
//     matrix vm = toMatrix(v);                //To make sure v can be a vector in main
//     return (vm * H * vm.T())(0,0) / (v*v);  //Since toMatrix([1,1]) --> [[1,1]], vm and vm.T are swapped
//                                             //matrix * matrix --> matrix, therefore the only element must be exracted, hence "(0,0)"
// }





// std::function<double(vector, vector)> R_α = [=](vector v, vector Δv){
    //     matrix vm = toMatrix(v).T();
    //     matrix Δvm = toMatrix(Δv).T();
    //     std::function<double(double)> f_α = [=](double α){
//         return (vm.T()*H*vm - 2*α*Δvm.T()*H*Δvm)(0,0) / (v*v + α*α*Δv*Δv);
//     };
//     return f_α;
// };
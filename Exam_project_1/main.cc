#include<iostream>
#include<iomanip>
#include<cmath>
#include<random>
#include<vector>
#include<functional>
#include"matrix.h"


double make_R(matrix H, vector v){
    matrix vm = toMatrix(v);                //To make sure v can be a vector in main
    return (vm * H * vm.T())(0,0) / (v*v);  //Since toMatrix([1,1]) --> [[1,1]], vm and vm.T are swapped
                                            //matrix * matrix --> matrix, therefore the only element must be exracted, hence "(0,0)"
}


vector gradient(const std::function<double(vector)>& f, vector v, matrix H, double R){
    matrix vm = toMatrix(v).T();
    return 2 * toVector(H*vm - R*vm) / (v*v);
}



// std::function<double(vector, vector)> R_α = [=](vector v, vector Δv){
//     matrix vm = toMatrix(v).T();
//     matrix Δvm = toMatrix(Δv).T();
//     std::function<double(double)> f_α = [=](double α){
//         return (vm.T()*H*vm - 2*α*Δvm.T()*H*Δvm)(0,0) / (v*v + α*α*Δv*Δv);
//     };
//     return f_α;
// };

vector newton(const std::function<double(vector)>& f, vector v, matrix H, double acc){
    int n = 0;
    double R_val = f(v);
    matrix vm = toMatrix(v).T();
    vector Δv;
    matrix Δvm;
    v /= v.norm();


//     R = 6.30283
//     v = [0.778518, 0.627622]


//     R = 6.30506
//     v = [0.777993, 0.628274]
    
    while (n<30) {
        std::cout << "R = " << R_val << std::endl;
        // H.print("H = ");

        /*  Gradient check  */
        // If the gradient for R(v)|_H is small enough then
        // v cannot be improved significantly
        vector g = gradient(f, v, H, R_val);
        // g.print("g = ");
        if (g.norm() < acc) break;
        
        
        
        
        /*  Finding the best α  */
        vm = toMatrix(v).T();
        Δv = toVector((H - R_val) * vm);
        // Δv /= Δv.norm();
        // v.print("v = ");
        // Δv.print("dv = ");
        Δvm = toMatrix(Δv).T();
    
        std::function<double(double)> f_α = [&](double α){
            return (vm.T()*H*vm - 2*α*Δvm.T()*H*vm + α*α*Δvm.T()*H*Δvm)(0,0) / (v*v + α*α*Δv*Δv);
        };

        //My own local minimum finder:
        double a = 0.0;    //Startguess for α
        double da = +0.1;   //Steplength for α
        double fα_val;
        double fα_val2;
        while (1){
            // fα_val = f_α(a);
            // fα_val2 = f_α(a + da);
            fα_val = f_α(a);
            fα_val2 = f_α(a + da);


            if (std::abs(fα_val - fα_val2) < 1e-8) break; //If change is to small a good α has been found

            if((fα_val2 - fα_val) > 0){   //If the gradient between f(α) and the next value ever becomes positive (uphill)
                da /= -2;                 //Turn around and take smaller steps
            }
            a += da;
        }
        std::cout << "α = " << a << std::endl;
        if(n==29){
            std::cout << "\n" << std::endl;
            
            for(double i=-200.0; i<200; i++){
                std::cout << i/100 << " " << f_α(i/100) << " " << f(v-(i/100)*Δv) << " " << a << std::endl;
            }
            std::cout << "\n" << std::endl;
        }
        // (a*Δv).print("adv = ");
        // std::cout << "\n" << std::endl;

        //Update v
        R_val = f(v-a*Δv);
        v -= a*Δv;
        // v /= v.norm();
        R_val = f(v);
        // v.print("v = ");
        n += 1;
    }
    // v /= v.norm();
    return v;
}






int main(int argc, char** argv) {
    // double rmax = 10,
    
    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];
        // if(arg == "-rmax" && i+1<argc) rmax = std::stod(argv[i + 1]);
    }
    
    // matrix H = matrix(2, 2)+1;
    matrix H({{2, 5},
              {5, 3}});
    // matrix H({{1, 2},
    //           {2, 3}});
    // H.print("H = ");
    // std::cout << "\n" << std::endl;
    
    // vector col = toVector(H.getCol(1))+3;
    vector col = vector({1, 1});
    // col.print("c = ");
    
    std::function<double(vector)> R = [=](vector v){
        matrix vm = toMatrix(v);                //To make sure v can be a vector in main
        return (vm * H * vm.T())(0,0) / (v*v);  //Since toMatrix([1,1]) --> [[1,1]], vm and vm.T are swapped
    };                                          //matrix * matrix --> matrix, therefore the only element must be exracted, hence "(0,0)"
    
    // col.print("v_col = ");
    vector n = newton(R, col, H, 1e-5);
    // double R_val = R(col);
    // std::cout << R_val << "\n" << std::endl;
    // std::cout << R(n) << "\n" << std::endl;
    // n.print("v_opt1 = ");
    // double R_opt1 = R(n);
    // n /= n.norm();
    // n.print("v_opt2 = ");
    // double R_opt2 = R(n);
    // std::cout << R_opt1 << std::endl;
    // std::cout << R_opt2 << std::endl;
    
    
    // (H/R(n) * toMatrix(n).T()).print("v? = ");
    // (H/6.30283 * toMatrix(vector({0.778518, 0.627622})).T()).print("v? = ");
    // (toVector(H * toMatrix(vector({0.777993, 0.628274})).T())/6.30506).print("v? = ");


//     R = 6.30506
//     v = [0.777993, 0.628274]

    
    // int N = (int)(rmax/dr)-1;
    // std::vector<double> r(N);
    // for(int i=0;i<N;i++) r[i]=dr*(i+1);
    
    // matrix H(N, N);
    // for(int i=0; i<N-1; i++){
    //     H(i,i)  =-2*(-0.5/dr/dr);
    //     H(i,i+1)= 1*(-0.5/dr/dr);
    //     H(i+1,i)= 1*(-0.5/dr/dr);
    // }
    // H(N-1, N-1) = -2*(-0.5/dr/dr);
    // for(int i=0; i<N; i++) H(i,i) += -1/r[i];

    // EigenD EH(H);
    // EH.cyclic();

    // std::cout << rmax << "," << dr << "," << EH.D(0,0) << std::endl;

    // if(wf > 0) {
    //     std::cout << "\n\n";
    //     for(int k = 0; k < wf; k++) {
    //         matrix eVec = EH.V.getCol(k)/std::sqrt(dr);
    //         for(int i = 0; i < N; ++i) {
    //             std::cout << r[i] << "," << eVec(i,0) << "\n";
    //         }
    //         std::cout << "\n\n";
    //     }
    // }
    return 0;
}

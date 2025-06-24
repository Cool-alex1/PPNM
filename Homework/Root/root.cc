
#include"root.h"
#include<functional>
#include<exception>
#include<cmath>




// vector gradient(const std::function<double(vector)>& f, vector x){
//     double fx = f(x);
//     vector gf = vector(len(x));
//     double dxi;
//     for (int i=0; i<len(x); i++){
//         dxi = (1+std::abs(x[i]))*std::pow(2, -26);
//         x[i] += dxi;
//         gf[i] = (f(x)-fx)/dxi;
//         x[i] -= dxi;
//     }
//     return gf;
// }


matrix jacobian(const std::function<vector(vector)>& f, vector x, vector fx, vector δx){
    if(δx.isZero()){
        δx = x.copy();
        for(int i=0; i<x.len; i++) δx[i] = std::abs(x[i]) * std::pow(2, -26);
    }
    if(fx.isZero()) fx = f(x);
    matrix J(x.len, x.len);
    for (int j=0; j<x.len; j++){
        x[j] += δx[j];
        vector df = f(x) - fx;
        for (int i=0; i<x.len; i++) J(i,j) = df[i]/δx[j];
        x[j] -= δx[j];
    }
    return J;
}


// std::tuple<vector, int> newton(const std::function<vector(vector)>& f, vector start, double acc, vector δx){
vector newton(const std::function<vector(vector)>& f, vector start, double acc, vector δx){
    vector x = start.copy();
    vector z, fz, fx = f(x);
    int n = 0;
    while (1) {
        if (fx.norm() < acc) break;
        matrix J = jacobian(f, x, fx, δx);
        QR fac(J);
        fac.decomp();
        vector dx = toVector(fac.solve(-fx));
        // std::cout << x[0] << ", " << x[1] << ", " << x[2] << std::endl;
        // dx.print("");
        double λ = 1 ;
        while (λ >= 1.0/1024.0){
            z = x + λ*dx;
            fz = f(z);
            if (fz.norm() < (1-λ/2)*fx.norm()) break;
            λ /= 2.0;
        }
        x = z;
        fx = fz;
        if(n >= 200000) break;
        n += 1;
    }
    return x;
}

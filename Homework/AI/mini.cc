
// #include"QR.h"
#include"mini.h"
// #include"matrix.h"
#include<functional>
#include<exception>
#include<cmath>




vector gradient(const std::function<double(vector)>& f, vector x){
    double fx = f(x);
    vector gf = vector(len(x));
    double dxi;
    for (int i=0; i<len(x); i++){
        dxi = (1+std::abs(x[i]))*std::pow(2, -26);
        x[i] += dxi;
        // std::cout << f(x)-fx << std::endl;
        // std::cout << fx << std::endl;
        gf[i] = (f(x)-fx)/dxi;
        x[i] -= dxi;
    }
    return gf;
}


matrix hessian(const std::function<double(vector)>& f, vector x){
    matrix H(len(x), len(x));
    vector gfx = gradient(f, x);
    double dxj;
    vector dgf;
    for (int j=0; j<len(x); j++){
        dxj = (1+std::abs(x[j]))*std::pow(2, -13);
        x[j] += dxj;
        dgf = gradient(f,x)-gfx;
        for (int i=0; i<len(x); i++) H(i,j) = dgf[i]/dxj;
        x[j] -= dxj;
    }
    return H;
}


std::tuple<vector, int> newton(const std::function<double(vector)> f, vector xind, double acc){
    int n = 0;
    vector x = xind.copy();
    while (1) {
        if(n%10000 == 0){
            std::cout << "f(x) = " << f(x) << std::endl;
        }
        vector g = gradient(f, x);
        // g.print("g = ");
        if (g.norm() < acc) break;
        matrix H = hessian(f, x);
        QR fac(H);
        fac.decomp();
        vector dx = toVector(fac.solve(-g));
        // std::cout << x[0] << ", " << x[1] << ", " << x[2] << std::endl;
        // dx.print("");
        double λ = 1 ;
        while (λ >= 1.0/1024.0){
            if (f(x + λ*dx) < f(x)) break;
            λ /= 2.0;
        }
        x += λ*dx;
        n += 1;
    }
    return std::make_tuple(x, n);
}
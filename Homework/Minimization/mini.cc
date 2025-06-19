
#include"QR.h"
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


std::tuple<vector, int> newton(const std::function<double(vector)>& f, vector x, double acc=1e-1){
    int n = 0;
    while (1) {
        vector g = gradient(f, x);
        // g.print("");
        if (g.norm() < acc) break;
        matrix H = hessian(f, x);
        QR fac(H);
        fac.decomp();
        vector dx = toVector(fac.solve(-g));
        // std::cout << x[0] << ", " << x[1] << std::endl;
        // dx.print("");
        double λ = 1 ;
        while (λ >= 1.0/1024){
            if (f(x + λ*dx) < f(x)) break;
            λ /= 2;
        }
        x += λ*dx;
        n += 1;
    }
    return std::make_tuple(x, n);
}
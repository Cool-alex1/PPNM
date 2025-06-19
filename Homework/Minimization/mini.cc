
#include"QR.h"
// #include"matrix.h"
#include<exception>
#include<cmath>





vector newton(const std::function<double(vector)>& f, vector x, double acc=1e-3){
    while 1 {
        vector g = gradient(f, x);
        if (g.norm() < acc) break;
        matrix H = hessian(φ, x);
        QR fac(H);
        vector dx = toVector(fac.decomp().solve(-g));
        double λ = 1 ;
        while (λ >= 1/1024){
            if (f(x + λ*dx) < f(x)) break;
            λ /= 2;
        }
        x = x + λ*dx;
    }
    return x;
}



vector gradient(const std::function<double(double)>& f, vector x){
    double fx = f(x);
    vector gf = vector(len(x))
    double dxi;
    for (int i=0; i<len(x); i++){
        dxi = (1+abs(x[i]))*2**(-26);
        x[i] += dxi;
        gf[i] = (f(x)-fx)/dxi;
        x[i] -= dxi;
        return gf
    }
}


matrix hessian(const std::function<double(double)>& f, vector x){
    matrix H(len(x), len(x));
    vector gfx = gradient(f, x);
    double dxj;
    vector dgf;
    for (int j=0; j<len(x); j++){
        dxj = (1+abs(x[j]))*2**(-13);
        x[j] += dxj;
        dgf = gradient(φ,x)-gfx;
        for (int i=0; i<len(x); i++) H(i,j) = dgf[i]/dxj;
        x[j] -= dxj;
    }
    return H
}


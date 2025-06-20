
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


std::tuple<vector, int> newton(const std::function<double(vector)>& f, vector x, double acc){
    int n = 0;
    while (1) {
        vector g = gradient(f, x);
        // g.print("");
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




std::tuple<vector, matrix> GH2(const std::function<double(vector)>& f, vector x){
    int l = len(x);
    double fx = f(x);
    vector dx = vector(l);
    vector gf = vector(l);
    vector fm = vector(l);
    vector fp = vector(l);
    matrix hess(l, l);
    for (int i=0; i<l; i++){
        dx[i] = (1+std::abs(x[i]))*std::pow(2, -26);
        
        fm[i] = f(x-dx.unit(i));
        fp[i] = f(x+dx.unit(i));

        gf[i] = (fp[i]-fm[i])/(2*dx[i]);
        hess(i,i) = (fp[i] - 2*fx + fm[i])/(dx[i]*dx[i]);
    }

    double fpp;
    double fpm;
    double fmp;
    double fmm;
    for (int i=0; i<l; i++){
        for (int j=i+1; j<l; j++){
            fpp = f(x + dx.unit(i) + dx.unit(j));
            fpm = f(x + dx.unit(i) - dx.unit(j));
            fmp = f(x - dx.unit(i) + dx.unit(j));
            fmm = f(x - dx.unit(i) - dx.unit(j));
            hess(i,j) = (fpp - fpm - fmp + fmm) / (4*dx[i]*dx[j]);
            hess(j,i) = hess(i,j);
        }
    }

    return std::make_tuple(gf, hess);
}



std::tuple<vector, int> newton2(const std::function<double(vector)>& f, vector x, double acc){
    int n = 0;
    while (1) {
        
        std::tuple<vector, matrix> GH = GH2(f, x);
        vector g = std::get<0>(GH);
        if (g.norm() < acc) break;

        matrix H = std::get<1>(GH);
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
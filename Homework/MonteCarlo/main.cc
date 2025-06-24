#include<iostream>
#include<functional>
#include<tuple>
#include<cmath>
#include<fstream>
#include<random>
#include"vector.h"


std::tuple<double, double> plainmc(const std::function<double(vector)>& f, vector a, vector b, int N){
    int dim = a.len;
    double V = 1;
    double sum = 0, sum2 = 0;

    vector x(dim);
    double fx;

    std::default_random_engine re;
    std::vector<std::uniform_real_distribution<double>> unifs(a.len);
    for(int i = 0; i < dim ; i++) {
        unifs[i] = std::uniform_real_distribution<double>(a[i],b[i]);
        V *= b[i] - a[i];
    } 
    for(int i=0; i<N; i++){
        for(int k=0; k<dim; k++){x[k] = unifs[k](re);}
        
        fx = f(x);
        sum  += fx;
        sum2 += fx*fx;
    }

    double mean = sum/N;
    double σ = std::sqrt(sum2/N - mean*mean);
    return std::make_tuple(mean*V, σ*V/std::sqrt(N));
}



double halton(int i, int b){
    double f = 1, r = 0;
    while (i > 0){
        f /= b;
        r += f * (i%b);
        i = std::floor(i/b);
    }
    return r;
}


std::tuple<double, double> quasimc(const std::function<double(vector)>& f, vector a, vector b, int N){
    int dim = a.len;
    double V = 1;
    for(int i = 0; i < dim ; i++) {V *= b[i] - a[i];} 
    double sum = 0, sum2 = 0;
    
    vector bases({2, 3, 5, 7, 11, 13, 17, 19});
    vector x(dim);
    
    for(int i=0; i<N; i++){
        for(int k=0; k<dim; k++){x[k] = a[k] + halton(i, bases[k]) * (b[k] - a[k]);}
        sum  += f(x);
        
        for(int k=0; k<dim; k++){x[k] = a[k] + halton(i + N, bases[k]) * (b[k] - a[k]);}
        sum2  += f(x);
    }
    
    double mean = sum/N;
    return std::make_tuple(mean*V, V/N * std::abs(sum - sum2));
}




std::tuple<double, double> stratmc(const std::function<double(vector)>& f, vector a, vector b, int N, int nmin){
    if(N < nmin) return plainmc(f, a, b, N);


    int dim = a.len;
    double V = 1;
    double sum = 0;

    std::vector<int> n_l(dim), n_r(dim);
    vector mean_l(dim), mean_r(dim);
    vector x(dim);
    double fx;

    std::default_random_engine re;
    std::vector<std::uniform_real_distribution<double>> unifs(a.len);
    for(int i = 0; i < dim ; i++) {
        unifs[i] = std::uniform_real_distribution<double>(a[i],b[i]);
        V *= b[i] - a[i];
    } 
    for(int i=0; i<N; i++){
        for(int k=0; k<dim; k++){x[k] = unifs[k](re);}
        fx = f(x);
        sum  += fx;
        
        for(int k=0; k<dim; k++){
            if(x[k] > (b[k] + a[k])/2){
                n_r[k]++;
                mean_r[k] += fx;
            } else {
                n_l[k]++;
                mean_l[k] += fx;
            }
        }

    }
    // double mean = sum/N;
    for(int k=0; k<dim; k++){
        mean_l[k] /= n_l[k];
        mean_r[k] /= n_r[k];
    }
    
    int kmax = 0;
    double maxvar = 0;
    for(int k=0; k<dim; k++){
        double var = std::abs(mean_l[k] - mean_r[k]);
        if(var > maxvar){
            maxvar = var;
            kmax = k;
        }
    }

    vector a_r = a.copy(), b_l = b.copy();
    a_r[kmax] = (b[kmax] + a[kmax]) / 2;
    b_l[kmax] = (b[kmax] + a[kmax]) / 2;


    int N_l = n_l[kmax];
    int N_r = n_r[kmax];

    std::tuple<double, double> res_l, res_r;


    res_l = stratmc(f, a, b_l, N_l, nmin);
    res_r = stratmc(f, a_r, b, N_r, nmin);
 

    double err_l = std::get<1>(res_l);
    double err_r = std::get<1>(res_r);

    double q = std::get<0>(res_l) + std::get<0>(res_r);
    double err = std::sqrt(err_l*err_l + err_r*err_r);
    return std::make_tuple(q, err);
}









auto f_const = [](vector x){return 1;};
auto f_ucirc = [](vector x){
    if(x.norm() <= 1.0) return 1;
    else return 0;
};
auto f_coses = [](vector x) {
    if((0 <= x[0] && x[0] <= M_PI) &&
    (0 <= x[1] && x[1] <= M_PI) &&
    (0 <= x[2] && x[2] <= M_PI)) return std::pow(M_PI,-3) * 1/(1 - std::cos(x[0])*std::cos(x[1])*std::cos(x[2]));
    return 0.0;
};

auto f_gauss2d = [](vector x) {
    return std::exp(-std::pow(x[0] - 1.0, 2)/2 - std::pow((x[1] - 0.5)/0.5, 2)/2);
};









int main(int argc, char** argv) {
    std::string opg = " ";
    std::string Npow = "1";
    for(int i = 0; i < argc ; ++i) {
        std::string arg = argv[i];
        if(arg == "--opg" && i+1 < argc) opg = argv[i + 1];
        if(arg == "--Npow" && i+1 < argc) Npow = argv[i + 1];
    }
    if(opg == " "){
        std::cout << "The tasks have here been split into the three out.txt filet:\n" <<
        "  Out_A.txt - Containing tast A, using plain monte carlo on some examples\n" <<
        "  Out_B.txt - Containing tast B, using quasi monte carlo on an example\n" <<
        "  Out_C.txt - Containing tast C, comparing the usage plain monte carlo and stratified sampling on the 2d gaussian function\n" << std::endl;
    }

    

    // A)
    if(opg == "A"){
        vector a,b;
        int N;
        double q,err;
        double q_ana;
        std::tuple<double,double> res;
        if(Npow == "1"){

            /* Constant function */
            a = vector({-1, -1, -1});
            b = vector({1, 1, 1});
            N = 1000;
            res = plainmc(f_const, a, b, N);
            q = std::get<0>(res);
            err = std::get<1>(res);
            q_ana = 8;
            
            std::cout << "Cube:\n"; 
            std::cout << "∫_-1^1∫_-1^1∫_-1^1 1 = " << q << " +/- " << err << "\n"; 
            std::cout << "With " << N << " samples\n";
            std::cout << "Expected result = "<< q_ana << "\n";
            std::cout << "Actual err = "<< std::abs(q-q_ana) << "\n\n\n";
            
            
            /* unit circle */
            a = vector({-1, -1});
            b = vector({1, 1});
            N = 100000;
            res = plainmc(f_ucirc, a, b, N);
            q = std::get<0>(res);
            err = std::get<1>(res);
            q_ana = M_PI;

            std::cout << "Unit circle:\n"; 
            std::cout << "∫ unit circle = " << q << " +/- " << err << "\n"; 
            std::cout << "With " << N << " samples\n";
            std::cout << "Expected result = "<< q_ana << "\n";
            std::cout << "Actual err = "<< std::abs(q-q_ana) << "\n\n\n";


            /* unit sphere */
            a = vector({-1.05, -1.05, -1.05});
            b = vector({1.05, 1.05, 1.05});
            N = 100000;
            res = plainmc(f_ucirc, a, b, N);
            q = std::get<0>(res);
            err = std::get<1>(res);
            q_ana = 4.0/3.0*M_PI;

            std::cout << "Unit circle:\n"; 
            std::cout << "∫ unit sphere = " << q << " +/- " << err << "\n"; 
            std::cout << "With " << N << " samples\n";
            std::cout << "Expected result = "<< q_ana << "\n";
            std::cout << "Actual err = "<< std::abs(q-q_ana) << "\n\n\n";



            /* unit 4D sphere */
            a = vector({-1.01, -1.01, -1.01, -1.01});
            b = vector({1.01, 1.01, 1.01, 1.01});
            N = 100000;
            res = plainmc(f_ucirc, a, b, N);
            q = std::get<0>(res);
            err = std::get<1>(res);
            q_ana = M_PI*M_PI/2;

            std::cout << "Unit circle:\n"; 
            std::cout << "∫ unit sphere 4D = " << q << " +/- " << err << "\n"; 
            std::cout << "With " << N << " samples\n";
            std::cout << "Expected result = "<< q_ana << "\n";
            std::cout << "Actual err = "<< std::abs(q-q_ana) << "\n\n\n";



            /* Integral */
            a = vector({0, 0, 0});
            b = vector({M_PI, M_PI, M_PI});
            N = 10000000;
            res = plainmc(f_coses, a, b, N);
            q = std::get<0>(res);
            err = std::get<1>(res);
            q_ana = 1.3932039296856768591842462603255;

            std::cout << "Unit circle:\n"; 
            std::cout << "∫_0^π∫_0^π∫_0^π 1/π^3 * [1-cos(x)cos(y)cos(z)]^-1 = " << q << " +/- " << err << "\n"; 
            std::cout << "With " << N << " samples\n";
            std::cout << "Expected result = "<< q_ana << "\n";
            std::cout << "Actual err = "<< std::abs(q-q_ana) << "\n\n\n";



        } else {
            /* unit circle graph*/
            a = vector({-1, -1});
            b = vector({1, 1});
            N = 1000 * std::pow(1.2, stod(Npow));
            res = plainmc(f_ucirc, a, b, N);
            q = std::get<0>(res);
            err = std::get<1>(res);
            q_ana = M_PI;
            
            std::cout << N << " " << err << " " << std::abs(q-q_ana) << std::endl; 
        }
    }
    
    
    
    if(opg == "B"){
        vector a,b;
        int N;
        double q,err;
        double q_ana;
        std::tuple<double,double> res;

        if(Npow == "1"){
            /* unit circle */
            a = vector({-1, -1});
            b = vector({1, 1});
            N = 100000;
            res = quasimc(f_ucirc, a, b, N);
            q = std::get<0>(res);
            err = std::get<1>(res);
            q_ana = M_PI;

            std::cout << "Using quasi-random sequences\n"; 
            std::cout << "Unit circle:\n"; 
            std::cout << "∫ unit circle = " << q << " +/- " << err << "\n"; 
            std::cout << "With " << N << " samples\n";
            std::cout << "Expected result = "<< q_ana << "\n";
            std::cout << "Actual err = "<< std::abs(q-q_ana) << "\n\n\n";
            
            
        } else {
            
            /* unit circle graph*/
            a = vector({-1, -1});
            b = vector({1, 1});
            N = 1000 * std::pow(1.2, stod(Npow));
            res = quasimc(f_ucirc, a, b, N);
            q = std::get<0>(res);
            err = std::get<1>(res);
            q_ana = M_PI;
            
            std::cout << N << " " << err << " " << std::abs(q-q_ana) << std::endl; 
            
        }
    }
        
        
    if(opg == "C"){
        vector a,b;
        int N;
        double q,err;
        double q_ana;
        std::tuple<double,double> res;

        a = vector({-15, -15});
        b = vector({15, 15});
        N = 10000000;
        res = plainmc(f_gauss2d, a, b, N);
        q = std::get<0>(res);
        err = std::get<1>(res);
        q_ana = M_PI;
    
        std::cout << "2d gauss with center (1, 0.5) and standard deviations (1, 0.5):\n"; 
        std::cout << "Using plain MC:\n"; 
        std::cout << "∫ 2d gauss = " << q << " +/- " << err << "\n"; 
        std::cout << "With " << N << " samples\n";
        std::cout << "Expected result = "<< q_ana << "\n";
        std::cout << "Actual err = "<< std::abs(q-q_ana) << "\n\n\n";
        


        a = vector({-15, -15});
        b = vector({15, 15});
        N = 10000000;
        res = stratmc(f_gauss2d, a, b, N, 1000);
        q = std::get<0>(res);
        err = std::get<1>(res);
        q_ana = M_PI;
    
        std::cout << "Using Stratified sampling:\n"; 
        std::cout << "∫ 2d gauss = " << q << " +/- " << err << "\n"; 
        std::cout << "With " << N << " samples\n";
        std::cout << "Expected result = "<< q_ana << "\n";
        std::cout << "Actual err = "<< std::abs(q-q_ana) << "\n\n\n";
    }

    return 0;
}
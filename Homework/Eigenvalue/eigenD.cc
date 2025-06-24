#include<cmath>
#include"matrix.h"
#include"eigenD.h"

void EigenD::timesJ(matrix& A, int p, int q, double Φ){
    double c=cos(Φ), s=sin(Φ);
	for(int i=0; i<A.nRow; ++i){
		double aip=A(i,p), aiq=A(i,q);
		A(i,p) = c*aip - s*aiq;
		A(i,q) = s*aip + c*aiq;
		}
}

void EigenD::Jtimes(matrix& A, int p, int q, double Φ){
    double c=cos(Φ), s=sin(Φ);
	for(int j=0; j<A.nRow; ++j){
		double aip=A(p,j), aiq=A(q,j);
		A(p,j) = c*aip + s*aiq;
		A(q,j) = -s*aip + c*aiq;
		}
}

void EigenD::cyclic(){
    bool changed = true;
    while(changed){
        changed = false;
        for(int p=0; p<D.nRow; ++p){
            for(int q=p+1; q<D.nRow; ++q){
                double apq=D(p,q), app=D(p,p), aqq=D(q,q);
                double theta = 0.5*atan2(2*apq, aqq-app);
                double c=cos(theta), s=sin(theta);
                double new_app = c*c*app - 2*s*c*apq + s*s*aqq;
                double new_aqq = s*s*app + 2*s*c*apq + c*c*aqq;
                if(new_app != app || new_aqq != aqq) // do rotation
                {
                    changed=true;
                    timesJ(D,p,q, theta); // A←A*J 
                    Jtimes(D,p,q,-theta); // A←JT*A 
                    timesJ(V,p,q, theta); // V←V*J
                    }
            }
        }
    }
}


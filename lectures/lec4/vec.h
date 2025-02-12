// #include<iostream>
// #include<string>
#ifndef HAVE_VEC_H
#define HAVE_VEC_H
// struct vec{
// 	double x,y,z;
// 	vec(double x,double y,double z): x(x),y(y),z(z){}
// 	vec():vec(0,0,0){}
// 	vec(const vec&)=default;
// 	vec(vec&&)=default;
// 	~vec()=default;
// 	vec& operator=(const vec&)=default;
// 	vec& operator=(vec&&)=default;
// 	vec& operator+=(const vec&);
// 	vec& operator-=(const vec&);
// 	vec& operator*=(double);
// 	vec& operator/=(double);
// 	void set(double a,double b,double c){x=a;y=b;z=c;}
// 	void print(std::string s="") const;
// 	friend std::ostream& operator<<(std::ostream& os, const vec& v);  //friend giver adgang til x, y og z
// };
// vec operator-(const vec&);
// vec operator-(const vec&, const vec&);
// vec operator+(const vec&, const vec&);
// vec operator*(const vec&, double);
// vec operator*(double, const vec&);
// vec operator/(const vec&, double);
// bool approx(const vec&, const vec&, double acc=1e-6,double eps=1e-6);
struct vec {
    double x, y, z;
};
#endif

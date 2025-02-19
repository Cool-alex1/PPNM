#include"vec.h"
#include<iostream>
#include<random>
int main(){
	std::mt19937 gen(0);
	std::uniform_real_distribution<double> dist(-1.0, 1.0);
	
	vec u,v,test;
	u.set(dist(gen),dist(gen),dist(gen));
	v.set(dist(gen),dist(gen),dist(gen));
	u.print("u= ");
	v.print("v= ");
	std::cout << "u=" << u << std::endl;
	std::cout << "v=" << v << std::endl;

	test.set(-u.x,-u.y,-u.z);
	(-u).print("-u  = ");
	test.print("test= ");
	if(approx(-u,test))std::cout << "\ntest 'unary -' passed\n" << std::endl;

	test.set(u.x+v.x,u.y+v.y,u.z+v.z);
	(u+v).print("u+v = ");
	test.print ("test= ");
	if(approx(u+v,test))std::cout << "test '+' passed\n" << std::endl;

	test.set(u.x-v.x,u.y-v.y,u.z-v.z);
	(u-v).print("u-v = ");
	test.print   ("test= ");
	if(approx(u-v,test))std::cout << "test '-' passed\n" << std::endl;

}
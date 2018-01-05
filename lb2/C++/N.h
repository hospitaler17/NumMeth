#include<iostream>
#include<cstdlib>
#include<cmath>

using namespace std;

class Newton{
	double x[2],temp_x[2],x_k1[2];
	double e[2];
	int NIT;
	int k;
	double F[2];
	double d[2];
	double A[2][2];
	int max,cur,n;
    public:
	Newton();
	double function1();
	double function2();
	double derivative11();
	double derivative12();
	double derivative21();
	double derivative22();
	void calcSLAU();
	int checkUsl();
	void findMax();
	void swap();
	void func();
	void func2();
	void work();
};

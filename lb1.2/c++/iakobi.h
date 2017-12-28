#include<iostream>
#include<cstdlib>
#include<cmath>
#include<fstream>
#include<ctime>
#include<cstring>

using namespace std;

class Slau{
	float **A,*Y,*X,*tempX;
	int n,iter;
    public:
	Slau();
	int readfile(char *fn);
	int checkUslovie();
	void findX(int method);
	void func(float E,int method);
	int reshenie(float E);
	void showMatrix();
        void showResult();
};

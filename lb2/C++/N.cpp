#include "N.h"
Newton::Newton(){
	e[0]=e[1]=pow(10,-9);
	k=1;
	n=2;
}
double Newton::function1() {
    	return (x[0]*x[0]-x[1]*x[1]-1);
}
double Newton::function2() {
    	return (x[0]*x[1]*x[1]*x[1]-x[1]-3);
}
double Newton::derivative11() {
    	return (2*x[0]);
}
double Newton::derivative12() {
    	return (2*x[1]);
}
double Newton::derivative21() {
    	return (x[1]*x[1]*x[1]);
}
double Newton::derivative22() {
    	return (3*x[0]*x[1]*x[1]-1);
}
void Newton::calcSLAU(){
	cur=max=0;
	A[0][0]=derivative11();
	A[0][1]=derivative12();
	A[1][0]=derivative21();
	A[1][1]=derivative22();
	F[0]=-1*function1();
	F[1]=-1*function2();
	for(;cur<n-1;++cur){
		swap();
		func();
		}
	for(;cur>=0;--cur){
		func2();
		}
	x_k1[0]=x[0]+temp_x[0];
	x_k1[1]=x[1]+temp_x[1];
	}
void Newton::findMax(){
	max=cur;
	for(int i=cur;i<n;++i){
		if(fabs(A[max][cur])<fabs(A[i][cur]))max=i;
		}
	}
void Newton::swap(){
	double temp;
	findMax();
	if(cur!=max){
		for(int i=cur;i<n;++i){
			temp=A[max][i];
			A[max][i]=A[cur][i];
			A[cur][i]=temp;
			}
		temp=F[max];
		F[max]=F[cur];
		F[cur]=temp;		
		}
	temp=A[cur][cur];
	for(int i=cur;i<n;++i){
		for(int j=cur;j<n;++j){
			A[i][j]/=temp;
			}
		F[i]/=temp;
		}
	}
void Newton::func(){
	double temp;
	for(int j=1;cur+j<n;++j){
		temp=A[cur+j][cur];
		for(int i=cur;i<n;++i){
			A[cur+j][i]-=A[cur][i]*temp;
			}
		F[cur+j]-=F[cur]*temp;
		}
	}
void Newton::func2(){
	double F1=F[cur];
	if(n!=cur){
		for(int i=n-1;i>cur;--i){
			F1-=A[cur][i]*temp_x[i];
			}
		}
	temp_x[cur]=F1/A[cur][cur];
	}
int Newton::checkUsl(){
	double temp;
	if(fabs(function1())>fabs(function2()))d[0]=fabs(function1());
	else d[0]=fabs(function2());
    	if (fabs(x_k1[0]) < 1) {
        	d[1] = fabs(x_k1[0] - x[0]);
    		}
    	else {
        	d[1] = fabs((x_k1[0] - x[0])/x_k1[0]);
    		}
    	if (fabs(x_k1[1]) < 1) {
        	temp = fabs(x_k1[1] - x[1]);
    		}
    	else {
        	temp = fabs((x_k1[1] - x[1])/x_k1[1]);
    		}
    	if (temp > d[1]) {
        	d[1] = temp;
    		}
	cout<<k<<" | "<<d[0]<<" | "<<d[1]<<" |"<<endl;
	if(d[0]<=e[0] && d[1]<=e[1])return 1;
	else return 0;
	}
void Newton::work(){
	cout<<"Введите начальное приближение:"<<endl;
	cout<<"x[0] = ";
	cin>>x[0];
	cout<<endl<<"x[1] = ";
	cin>>x[1];
	cout<<endl;
	cout<<"Введите максимальное количество итераций:"<<endl;
	cout<<"NIT = ";
	cin>>NIT;
	cout<<endl;
	cout<<"k |   d1   |   d2   |"<<endl;
	while(1){
		calcSLAU();
		if(checkUsl())break;
		if(k>=NIT){cout<<"IER=2"<<endl;break;}
		++k;
		x[0]=x_k1[0];
		x[1]=x_k1[1];
		}
	}

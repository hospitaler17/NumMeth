#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
class interpolation {
	double* x;
	double* y;
	int N;
public:
	void readfile(const char* name_file);
	void lagrange(double X);
	void newton(double X);
};


void interpolation:: readfile(const char* name_file){
	int i=0;
	N=0;
	double num;
	ifstream fin;
	fin.open(name_file, ios::app);
	if(!fin){
		cout<<"Ошибка при чтении из файла!"<<endl;
		exit(1);
	}
	fin>>num;
	N++;
	while(!fin.eof()){
		fin>>num;
		N++	;
	}
	N=N/2;
	fin.close();
	fin.open(name_file, ios::app);
	x= new double[N];
	y= new double[N];
	fin>>x[i];
	while(!fin.eof()){
		fin>>y[i];
		++i;
		fin>>x[i];
	}

}

void interpolation::lagrange(double X){
	double result=0;
	std::cout << "Метод Лагранжа: " << '\n';
	for(int i=0;i<N;i++){
		double temp=y[i];
		for(int j=0;j<N;j++){
			if(i==j) continue;
			temp*=(X-x[j])/(x[i]-x[j]);
		}
		result+=temp;
	}
	cout<<"Ответ: "<<result<<endl;
	std::cout << "==============================" << '\n';
}
void interpolation::newton(double X) {
	double f[N][N];
	double result=y[0];
	std::cout << "Метод Ньютона: " << '\n';
	for(int i=0;i<N;i++){
		f[0][i]=y[i];
	}
	double t =1;
	for(int i=1;i<N;i++){
		for(int j=0;j<N-i;j++){
			f[i][j]=(f[i-1][j+1]-f[i-1][j])/(x[j+i]-x[j]);
		}
		t*= X-x[i-1];
		result+=f[i][0]*t;
	}
	cout<<"Ответ: "<<result <<endl;
	std::cout << "==============================" << '\n';
}

 int main() {
 	interpolation object;
	int n;
	char filename[20];
	double X;
	cout<<"Введите имя файла с точками:\n>>> ";
	cin>>filename;
	object.readfile(filename);
	cout<<"Введите значение X:\n>>> ";
	cin>>X;
	std::cout << "==============================" << '\n';
	object.newton(X);
 	object.lagrange(X);

 	return 0;
 }

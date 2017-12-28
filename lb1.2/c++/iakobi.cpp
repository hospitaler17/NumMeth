#include"iakobi.h"

Slau::Slau(){
	n=0;
	iter=0;
	}

int Slau::readfile(char *fn){
	ifstream file(fn);
	if(!file){
	cout<<"Файл не найден!"<<endl;
	return 1;
	}
	bool check=false;
	bool start=false;
	char ch=0,ch2=0;
	string str="";
	int stroka=0,stolbez=0;
	if(file.eof())return 1;
	cout<<"Введите количество уравнений:";
	cin>>n;
	X=new float [n+1];
	tempX=new float [n+1];
	for(int i=0;i<n;++i)tempX[i]=0;
	Y=new float [n+1];
	A=new float *[n+1];
	for(int i=0;i<n+1;++i)A[i]=new float[n+1];
	while(!file.eof()){
		ch=0;
		while(ch!=10){
			file.read((char*)&ch,1);
			if(file.eof()){
				break;
				}
			if(((ch==10 || ch==32) && (ch2==10 || ch2==32)) || ((ch==46 && (ch2!=32 || ch2!=10)) && start==true)){
				cout<<"Неверный формат СЛАУ!"<<endl;
				return 1;			
				}
			else if(ch2==46 && (ch==10 || ch==32)){
				cout<<"Неверный формат СЛАУ!"<<endl;
				return 1;
				}
			if((ch>='0' && ch<='9')||(ch==45)){str+=ch;ch2=ch;}
			else if(ch==32 || ch==10){
					if(ch==10 && stolbez!=n){
							cout<<"Неверный формат СЛАУ!"<<endl;
							return 1;
						}
					else if(stolbez==n){
								if(str[str.size()-1]==46){							
									cout<<"Неверный формат СЛАУ!"<<endl;
									return 1;
									}
								Y[stroka]=atof(str.c_str());
								stolbez=0;
								++stroka;
								ch2=ch;
								}
						else {
							if(str[str.size()-1]==46){							
								cout<<"Неверный формат СЛАУ!"<<endl;
								return 1;
								}
							A[stroka][stolbez]=atof(str.c_str());
							++stolbez;
							ch2=ch;
							}
						str="";
						check=false;
						}
				else if(ch==46){
						str+=ch;
						ch2=ch;
						if(check){
							cout<<"Неверный формат СЛАУ!"<<endl;
							return 1;
							}
						else check=true;
						}
					else {
						cout<<"Неверный формат СЛАУ!"<<endl;
						return 1;
					}
			start=true;
			}
		}
	return 0;
	}
int Slau::checkUslovie(){
	float num=0,sum=0;
	for(int i=0;i<n;++i){
		num=fabs(A[i][i]);
		for(int j=0;j<n;++j)if(i!=j)sum+=fabs(A[i][j]);
		if(num<sum)return 1;
		sum=0;
		}
	return 0;
	}
void Slau::findX(int method){
	if(method==1){
		for(int i=0;i<n;++i){
			X[i]=Y[i];
			for(int j=0;j<n;++j){
				if(i!=j)X[i]-=A[i][j]*tempX[j];
				}
			X[i]/=A[i][i];
			}
		}
	if(method==2){
		for(int i=0;i<n;++i){
			X[i]=Y[i];
			for(int j=0;j<i;++j){
				if(i!=j)X[i]-=A[i][j]*X[j];
				}
			for(int j=i;j<n;++j){
				if(i!=j)X[i]-=A[i][j]*tempX[j];
				}
			X[i]/=A[i][i];
			}		
		}
	}
void Slau::func(float E,int method){
	float max=0;
	while(1){
		findX(method);
		++iter;
		max=fabs(X[0]-tempX[0]);
		for(int i=1;i<n;++i){
			if(max<fabs(X[i]-tempX[i]))max=fabs(X[i]-tempX[i]);
			}
		if(max<E)return;
		for(int i=0;i<n;++i)tempX[i]=X[i];
		}
	}
int Slau::reshenie(float E){
	if(checkUslovie()){
		cout<<"Не выполнено условие диагонального преобладания!"<<endl;
		return 1;
		}
	showMatrix();
	func(E,1);
	cout<<"Метод Якоби:"<<endl;
	showResult();
	for(int i=0;i<n;++i)tempX[i]=0;
	iter=0;
	func(E,2);
	cout<<"Метод Гаусса-Зейделя:"<<endl;
	showResult();	
	return 0;
	}
void Slau::showMatrix(){
	cout<<endl<<"СЛАУ:"<<endl;
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<A[i][j]<<"*X"<<j+1<<"  ";
			}
		cout<<"  =  "<<Y[i]<<endl;
		}
	cout<<endl;
	}
void Slau::showResult(){
	cout<<endl<<"Result:"<<endl;
	for(int i=0;i<n;++i){
		cout<<"X"<<i+1<<" = "<<X[i]<<endl;
		}
	cout<<"Количество итераций:"<<iter<<endl;
	cout<<endl;
	}

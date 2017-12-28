#include"iakobi.h"

int main(){
	char *fn=new char [25];
	float E;
	cout<<"Введите имя файла:"<<endl;
	cin>>fn;
	Slau ob;
	if(ob.readfile(fn))return 1;
	cout<<"Введите точность E:"<<endl;
	cin>>E;
	if(ob.reshenie(E))return 1;
	}

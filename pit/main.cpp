/*  линейное уравнение (уравнение прямой) Ax+By+C=0  */
/* при этом (y1-y2)*x + (x2-x1)*y + (x1*y2-x2*y1) = 0 */
/* y = (Ax+C)/B */

/*==============================================================================*/
#include <iostream>
#include <fstream>

#define  N 100


using namespace std;

int main (int argc, char** argv) {
	int i, j, count = 0;// счетчики
	long double X, Y; // х и у для обработки
	long double arrX[N], arrY[N];
	char name[] = "dots.txt"; // имя входного файла
	fstream f; // файл
	f.open (name, ios_base::in); // блок открытия файла
	if (!f.is_open()) { // проверка файла
		cerr << "Не удалось открыть файл!\n";
		return 0;
	}
	else
		cout << "Файл "<< name << " успешно открыт!" << '\n';
	while (!f.eof()) {
		f >> arrX[count];
		f >> arrY[count];
		count++;
		std::cout << "Найдена точка ( " <<arrX[count]<< " \t, "<< arrY[count] <<" )\n";
	}
	count--;// из-за перехода на след строку(
	std::cout << "Всего точек "<< count << '\n';
	//f.clear();// отчистим поток
	//f.seekg(0);// двинемся в начало файла
	f.close();
	//long double *arrX = new long double[i];// массив для хранения точек
	//long double *arrY = new long double[i];
	for (i = 0; i < count; i++)
		std::cout << "Найдена точка ( " <<X<< " \t, "<<Y<<" )\n";
	std::cout << "Точки загружены в память" << '\n';
	while (true) { // сортировка
		i=0;
		for (j = 0; j < count; j++) {
			if(arrX[j] > arrX[j+1]) {
				X = arrX[j];
				Y = arrY[j];
				arrX[j] = arrX[j+1];
				arrY[j] = arrY[j+1];
				arrX[j+1] = X;
				arrY[j+1] = Y;
				i=1;
			}
		}
		if(i == 0)
			break;
	}
	for (i = 0; i < count; i++) {
		std::cout <<i+1<< ": ( " << X << " \t, "<<Y<<" )\n";
	}
	//delete[] arrX, arrY;

}
//TODO: сделать анализатор для чисел из файла
//TODO: сделать анализатор для числа икс от пользовалеля
//TODO: Написать меню
//TODO: разобратся с графиком
//TODO: написать функцию-сортировку по Х

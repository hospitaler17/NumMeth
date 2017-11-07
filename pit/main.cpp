/*  линейное уравнение (уравнение прямой) Ax+By+C=0  */
/* при этом (y1-y2)*x + (x2-x1)*y + (x1*y2-x2*y1) = 0 */
/* y = (Ax+C)/B */

/*==============================================================================*/
#include <iostream>
#include <fstream>

using namespace std;

long double findY(long double X1, long double Y1, long double X2, long double Y2, long double X){
	long double A, B, C;
	A = Y1 - Y2;
	B = X2 - X1;
	C = X1*Y2 - X2*Y1;
	std::cout << "A = "<< A <<", B = "<< B <<", C = "<< C << '\n';
	return ((A*X+C)/B)*(-1);
}

int main (int argc, char** argv) {
	int i, ch, j, count = 0;// счетчики
	long double X, Y; // х и у для обработки
	char name[] = "dots.txt"; // имя входного файла
	ifstream f; // файл
	f.open (name); // блок открытия файла
	if (!f.is_open()) { // проверка файла
		cerr << "Не удалось открыть файл!\n";
		return 0;
	}
	else
		cout << "Файл "<< name << " успешно открыт!" << '\n';
	while (!f.eof()) {
		f >> X;
		f >> Y;
		count++;
	}
	count--;// из-за перехода на след строку(
	std::cout << "Всего точек "<< count << '\n';
	f.clear();// отчистим поток
	f.seekg(0);// двинемся в начало файла

	long double *arrX = new long double[count];// массив для хранения точек
	long double *arrY = new long double[count];
	for (i = 0; i < count; i++) {
		f >> arrX[i];
		f >> arrY[i];
	}
	f.close();
	for (i = 0; i < count; i++)
		std::cout << "Найдена точка ( " <<arrX[i]<< " ,\t "<<arrY[i]<<" \t)\n";
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
		std::cout <<i+1<< ": ( " << arrX[i] << " ,\t "<<arrY[i]<<" \t)\n";
	}
	std::cout << "Точки отсортированы" << '\n';
	while (true) {
		std::cout << "+++++++++++++++++++++++++++++++++++++++++" << '\n';
		std::cout << "1: Найти Y по X" << '\n';
		std::cout << "2: Нарисовать график" << '\n';
		std::cout << "0: Выход" << '\n';
		std::cout << "+++++++++++++++++++++++++++++++++++++++++" << '\n'<< "> ";
		std::cin >> ch;
		switch (ch) {
			case 1:// считаем!
				std::cout << "X может принимать значение от "<< arrX[0] << " до "<< arrX[count-1] << '\n';
				std::cout << "Введите X: ";
				std::cin >> X;
				if(X < arrX[0] || X > arrX[count]){
					std::cout << "Данный X не входит в интервал точек!" << '\n';
					break;
				}
				for (i = 0; i < count; i++) {
					if(arrX[i] > X){
						std::cout << "X = "<< X <<" находится в интервале между точками ";
						std::cout << "("<< arrX[i-1]<<", "<<arrY[i-1] <<") и ("<< arrX[i]<<", "<<arrY[i] <<")"<< '\n';
						Y = findY (arrX[i-1], arrY[i-1], arrX[i], arrY[i], X);
						std::cout << "Ответ:   Y = "<< Y << '\n';
						break;
					}
				}
				break;
			case 2:// Рисуем график
				std::cout << "Пока не работает ;(" << '\n';
				break;
			case 0:// Выход!
				return 0;
			default:
				std::cout << "Нет такого значения!" << '\n';
				break;
		}
	}

	delete[] arrX, arrY;

}
//TODO: разобратся с графиком(gnuplot, qt или matlab?)

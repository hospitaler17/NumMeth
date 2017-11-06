/*  линейное уравнение (уравнение прямой) Ax+By+C=0  */
/* при этом (y1-y2)*x + (x2-x1)*y + (x1*y2-x2*y1) = 0 */
/* y = (Ax+C)/B */


/*==============================================================================*/
#include <iostream>
#include <fstream>

using namespace std;

int main (int argc, char** argv) {
				long double X,Y; // х и у для обработки
				long double arrX, arrY; // массив для хранения точек
				char* name; // имя входного файла
				fstream f; // файл
				if (argc < 2) {
								cerr << "Ошибка аргумента!\nТип ввода аргуметов: ./[prog_name] [input_file.txt]\n";
								return 0;
				}
				else {
								name = argv[1];
				}
				f.open (name, ios_base::in); // блок открытия файла
				if (!f.is_open()) { // проверка файла
								cerr << "Не удалось открыть файл!\n";
								return 0;
				}
				else
								cout << "Файл "<< name << " успешно открыт!" << '\n';

}
//TODO: сделать анализатор для чисел из файла
//TODO: сделать анализатор для числа икс от пользовалеля
//TODO: Написать меню
//TODO: разобратся с графиком
//TODO: написать функцию-сортировку по Х
//TODO: *поиск по половинке
//TODO: количество X = Y

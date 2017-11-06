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

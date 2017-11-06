#include <iostream>


int main (int argc, char** argv) {
long double X,Y; // х и у для обработки
long double arrX, arrY; // массив для хранения точек
char* name;// имя входного файла
if(argc < 1) {

			std::cerr << "Ошибка аргумента!\nТип ввода аргуметов: ./[prog_name] [input_file.txt]\n";
			return 1;
}
	name = argv[1];

}

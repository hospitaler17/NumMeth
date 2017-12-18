#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <iomanip>

#define filename "matr.txt"

using namespace std;

int main(int argc, char *argv[]) {
	int i, j, count;
	double symbol;
	double **matr = NULL, **matrix1;
	int L = 0;
	double max_el = 0.0;
	int max_el_row;
	double tmp_address;
	double tmp_doub1 = 0.0, tmp_doub2 = 0.0, tmp_doub3 = 0.0;
	ifstream fin(filename);


	if (!fin.is_open()) { // проверка файла
		cerr << "Не удалось открыть файл!\n";
		return 0;
	}
	else
		cout << "Файл "<< filename << " успешно открыт!" << '\n';
	while (!fin.eof()) {
		fin >> tmp_doub1;
		count++;
	}
	count--;// из-за перехода на след строку(
	std::cout << "Всего эл-ов в матрице: "<< count << '\n';
	while (1) {
        tmp_doub1 = sqrt(count);
        i = modf(tmp_doub1, &tmp_doub2);
        //std::cout << "count = " << i << '\n';
        if (i == 0) {
            break;
        }
        count--;

    }
	count = static_cast<int>(tmp_doub2);
	tmp_doub1 = 0.0;
	tmp_doub2 = 0.0;

	std::cout << "Размер матрицы: "<< count << '\n';
	fin.clear();// отчистим поток
	fin.seekg(0);// двинемся в начало файла
	matr = new double * [count];
	for(i=0; i<count; i++) {
		matr[i] = new double [count+1];
		for(j=i; j<count; j++) {
		}
	}
	for(int i=0; i<count; i++) {
  		for(int j=0; j<count+1; j++)
     		fin >> matr[i][j];
	}

	matrix1 = new double * [count];
	for(i=0; i<count; i++) {
		matrix1[i] = new double [count+1];
		for(j=i; j<count; j++) {
		}
	}

	for(int i=0; i<count; i++) {
  		for(int j=0; j<count+1; j++) {
			matrix1[i][j] = matr[i][j];
		}
	}

	std::cout << "\nМатрица, считанная с файла: " << '\n';
	for(int i=0; i<count; i++) {
  		for(int j=0; j<count+1; j++) {
				if (j == count) {
					std::cout << "\t";
				}
    			cout << matr[i][j] << " \t ";

		}
		cout << endl;
	}
	// прямой ход метода Гаусса
	unsigned int start_time =  clock(); // начальное время
	for(i=0; i<count; i++) {
  		for(j=i; j<count; j++) {
    		if(fabs(matr[j][i]) > max_el) {
      			max_el_row = j;
        		max_el = fabs(matr[j][i]);
			}
		}
		max_el = 0.0;
		for(int t=0; t<count+1; t++) {
    			tmp_address = matr[max_el_row][t];
    			matr[max_el_row][t] = matr[L][t];
    			matr[L][t] = tmp_address;
			}
		for(int k=1+L; k<count; k++) {
    		tmp_doub1 = matr[k][i]/matr[L][i];
    		for(int l=0; l<=count; l++) {
        		if(fabs(tmp_doub1) == 0)
					break;
        		tmp_doub2 = (matr[L][l]*tmp_doub1);
        		tmp_doub3 = matr[k][l] - tmp_doub2;
        		matr[k][l] = tmp_doub3;
    		}
    	}
		L++;
	}
	unsigned int end_time = clock(); // конечное время
	unsigned int search_time = end_time - start_time; // искомое время
	std::cout << "\nВремя, затраченное на прямой ход Гаусса: " << search_time << " (мс)";
	std::cout << "\nПолученная треугольная матрица: " << endl;
	for(int i=0; i<count; i++) {
 		for(int j=0; j<count+1; j++) {
    		cout << matr[i][j] << "\t       ";
		}
		cout << endl;
	}

	double sum;
	double x[20];
	start_time = clock();
	// обратный ход метода Гаусса
	for(int i=count-1; i>=0; i--) {
  		sum = 0;
  		for(int j=count-1; j>=i; j--) {
   			sum = sum + x[j]*matr[i][j];
    	}
    	x[i]=(matr[i][count]-sum)/matr[i][i];
  		if (x[i]==0) x[i]=fabs(x[i]);
	}
	end_time = clock();
	search_time = end_time - start_time;
	cout << "\nВремя, затраченное на обратный ход Гаусса: " << search_time << " (мс)" << endl;

	cout << "\nРезультаты вычислений: " << endl;
	for(i=0; i<count; i++) {
		cout << fixed << setprecision(5) << "x" << i << " = " << x[i] << endl;
	}
	double s[count];
	double fault[20];
	cout << "\nВектор невязки: " << endl;
	// вычисление вектора невязки
	for(i=0; i<count; i++) {
		s[i] = 0;
		for(j=0; j<count; j++) {
			s[i] = s[i] + matrix1[i][j]*x[j];
		}
		s[i] = matrix1[i][count] - s[i];
		cout << fixed << setprecision(5) << "F[" << i << "] = " << s[i] << endl;
	}

	max_el = 0.0;
	for(i=0; i<count; i++) {
    	if(fabs(s[i]) > max_el) {
    		max_el_row = i;
    		max_el = fabs(s[i]);
    	}
	}
	std::cout << "Норма:" << '\n';
	cout << "\nd = " << fabs(s[max_el_row]) << endl << endl;

	delete matr;
	delete matrix1;
}

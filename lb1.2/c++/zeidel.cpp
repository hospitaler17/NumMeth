#include<iostream>
#include<cstdlib>
#include<cmath>
#include<fstream>
#include<ctime>
#include <iomanip>

#define filename "matr.txt"
// #define filename "mymatr.txt"

using namespace std;




// Функции для расчета =================================================


int check(double **A, int size){ // проверка условий
    int numb = 0;
    int summ = 0;
    int i, j;
    for (i = 0; i < size; i++) {
        numb = fabs(A[i][i]);
        for (j = 0; j < size; j++) {
            if (i != j)
                summ = summ + fabs(A[i][j]);
        }
        if (numb < summ){
            std::cout << "Условие диагонального преобладания НЕ выполнено!" << '\n';
            return 1;
        }
        summ = 0;
    }
    std::cout << "Условие диагонального преобладания выполнено!" << '\n';
    return 0;
}

int main(int argc, char const *argv[]) {
	int iterat = 0, size;
	int i, j, k;
    double E = 0.001; // точность
    double **A, *b, *X, **Z, *tempX;
    double tmp_doub1 = 0.0, tmp_doub2 = 0.0;
    float time0, time1;
    ifstream fin(filename);

	if (!fin.is_open()) { // проверка файла
		cerr << "Не удалось открыть файл [matr.txt]!\n";
		return 0;
    }
    cout << "Файл ["<< filename << "] успешно открыт!" << '\n';
    while (!fin.eof()) {
		fin >> tmp_doub1;
		size++;
	}
	size--;// из-за перехода на след строку(
	std::cout << "Всего эл-ов в матрице: "<< size << '\n';
	while (1) {
		tmp_doub1 = sqrt(size);
		i = modf(tmp_doub1, &tmp_doub2);
		// std::cout << "size = " << i << '\n';
		if (i == 0) {
			break;
		}
		size--;

	}
	size = static_cast<int>(tmp_doub2); // пеобразуем целое дабл в инт
	std::cout << "Размер матрицы: "<< size << '\n';
	fin.clear();// отчистим поток
	fin.seekg(0);// двинемся в начало файла

	std::cout << "\n=========================================" << '\n';

    A = new double* [size];// матр коэф
	for (i = 0; i < size; i++)
		A [i] = new double [size];

    Z = new double* [size];// матр коэф test
	for (i = 0; i < size; i++)
		Z[i] = new double [size];

    b = new double [size];// вектор
    X = new double [size];// корни
    tempX = new double [size];



    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            fin >> A[i][j];
        }
        fin >> b[i];
        tempX[i] = 0;
    }
	if (check(A, size) != 0)
        return 1;
	std::cout << "Матрица коеффициентов A и вектор b:" << '\n';
    for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			cout << setw(5) << A[i][j];
		}
		cout << "  |" << setw(3) << b[i] << endl;
	}

    // ==================[ решение Якоби] ======================================================

    time0 = clock ();
    double Max = 0.0;
    while (1){
        for (i = 0; i < size; i++) {
            X[i] = b[i];
            for (j = 0; j < size; j++)
                if (i != j)
                    X[i] = X[i] - A[i][j] * tempX[j];
            X[i] = X[i] / A[i][i];
        }
        iterat += 1;
        Max = fabs(X[0] - tempX[0]);
        for (i = 1; i < size; i++) {
            if (Max < fabs(X[i]-tempX[i]))
                Max = fabs(X[i]-tempX[i]);
        }
        if (Max < E){
            break;
        }
        for (i = 0; i < size; i++)
            tempX[i] = X[i];
    }
    time1 = clock ();
	std::cout << "\n=========================================" << '\n';
	std::cout << "Метод Якоби" << '\n';
	std::cout << "Решение:" << '\n';
    for ( i = 0; i < size; i++) {
        std::cout << "  X"<< i+1 <<" = " << X[i] <<'\n';
        X[i] = 0;
        tempX[i] = 0;
    }
	std::cout << "Кол-во итераций: " << iterat << '\n';
    iterat = 0;
    cout << "На метод Якоби потрачено " << (time1 - time0) / 1000 << " секунд" << endl;
    std::cout << "\n=========================================" << '\n';
    // ==================[ решение Гаусса-Зейделя] ==================================================
    std::cout << "Метод Гаусса-Зейделя" << '\n';
	std::cout << "Решение:" << '\n';
    time0 = clock ();//
    Max = 0.0;
    while (1){
        for (i = 0; i < size; i++) {
            X[i] = b[i];
            for (j = 0; j < i; j++)
                if (i != j)
                    X[i] = X[i] - A[i][j] * X[j];
            for (j = i; j < size; j++)
                if (i != j)
                    X[i] = X[i] - A[i][j] * tempX[j];
            X[i] = X[i] / A[i][i];
        }

        iterat += 1;
        Max = fabs(X[0] - tempX[0]);
        for (i = 1; i < size; i++) {
            if (Max < fabs(X[i]-tempX[i]))
                Max = fabs(X[i]-tempX[i]);
        }
        if (Max < E){
            break;
        }
        for (i = 0; i < size; i++)
            tempX[i] = X[i];
    }
    time1 = clock ();//
    for ( i = 0; i < size; i++) {
        std::cout << "  X"<< i+1 <<" = " << X[i] <<'\n';
    }
    std::cout << "Кол-во итераций: " << iterat << '\n';
    cout << "На метод Гаусса-Зейделя потрачено " << (time1 - time0) / 1000 << " секунд" << endl;
    return 0;
}

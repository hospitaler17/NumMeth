#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <string>

#define filename "matr.txt"

using namespace std;

int main (int argc, char **argv)
{
	int count, k, p, l, i, j, AKK, M;
	double **A, *b, **U, *q, *x, AMAIN, delta = 0, *F;
	double tmp_doub1 = 0, tmp_doub2 = 0, tmp_doub3 = 0;
	int *IOR;
	float time0, time1;

	ifstream fin(filename);


	if (!fin.is_open()) { // проверка файла
		cerr << "Не удалось открыть файл!\n";
		return 0;
	}
	else
		cout << "Файл "<< filename << " успешно открыт!" << '\n';
	std::cout << "=================================================" << '\n';
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
	cout << "Исходная матрица:" << endl;
	A = new double* [count];
	b = new double [count];
	U = new double* [count];
	q = new double [count];
	x = new double [count];
	for (i = 0; i < count; i++){
		A [i] = new double [count];
		U [i] = new double [count];
		for (j = 0; j < count; j++){
			fin >> A[i][j];
			U[i][j] = A[i][j];
			cout << setw(5) << A[i][j];
		}
		fin >> b[i];
		q[i] = b[i];
		cout << "  |" << setw(3) << b[i] << endl;
	}

	std::cout << "=================================================" << '\n';
	time0 = clock ();
	// Прямой ход метода Гаусса:
	IOR = new int [count];
	for (k = 0; k < count; k++)
		IOR[k] = k;

	for (k = 0; k < count-1; k++){
		AKK = 0;
		for (i = k; i < count; i++){
			l = IOR[i];
			if (fabs (U[l][k]) >= AKK){
				M = l;
				p = i;
				AKK = fabs (U[l][k]);
			}
		}

		if (p != k){
			IOR[p] = IOR[k];
			IOR[k] = M;
		}

		AMAIN = U[M][k];
		if (AMAIN == 0){
			cout << "Произошла ошибка (IER = 1).(#1)" << endl;
			return 1;
		}

		for (j = k; j < count; j++)
			U[M][j] = U[M][j] / AMAIN;


		q[M] = q[M] / AMAIN;
		for (i = k+1; i < count; i++){
			l = IOR[i];
			for (j = k+1; j < count; j++)
				U[l][j] = U[l][j] - U[l][k] * U[M][j];
			q[l] = q[l] - U[l][k] * q[M];
		}
	}

	l = IOR[count-1];
	q[l] = q[l] / U[l][count-1];
	x[count-1] = q[l];

	if (U[l][count-1] == 0){
		cout << "Произошла ошибка (IER = 1).(#2)" << endl;
		return 1;
	}

	time1 = clock ();
	cout << "На прямой ход Гаусса потрачено " << (time1 - time0) / 1000 << " секунд" << endl;
	time0 = clock ();
	// Обратный ход метода Гаусса:
	for (k = count-1; k >= 0; k--){
		l = IOR[k];
		x[k] = q[l];
		for (j = k+1; j < count; ++j)
			x[k] = x[k] - U[l][j] * x[j];
	}

	time1 = clock ();
	cout << "На обратный ход Гаусса потрачено " << (time1 - time0) / 1000 << " секунд" << endl;
	std::cout << "=================================================" << '\n';
	// Вывод результатов:
	cout << "Ответ: " << endl;
	for (i = 0; i < count; i++)
		cout << ">>> x" << i+1 << " = " << x[i] << endl;
	// Вычисление нормы вектора:
	F = new double [count];
	std::cout << "Вектора невязки:" << '\n';
	for (i = 0; i < count; i++){
		F[i] = 0;
		for (j = 0; j < count; j++)
			F[i] = F[i] + A[i][j] * x[j];
		F[i] = F[i] - b[i];
		std::cout << ">>> " << F[i] <<'\n';
		if (F[i] > delta)
			delta = F[i];
	}
	cout << "Норма вектора невязки: " << "\n>>> " << delta << endl;
	for (i = 0; i < count; i++){
		delete [] A[i];
		delete [] U[i];
	}
	delete [] A;
	delete [] b;
	delete [] U;
	delete [] q;
	delete [] x;
	delete [] F;
	return 0;
}

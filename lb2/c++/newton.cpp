#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(int argc, char const *argv[]) {
	double x1 = 1, x2 = 0; // начальное приближение (дано)
	double x_k1, x_k2;
	double e1 = 0.000000001, e2 = 0.000000001; // конст, опр. погрешность
	int NIT = 100; // макс итератор
	int k = 1;
	double d1, d2; // дельты
	double F[2]; // ориг. функции
	double J[2][2]; // матрица производных
	double detJ = 0; // детерминанта (решение) J
	double W[2][2];
	std::cout << "Введите максимальное кол-во итераций\nNIT >>> ";
	cin >> NIT;
	std::cout << "============================================" << '\n';
	std::cout << "|  k  | " << setw(16) << "delta1" << " | " << setw(18) << "delta2 |\n";
	std::cout << "============================================" << '\n';
	while (1) {
		if (k == NIT){ // Если макс итератор настигнут
			std::cout << "============================================" << '\n';
			std::cerr << "(!) Ошибка: IER = 2 (!)" << '\n';
			break;
		}
		F[0] = sin(x1) - x2 - 1.32;
		F[1] = cos(x2) - x1 + 0.85;
		J[0][0] = cos(x1);
		J[0][1] = -1;
		J[1][0] = -1 * sin(x2);
		J[1][1] = -1;

		detJ = J[0][0] * J[1][1] - J[0][1] * J[1][0]; // находим детерминанту
		W[0][0] = 1/detJ * J[1][1];
		W[0][1] = 1/detJ * (-J[0][1]);
		W[1][0] = 1/detJ * (-J[1][0]);
		W[1][1] = 1/detJ * J[0][0];
		x_k1 = x1 - (W[0][0] * F[0] + W[0][1] * F[1]);
		x_k2 = x2 - (W[1][0] * F[0] + W[1][1] * F[1]);
		d1 = abs (F[0]);
		if (abs (F[1]) > d1)
			d1 = abs (F[1]);

		if (abs (x_k1) < 1) {
			d2 = abs (x_k1 - x1);
			if (abs (x_k2 - x2) > d2)
				d2 = abs (x_k2 - x2);
		}
		else {
			d2 = abs ((x_k1 - x1)/x_k1);
			if (abs ((x_k2 - x2)/x_k2) > d2)
				d2 = abs ((x_k2 - x2)/x_k2);
		}

		std::cout << '|' << setw(3) << k << "  | " << setw(16) << d1 << " | " << setw(15) << d2 << " |" << '\n';

		x1 = x_k1;
		x2 = x_k2;

		if ((d1 <= e1) && (d2 <= e2))
			break;

		k++;
	}
	cout << "Решение:\n" << "x1 = " << x1 << "\nx2 = " << x2 << '\n';
	return 0;
}

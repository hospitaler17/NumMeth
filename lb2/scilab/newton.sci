x1 = 1.0
x2 = 0 // начальное приближение (дано)
// double x_k1, x_k2;
e1 = 0.000000001
e2 = 0.000000001 // конст, опр. погрешность
NIT = 100 // макс итератор
k = 1
// double d1, d2; // дельты
// F = zeros(2);
// double F[2]; // ориг. функции
J = zeros(2,2);
// double J[2][2]; // матрица производных
detJ = 0; // детерминанта (решение) J
W = zeros(2,2);
// double W[2][2];

printf("Введите максимальное кол-во итераций")
NIT = input('NIT >>> ');
disp( '========================================')
printf("| k |         delta1 |         delta2 |")
disp( '========================================')
while (1) do
	if (k == NIT) then // Если макс итератор настигнут
		disp( '============================================')
		disp("(!) Ошибка: IER = 2 (!)")
		break;
	end
	F1 = sin(x1) - x2 - 1.32;
	F2 = cos(x2) - x1 + 0.85;
	J(1, 1) = cos(x1);
	J(1, 2) = -1;
	J(2, 1) = -1 * sin(x2);
	J(2, 2) = -1;
	detJ = J(1, 1) * J(2, 2) - J(1, 2) * J(2, 1); // находим детерминанту
	W(1, 1) = 1/detJ * J(2, 2);
	W(1, 2) = 1/detJ * (-J(1, 2));
	W(2, 1) = 1/detJ * (-J(2, 1));
	W(2, 2) = 1/detJ * J(1, 1);
	x_k1 = x1 - (W(1, 1) * F1 + W(1, 2) * F2);
	x_k2 = x2 - (W(2, 1) * F1 + W(2, 2) * F2);
	d1 = abs (F1);
	if (abs (F2) > d1) then
		d1 = abs (F2);
    end
	if (abs (x_k1) < 1) then
		d2 = abs (x_k1 - x1);
		if (abs (x_k2 - x2) > d2) then
			d2 = abs (x_k2 - x2)
        end
    end
    if (abs (x_k1) >= 1) then
		d2 = abs ((x_k1 - x1)/x_k1);
		if (abs ((x_k2 - x2)/x_k2) > d2) then
			d2 = abs ((x_k2 - x2)/x_k2);
        end
    end
	// std::cout << '|' << setw(3) << k << "  | " << setw(16) << d1 << " | " << setw(15) << d2 << " |" << '\n';
    // disp(k, d1, d2)
	printf("| %d | %1.12f | %1.12f |\n",k, d1, d2);
	x1 = x_k1;
	x2 = x_k2;

	if (d1 <= e1) & (d2 <= e2) then
		break;
    end
	k = k + 1;
end
// disp( x1, x2, "Решение:")
printf("Решение:\n x1 =  %1.12f\n x2 = %1.12f\n", x1, x2);

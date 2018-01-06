# -*- coding: utf-8 -*-
import numpy as np
import math


x1 = 1.0
x2 = 0.0 # начальное приближение (дано)
e1 = 0.000000001
e2 = 0.000000001 # конст, опр. погрешность
k = 1
F = np.zeros(2)
J = np.zeros((2,2))
detJ = 0 # детерминанта (решение)
W = np.zeros((2,2))
NIT = int(raw_input("Введите максимальное количество итераций\nNIT >>> "))
print ("============================================\n")
print("|  k  | delta1 | delta2 |\n")
print ("============================================\n")
while (True):
	if (k == NIT): # Если макс итератор настигнут
		print ("============================================\n")
		print("(!) Ошибка: IER = 2 (!)\n")
		break

	F[0] = math.sin(x1) - x2 - 1.32
	F[1] = math.cos(x2) - x1 + 0.85
	J[0][0] = math.cos(x1)
	J[0][1] = -1
	J[1][0] = -1 * math.sin(x2)
	J[1][1] = -1

	detJ = J[0][0] * J[1][1] - J[0][1] * J[1][0] # находим детерминанту
	W[0][0] = 1/detJ * J[1][1]
	W[0][1] = 1/detJ * (-J[0][1])
	W[1][0] = 1/detJ * (-J[1][0])
	W[1][1] = 1/detJ * J[0][0]
	x_k1 = x1 - (W[0][0] * F[0] + W[0][1] * F[1])
	x_k2 = x2 - (W[1][0] * F[0] + W[1][1] * F[1])
	d1 = abs (F[0])
	if (abs (F[1]) > d1):
		d1 = abs (F[1]);

	if (abs (x_k1) < 1):
		d2 = abs (x_k1 - x1);
		if (abs (x_k2 - x2) > d2):
			d2 = abs (x_k2 - x2);

	else:
		d2 = abs ((x_k1 - x1)/x_k1);
		if (abs ((x_k2 - x2)/x_k2) > d2):
			d2 = abs ((x_k2 - x2)/x_k2);

	print("| %d | %.8f   | %.8f   |"  %(k, d1, d2))
	x1 = x_k1
	x2 = x_k2

	if ((d1 <= e1) and (d2 <= e2)):
		break

	k = k + 1
print("Решение:\nx1 = %.8f\nx2 = %.8f\n"  %(x1, x2))

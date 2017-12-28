# -*- coding: utf-8 -*-
import math # мат. опер.
import os
import numpy as np # для работы с матрицей
from time import time # для времени

size = int(raw_input("Введите размер квадратной матрицы:\n>>> "))
delta = 0
l = 0
tmp_doub1 = 0
tmp_doub2 = 0
tmp_doub3 = 0

U = np.zeros(size)
q = np.zeros(size)
x = np.zeros(size)



A = np.zeros((size,size)) # матрицы размера size с нулями
b = np.zeros(size)
F = np.zeros(size)

fname = "matr.txt" # Название файла с матрицей
if os.path.exists(fname):
    data = np.loadtxt(fname, delimiter=' ' ,dtype = np.float)
    for i in range(size):
        for j in range(size):
            A[i, j] = data[i, j]
        b[i] = data[i, size]
else:
    print("Файл [matr.txt] не найден!\nПроверьте файлы программы...")
    raise SystemExit # выход!
q = b;
U = A;
print("Исходная матрица:")

print(U)
print(q)

print("=================================================")
tic = time() # Прямой ход Гаусса
IOR = np.zeros(size+1)
for k in range(size):
	IOR[int(k)] = k
for k in range(size-1):
	AKK = 0
	for i in range(k, size):
		l = IOR[int(i)]
		if math.fabs(U[int(l)][int(k)]) >= AKK:
			M = l
			p = k+i
			AKK = math.fabs(U[int(l)][int(k)])

	if p != k:
		IOR[int(p)] = IOR[int(k)]
		IOR[int(k)] = M

	AMAIN = U[int(M)][int(k)]
	if AMAIN == 0:
		print( "Произошла ошибка (IER = 1).(#1)")
		raise SystemExit # выход!

	for j in range(k, size):
		U[int(M)][int(j)] = U[int(M)][int(j)] / AMAIN


	q[int(M)] = q[int(M)] / AMAIN
	# print("un",q[int(M)])
	for i in range(k+1, size):
		l = IOR[int(i)]
		for j in range(k+1, size):
			U[int(l)][int(j)] = U[int(l)][int(j)] - U[int(l)][int(k)] * U[int(M)][int(j)]
		q[int(l)] = q[int(l)] - U[int(l)][int(k)] * q[int(M)]
	# print("circle №",k ,q[int(l)])

print(q)
l = IOR[int(size-1)]
q[int(l)] = q[int(l)] / U[int(l)][int(size-1)]
x[int(size-1)] = q[int(l)]

if U[int(l)][int(size-1)] == 0:
	print("Произошла ошибка (IER = 1).(#2)")
	raise SystemExit # выход!

toc = time()
print("Время работы прямого хода: %f" %(toc-tic))
tic = time() # Обратный ход Гаусса
for k in reversed(size-1): # ????
	l = IOR[k]
	x[k] = q[l]
	for j in range(k+1, size):
		x[k] = x[k] - U[l][j] * x[j]

toc = time()
print("Время работы обратного хода: %f" %(toc-tic))
print("=================================================")
print("Ответ: ")
for i in range(size):
	print(">>> x = ", x[i])

F = np.zeros(size)
print("Вектора невязки:")
for i in range(size):
	F[i] = 0
	for j in range(size):
		F[i] = F[i] + A[i][j] * x[j]
	F[i] = F[i] - b[i]
	print(">>> ", F[i])
	if F[i] > delta:
		delta = F[i]
print("Норма вектора невязки: \n>>> ", delta)

# -*- coding: utf-8 -*-
import numpy as np
from math import fabs
import os
import re

def check(A,N): # проверка условий
    numb = 0
    summ = 0
    for i in range(N):
        numb = fabs(A[i][i])
        for j in range(N):
            if i!=j:
                summ = summ + fabs(A[i][j])
        if numb < summ:
            print("Условие диагонального преобладания не выполнено!")
            raise SystemExit # выход!()
        summ = 0


def findX(method,A,Y,X,tempX,N):
    if method == 1: # Для Якоби
        for i in range(N):
            X[i] = Y[i]
            for j in range(N):
                if i != j:
                    X[i] = X[i] - A[i][j] * tempX[j]
            X[i] = X[i] / A[i][i]
    if method == 2: # для Гаусса-Зейделя
        for i in range(N):
            X[i] = Y[i]
            for j in range(i):
                if i != j:
                    X[i] = X[i] - A[i][j] * X[j]
            for j in range(i,N):
                if i != j:
                    X[i] = X[i] - A[i][j] * tempX[j]
            X[i] = X[i] / A[i][i]

def calc(E,method,A,Y,X,tempX,N,iterat): # Вычисления!
    Max = 0
    while 1:
        findX(method,A,Y,X,tempX,N)
        iterat[0] += 1
        Max = fabs(X[0] - tempX[0])
        for i in range(1,N):
            if Max < fabs(X[i]-tempX[i]):
                Max = fabs(X[i]-tempX[i])
        if Max < E:
            return
        for i in range(N):
            tempX[i] = X[i]

iterat = [0]
N = int(raw_input("Введите размер матрицы:\n>>> "))
print("\n=========================================")
# E = float(raw_input("Введите точность:\n>>> "))
E = 0.001
A = np.zeros((N,N))
Y = np.zeros(N)
X = np.zeros(N)
tempX = np.zeros(N)
filename = "matr.txt"
if os.path.exists(filename):#  Если вообще открылось
	file = open(filename)
	text = file.readlines()
	for i in range(N):
		arr = re.findall(r"[-]?\d+\.\d+|[-]?\d+", text[i])
		if len(arr) != N + 1:
			print("Размер матрицы меньше заданного числа!")
			raise SystemExit # выход!()
		else:
			for j in range(N):
				A[i][j] = arr[j]
			Y[i] = arr[N]
#     for i in range(size):
#         for j in range(size):
#             Amatr[i, j] = data[i, j]
#         Barr[i] = data[i, size]
else:
    print("Файл [matr.txt] не найден!\nПроверьте файлы программы...")
    raise SystemExit # выход!

check(A,N)
print("Матрица коеффициентов:")
print(A)
print("Матрица b:")
print(Y)
calc(E,1,A,Y,X,tempX,N,iterat)
print("\n=========================================")
print("Метод Якоби")
print("Решение:")
print(X)
print("Кол-во итераций: %d"%iterat[0])
for i in range(N):
    tempX[i] = 0
    X[i] = 0
iterat[0] = 0
calc(E,2,A,Y,X,tempX,N,iterat)
print("\n=========================================")
print("Метод Гаусса-Зейделя")
print("Решение:")
print(X)
print("Кол-во итераций: %d"%iterat[0])

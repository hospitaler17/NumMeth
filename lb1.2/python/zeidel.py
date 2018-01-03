# -*- coding: utf-8 -*-
import numpy as np
from math import fabs
import os
import re

def check(A,size): # проверка условий
    numb = 0
    summ = 0
    for i in range(size):
        numb = fabs(A[i][i])
        for j in range(size):
            if i!=j:
                summ = summ + fabs(A[i][j])
        if numb < summ:
            print("Условие диагонального преобладания не выполнено!")
            raise SystemExit # выход!()
        summ = 0


def findX(method,A,b,X,tempX,size):
    if method == 1: # Для Якоби
        for i in range(size):
            X[i] = b[i]
            for j in range(size):
                if i != j:
                    X[i] = X[i] - A[i][j] * tempX[j]
            X[i] = X[i] / A[i][i]
    if method == 2: # для Гаусса-Зейделя
        for i in range(size):
            X[i] = b[i]
            for j in range(i):
                if i != j:
                    X[i] = X[i] - A[i][j] * X[j]
            for j in range(i,size):
                if i != j:
                    X[i] = X[i] - A[i][j] * tempX[j]
            X[i] = X[i] / A[i][i]

def calc(E,method,A,b,X,tempX,size,iterat): # Вычисления!
    Max = 0
    while 1:
        findX(method,A,b,X,tempX,size)
        iterat[0] += 1
        Max = fabs(X[0] - tempX[0])
        for i in range(1,size):
            if Max < fabs(X[i]-tempX[i]):
                Max = fabs(X[i]-tempX[i])
        if Max < E:
            return
        for i in range(size):
            tempX[i] = X[i]

iterat = [0]
size = int(raw_input("Введите размер матрицы:\n>>> "))
print("\n=========================================")
# E = float(raw_input("Введите точность:\n>>> "))
E = 0.001
A = np.zeros((size,size))
b = np.zeros(size)
X = np.zeros(size)
tempX = np.zeros(size)
filename = "matr.txt"
if os.path.exists(filename):#  Если файл существует
	file = open(filename)
	text = file.readlines()
	for i in range(size):
		arr = re.findall(r"[-]?\d+\.\d+|[-]?\d+", text[i])
		if len(arr) != size + 1:
			print("Размер матрицы меньше заданного числа!")
			raise SystemExit # выход!()
		else:
			for j in range(size):
				A[i][j] = arr[j]
			b[i] = arr[size]
else:
    print("Файл [matr.txt] не найден!\nПроверьте файлы программы...")
    raise SystemExit # выход!

check(A,size)
print("Матрица коеффициентов:")
print(A)
print("Матрица b:")
print(b)
calc(E,1,A,b,X,tempX,size,iterat)
print("\n=========================================")
print("Метод Якоби")
print("Решение:")
print(X)
print("Кол-во итераций: %d"%iterat[0])
for i in range(size):
    tempX[i] = 0
    X[i] = 0
iterat[0] = 0
calc(E,2,A,b,X,tempX,size,iterat)
print("\n=========================================")
print("Метод Гаусса-Зейделя")
print("Решение:")
print(X)
print("Кол-во итераций: %d"%iterat[0])

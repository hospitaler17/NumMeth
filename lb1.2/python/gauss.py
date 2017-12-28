# -*- coding: utf-8 -*-
import math # мат. опер.
import os
import numpy as np # для работы с матрицей
from time import time # для времени

max = [0]
cur = [0]
D = [0]
size = int(raw_input("Введите размер квадратной матрицы:\n>>> "))
Amatr = np.zeros((size,size)) # матрицы размера size с нулями
Barr = np.zeros(size)
X = np.zeros(size)
F = np.zeros(size)
fname = "matr.txt" # Название файла с матрицей
if os.path.exists(fname):
    data = np.loadtxt(fname, delimiter=' ' ,dtype = np.float)
    for i in range(size):
        for j in range(size):
            Amatr[i, j] = data[i, j]
        Barr[i] = data[i, size]
else:
    print("Файл [matr.txt] не найден!\nПроверьте файлы программы...")
    raise SystemExit # выход!
print(Amatr)
print(Barr)
Acp = Amatr.copy() # копии
Bcp = Barr.copy()

# ===============[Функции для вычисления]======================
def calc1(arr, b, cu, n):
    for i in range(cu[0]+1, n):
        tmp = arr[i, cu[0]]
        for j in range(cu[0], n):
            arr[i,j] -= arr[cu[0], j]*tmp
        b[i] -= b[cu[0]]*tmp

def calc2(arr, b, x, cu, n):
    y1 = b[cu[0]]
    if n != cu[0]:
        for i in range(n-1, cu[0], -1):
            y1 -= arr[cu[0], i]*x[i]
    x[cu[0]] = y1/arr[cu[0], cu[0]]

def gauss1(arr, b, M, cu, n): # Прямой ход Гаусса
    while(cu[0] < n-1):
        M[0] = cu[0] # поиск макс значения
        for i in range(cu[0], n):
            if math.fabs(arr[M[0], cu[0]]) < math.fabs(arr[i, cu[0]]):
                M[0] = i
        if cu != M:# подмена
            for i in range(cu[0], n):
                tmp = arr[M, i]
                arr[M, i] = arr[cu[0], i]
                arr[cu[0], i] = tmp
            tmp = b[M]
            b[M] = b[cu[0]]
            b[cu[0]] = tmp
        tmp = arr[cu[0], cu[0]]
        for i in range(cu[0], n):
            for j in range(cu[0], n):
                arr[i,j] = arr[i,j]/tmp
            b[i] = b[i]/tmp
        calc1(arr, b, cu, n) # посчитаем
        cu[0] += 1

def gauss2(arr, b, x, cu, n): # Обратный ход Гаусса
    while(cu[0] >= 0):
        calc2(arr, b, x, cu, n)
        cu[0] -= 1

def vect(arr, b, x, f, n, delta): # вектор невязки, норма
    # q = [15.71, 43.78, 37.11]
    #
    # print(q)
    # print(arr)
    # for i in range(n):
    #     for j in range(n):
    #         f[i] = f[i] + arr[i,j]*x[j]
    #         print(f[i])
    #     print(f[i],"-", q[i])
    #     f[i] = f[i] - q[i]
    # delta[0] = math.fabs(f[0])
    # for i in range(n):
    #     if delta[0] < math.fabs(f[i]):
    #     	delta[0] = math.fabs(f[i])
    #     #print(delta[0])


    for i in range(n):
		f[i] = 0.0
		for j in range(n):
			f[i] = f[i] + arr[i][j] * x[j]
		f[i] = f[i] - b[i]

    delta[0] = math.fabs(f[0])
    for i in range(n):
        if delta[0] < math.fabs(f[i]):
            delta[0] = math.fabs(f[i])
# ===============[the end]======================

tic = time() # Прямой ход Гаусса
gauss1(Amatr, Barr, max, cur, size)
toc = time()
print("Время работы прямого хода: %f" %(toc-tic))

tic = time() # Обратный ход Гаусса
gauss2(Amatr, Barr, X, cur, size)
toc = time()
print("Время работы обратного хода: %f" %(toc-tic))

vect(Acp, Bcp, X, F, size, D)
print("Решение системы: ")
print(X)

print("Вектор невязки: ")
print(F)

print("Норма: ")
print(D[0])

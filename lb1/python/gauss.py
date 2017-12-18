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
Ycp = Barr.copy()

# ===============[Функции для вычисления]======================
def calc1(ar, y, cu, n):
    for i in range(cu[0]+1, n):
        tmp = ar[i, cu[0]]
        for j in range(cu[0], n):
            ar[i,j] -= ar[cu[0], j]*tmp
        y[i] -= y[cu[0]]*tmp

def calc2(ar, y, x, cu, n):
    y1 = y[cu[0]]
    if n != cu[0]:
        for i in range(n-1, cu[0], -1):
            y1 -= ar[cu[0], i]*x[i]
    x[cu[0]] = y1/ar[cu[0], cu[0]]

def gauss1(ar, y, M, cu, n): # Прямой ход Гаусса
    while(cu[0] < n-1):
        M[0] = cu[0] # поиск макс значения
        for i in range(cu[0], n):
            if math.fabs(ar[M[0], cu]) < math.fabs(ar[i, cu[0]]):
                M[0] = i
        if cur != M:# подмена
            for i in range(cu[0], size):
                tmp = ar[M, i]
                ar[M, i] = ar[cu[0], i]
                ar[cu[0], i] = tmp
            tmp = y[M]
            y[M] = y[cu[0]]
            y[cu[0]] = tmp
        tmp = ar[cu[0], cu[0]]
        for i in range(cu[0], n):
            for j in range(cu[0], n):
                ar[i,j] = ar[i,j]/tmp
            y[i] = y[i]/tmp
        calc1(ar, y, cu, n) # посчитаем
        cu[0] += 1

def gauss2(ar, y, x, cu, n): # Обратный ход Гаусса
    while(cu[0] >= 0):
        calc2(ar, y, x, cu, n)
        cu[0] -= 1

def vect(ar, y, x, f, n, d): # вектор невязки, норма
    for i in range(n):
        for j in range(n):
            f[i] += ar[i,j]*x[j]
        f[i] -= y[i]
    d[0] = math.fabs(f[0])
    for i in range(n):
        if d[0] < math.fabs(f[i]):
            d[0] = math.fabs(f[i])
	    print(d[0])
# ===============[the end]======================

tic = time() # Прямой ход Гаусса
gauss1(Amatr, Barr, max, cur, size)
toc = time()
print("Время работы прямого хода: %f" %(toc-tic))

tic = time() # Обратный ход Гаусса
gauss2(Amatr, Barr, X, cur, size)
toc = time()
print("Время работы обратного хода: %f" %(toc-tic))

vect(Acp, Ycp, X, F, size, D)
print("Решение системы: ")
print(X)

print("Вектор невязки: ")
print(F)

print("Норма: ")
print(D[0])

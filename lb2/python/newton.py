# -*- coding: utf-8 -*-
import numpy as np
import math

###################################################################################
##################################[ функции ]######################################
###################################################################################

def function1(x): # ориг функции
    return (math.sin(x[0])-x[1]-1.32)

def function2(x):
    return (math.cos(x[1])-x[0]+0.85)

def derivativef1x1(x): # производ 1 функции
    return (math.cos(x[0]))

def derivativef1x2(x):
    return (-1)

def derivativef2x1(x): # производ 2 функции
    return (-1*math.sin(x[1]))

def derivativef2x2(x):
    return (-1)

def findMax(A, maxim, cur, n):
    maxim[0] = cur[0]
    for i in range(cur[0], n):
        if math.fabs(A[maxim[0], cur[0]]) < math.fabs(A[i, cur[0]]):
            maxim[0] = i

def swap(A, F, maxim, cur, n):
    findMax(A, maxim, cur, n)
    if cur != maxim:
        for i in range(cur[0], n):
            temp = A[maxim, i]
            A[maxim, i] = A[cur[0], i]
            A[cur[0], i] = temp
        temp = F[maxim]
        F[maxim] = F[cur[0]]
        F[cur[0]] = temp
    temp = A[cur[0], cur[0]]
    for i in range(cur[0], n):
        for j in range(cur[0], n):
            A[i, j] = A[i, j] / temp
        F[i] = F[i] / temp

def func1(A, F, cur, n):
    for i in range(cur[0] + 1, n):
        temp = A[i, cur[0]]
        for j in range(cur[0], n):
            A[i,j] -= A[cur[0], j] * temp
        F[i] -= F[cur[0]] * temp

def gauss1(A, F, maxim, cur, n):
    while cur[0] < n - 1:
        swap(A, F, maxim, cur, n)
        func1(A, F, cur, n)
        cur[0] += 1

def func2(A, F, temp_x, cur, n):
    F1 = F[cur[0]]
    if n != cur[0]:
        for i in range(n - 1, cur[0], -1):
            F1 -= A[cur[0], i] * temp_x[i]
    temp_x[cur[0]] = F1 / A[cur[0], cur[0]]

def gauss2(A, F, temp_x, cur, n):
    while(cur[0] >= 0):
        func2(A, F, temp_x, cur, n)
        cur[0] -= 1

def calcSLAE(A, F, temp_x, x, x_k1, NIT): # System of Linear Algebraic Equations
    cur = [0]
    maxim = [0]
    n = 2
    A[0][0] = derivativef1x1(x)
    A[0][1] = derivativef1x2(x)
    A[1][0] = derivativef2x1(x)
    A[1][1] = derivativef2x2(x)
    F[0] =- 1 * function1(x)
    F[1] =- 1 * function2(x)
    gauss1(A, F, maxim, cur, n)
    gauss2(A, F, temp_x, cur, n)
    x_k1[0] = x[0] + temp_x[0]
    x_k1[1] = x[1] + temp_x[1]

def check(d, E, x_k1, x, k): # проверка условия!!
    temp = 0
    if math.fabs(function1(x)) > math.fabs(function2(x)):
        d[0] = math.fabs(function1(x))
    else:
        d[0] = math.fabs(function2(x))
    if (math.fabs(x_k1[0]) < 1):
        d[1] = math.fabs(x_k1[0] - x[0]);
    else:
        d[1] = math.fabs((x_k1[0] - x[0]) / x_k1[0])
    if (math.fabs(x_k1[1]) < 1):
        temp = math.fabs(x_k1[1] - x[1])
    else:
        temp = math.fabs((x_k1[1] - x[1]) / x_k1[1])
    if (temp > d[1]):
        d[1] = temp
    print("%d | %.10f   | %.10f   |"  %(k[0], d[0], d[1]))
    if(d[0] <= E[0] and d[1] <=E [1]):
        return 1
    else:
        return 0

###################################################################################
###############################[основной код]######################################
###################################################################################

A = np.zeros((2,2))
F = np.zeros(2)
x_k1 =np.zeros(2)
temp_x =np.zeros(2)
x = np.zeros(2)
E = np.zeros(2)
d = np.zeros(2)

k = [1]
NIT = int(raw_input("Введите максимальное кол-во итераций\nNIT >>> "))

x[0] = float(raw_input("Введите начальные приближения\nx1 >>> "))
x[1] = float(raw_input("x2 >>> "))

# E[0] = float(raw_input("Введите константы, опред. погрешность\nE1 >>> "))
# E[1] = float(raw_input("E2 >>> "))

E[0] = 0.000000001
E[1] = 0.000000001

print("===================================================================")
while True:
    calcSLAE(A, F, temp_x, x, x_k1, NIT)
    if(check(d, E, x_k1, x, k)):
        break
    if(k[0]>=NIT):
        print("IER=2")
        print(k[0])
        break
    k[0] = k[0] + 1
    x[0] = x_k1[0]
    x[1] = x_k1[1]

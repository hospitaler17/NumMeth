# -*- coding: utf-8 -*-
from math import sin, factorial, fabs

x=0.0
j=0
result=0.0
while 1:
    n = int (raw_input("Введите максимальное значение: "))# ввод n - стоп цикла
    if n%2 and n>0: # проверка на вшивость (остаток от деления и нуль)
        break
while 1:
    E = float (raw_input ("Введите значение точности: "))
    if E > 0:
        break
print ("=================================")
print ("n\t X max\t")
print ("---------------------------------")
for t in range(1, n+1, 2):
    x = 0.0
    for i in range (1000):
        result = 0.0
        j = 0 # коэф. знака
        for r in range(1, t+1, 2):
            result+= ((-1)**j)*((x**r)/factorial(r))# ** - степень
            j = j+1
        if fabs (sin(x) - result) > E: # модуль; точность
            x-=0.1
            print("%i --\t %f\t" %(t,x))
            break
        else:
            x+=0.1
print("=================================")

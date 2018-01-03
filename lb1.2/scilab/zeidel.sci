funcprot(0);
function [] = check(size, A)
    num = 0;
    summ = 0;
    for i = 1:size
        num = abs(A(i, i));
        for j = 1:size
            if(i ~= j) then
                summ = summ + abs(A(i, j));
            end
        end
        if(num < summ) then
            disp('Условие диагонального преобладания не выполнено!');
            abort;
        end
        summ = 0;
    end
endfunction
function[X] = findX(size, method, b, A, tempX)
    if(method == 1) then
        for i = 1:size
            X(i, 1) = b(i, 1);
            for j = 1:size
                if(i ~= j) then
                    X(i, 1)=X(i, 1)-A(i, j)*tempX(j, 1);
                end
            end
            X(i,1) = X(i, 1) / A(i, i);
        end
    end
    if(method == 2) then
        for i = 1:size
            X(i, 1)=b(i, 1);
            for j = 1:i
                if(i ~= j) then
                    X(i, 1) = X(i, 1) - A(i, j) * X(j, 1);
                end
            end
            for j = i:size
                if(i ~= j) then
                    X(i, 1) = X(i, 1) - A(i, j) * tempX(j, 1);
                end
            end
            X(i, 1) = X(i, 1) / A(i, i);
        end
    end
endfunction
function[iterat, X, tempX] = func(E, size, b, A, method, iterat, X, tempX)
    Max = 0;
    while 1
        [X] = findX(size, method, b, A, tempX);
        iterat = iterat + 1;
        Max=abs(X(1, 1) - tempX(1, 1));
        for i = 2:size
            if(Max < abs(X(i, 1) - tempX(i, 1))) then
                Max = abs(X(i, 1) - tempX(i, 1));
            end
        end
        if(Max < E) then
            return
        end
        for i = 1:size
            tempX(i, 1)=X(i, 1);
        end
    end
endfunction
disp('Лабораторная работа 1.2');
disp('Введите размер матрицы:')
size = input('>>> ');
b = zeros(size, 1);
A = zeros(size, size);
//A = read("matr.txt", size, size);
matrix = read("matr.txt", size, size+1);
for i = 1:size
    for j = 1:size
        A(i, j) = matrix(i, j);
    end
    b(i) = matrix(i, 4);
end



E = 0.001;

X = zeros(size, 1);
iterat = 0;


disp('Матрица A');
disp(A);
disp('Вектор b');
disp(b);

check(size, A);
tempX = zeros(size, 1)


[iterat, X, tempX] = func(E, size, b, A, 1, iterat, X, tempX);


disp('====================================================');
disp('Метод Якоби');
disp('Решение:');
disp(X);
disp('Итераций:');
disp(iterat);

for i=1:size
    X(i,1)=0;
    tempX(i,1)=0;
    F(i,1)=0;
end
iterat = 0;
d = 0;


[iterat, X, tempX] = func(E, size, b, A, 2, iterat, X, tempX);


disp('====================================================');
disp('Метод Гаусса-Зейделя');
disp('Решение:');
disp(X);
disp('Итераций:');
disp(iterat);

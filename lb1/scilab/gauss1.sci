disp('Лабораторная работа 1: метод Гаусса')
Matrix = read("matr.txt", -1, 4);
copyMatrix = Matrix;
disp(Matrix,"Исходная матрица:")
n = length(Matrix(:,1));;

j = 1;

tic;
for i=1:n
    bla = 1;
    tmp = Matrix(i,i);
    while tmp == 0
        if bla >= n then
            disp("Wrong matrix!")
            exit;
        end;
        swap = Matrix(i, :);
        Matrix(i, :) = Matrix(bla, :);
        Matrix(bla, :) = swap;
        tmp = Matrix(i,i);
        bla = bla + 1;
    end;
    bla = 0;
    Matrix(i,i) = 1;
    for j=n+1:-1:i
        Matrix(i,j) = Matrix(i,j)/tmp;
    end;
    for j = i+1:1:n
        tmp = Matrix(j,i);
        Matrix(j,i) = 0;
        for k = n+1:-1:i+1
            Matrix(j,k) = Matrix(j,k) - tmp*Matrix(i,k);
        end;
    end;
end;
toc;
disp(toc(),"Время на прямой ход:");

tic;
solution = [0 0 0];
solution(n) = Matrix(n,n+1);
for i=n-1:-1:1
    solution(i) = Matrix(i,n+1);
    for j = i+1:1:n
        solution(i) = solution(i) - Matrix(i,j) * solution(j);
    end;
end;
disp(toc(),"Время на обратный ход:");

format(15);
disp(solution,"Решение:");

disp("Вектор невязки:");
neviaz = [0 0 0];
for i = 1:1:n
    for j = 1:1:n
        neviaz(i) = neviaz(i) + copyMatrix(i,j)*solution(j);
    end;
end;

for i=1:1:n
    neviaz(i) = neviaz(i) - copyMatrix(i,n+1);
end;
disp(neviaz);


delta = neviaz(1);
for i = 1:1:n
    if abs(neviaz(i)) > delta then
        delta = abs(neviaz(i));
    end;
end;
disp("Норма вектора невязки:");
disp(delta);

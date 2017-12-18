// считываем матрицу из файла matrix.txt
X = read("matrix.txt", -1, 4);
n = length(X(:,1));

disp('Данная матрица');
disp(X);

Z = X;
max_el = 0;
max_el_row = 1;
L = 1;
tic();

// прямой ход метода Гаусса
for i = 1:n
	for j = i:n do
		if abs(X(j,i)) > max_el then
			max_el_row = j;
			max_el = abs(X(j,i));
			end;
		end;
	max_el = 0;
	for t = 1:n+1
		tmp_address = X(max_el_row,t);
		X(max_el_row,t) = X(L,t);
		X(L,t) = tmp_address;
		end;
	for k= 1+L:n
		tmpf = X(k,i)/X(L,i);
		for l = 1:n+1
			if abs(tmpf) == 0 then
				break;
			end
		tmpf2 = (X(L,l)*tmpf);
		t3 = X(k,l)-tmpf2;
		X(k,l) = t3;
		end;
	end;
L = L+1;
end
disp('Время, затраченное на прямой ход');
disp(toc());
disp('Полученная треугольная матрица');
disp(X);
Y = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
tic();
// обратный ход метода Гаусса
for i = n:-1:1
	s = 0;
	for j=n:-1:i
		s = s + Y(j)*X(i,j);
		end;
	r = X(i,n+1)-s;
	Y(i) = r/X(i,i);
	if Y(i) == 0 then
		Y(i) = abs(Y(i));
		end
	end

disp('Время, затраченное на обратный ход');
disp(toc());
disp('Результаты вычислений')
for i = 1:n
	disp(Y(i));
	end

S = [0 0 0]
fault = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
disp('Вектор невязки');
// вычисление вектора невязки
for i = 1:n
	S(i) = 0;
	for j = 1:n
		S(i) = S(i) + Z(i,j)*Y(j);
		end;
	S(i) = Z(i,n+1) - S(i);
	end

max_el = 0;
for i = 1:n
	if abs(S(i)) > max_el then
		max_el_row = i;
		max_el = abs(S(i));
		end
	end

disp('d = ');
disp(abs(S(max_el_row)));
format(20);

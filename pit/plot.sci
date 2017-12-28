X = read("sort_dots.txt", -1, 2);
n = length(X(:,1));
disp(X)
xlabel('X(мм)');
ylabel('Y(мм)');
title('график по точкам')

for i = 1:n
	A(i) = X(i, 1)
	B(i) = X(i, 2)
	end;
plot2d(A, B, style=[color("black")])
legend('x');
xset("thickness",1);
xgrid();

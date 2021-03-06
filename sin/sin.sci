x = -%pi*5:0.1:%pi*5;
xlabel('X(мм)');
ylabel('Y(мм)');
title('Графики синуса и синусов, разложенных в ряды Тейлора')
xset("thickness",3);
y1 = x;
y3 = x-(x.^3)/6;
y5 = x-(x.^3)/6+(x.^5)/factorial(5);
y7 = x-(x.^3)/6+(x.^5)/factorial(5)-(x.^7)/factorial(7);
y9 = x-(x.^3)/6+(x.^5)/factorial(5)-(x.^7)/factorial(7)+(x.^9)/factorial(9);
y11 = x-(x.^3)/6+(x.^5)/factorial(5)-(x.^7)/factorial(7)+(x.^9)/factorial(9)-(x.^11)/factorial(11);
y = sin(x);
plot2d(x, y, style=[color("black")], rect=[-16,-4, 16,4]);
plot2d(x, y1, style=[color("red")], rect=[-16,-4, 16,4]);
plot2d(x, y3, style=[color("pink")], rect=[-16,-4, 16,4]);
plot2d(x, y5, style=[color("yellow")], rect=[-16,-4, 16,4]);
plot2d(x, y7, style=[color("blue")], rect=[-16,-4, 16,4]);
plot2d(x, y9, style=[color("orange")], rect=[-16,-4, 16,4]);
plot2d(x, y11, style=[color("green")], rect=[-16,-4, 16,4]);
legend('sin (x)', 'y1', 'y3', 'y5', 'y7', "y9", "y11");
xset("thickness",1);
xgrid();

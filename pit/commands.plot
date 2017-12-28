set xlabel "x(мм)"
set ylabel "y(мм)"
set terminal png
set output "pit.png"

plot "sort_dots.txt" with lines title "pit"

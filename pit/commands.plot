set xlabel "x"
set ylabel "y"
set terminal png
set output "pit.png"

plot "sort_dots.txt" with lines title "pit"

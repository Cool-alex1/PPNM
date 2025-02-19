set terminal svg background "white"
set output "plot.test.svg"

set xlabel "x"
set ylabel "y"

set key out

plot [0: 2*pi][-2:2]\
    sin(x) with lines title "sin(x) label"\
    ,cos(x) with lines title "cos(x) label"
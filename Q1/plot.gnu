

set ylabel 'Speedup'
set xlabel 'p (number of threads)'
set grid
set term png
set output 'Speedup.png'
set datafile separator ","

plot 'out-262144.csv' using 1:3 with linespoints title "n=262144",'out-1048576.csv' using 1:3 with linespoints title "n=1048576",'out-4194304.csv' using 1:3 with linespoints title "n=4194304"



set ylabel 'Tp (parallel time)'
set xlabel 'p (number of threads)'
set grid
set term png
set output 'Times.png'
set datafile separator ","

plot 'out-262144.csv' using 1:2 with linespoints title "n=262144",'out-1048576.csv' using 1:2 with linespoints title "n=1048576",'out-4194304.csv' using 1:2 with linespoints title "n=4194304"

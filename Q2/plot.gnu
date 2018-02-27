unset key

set key top right
set ylabel 'Tp (parallel time)'
set xlabel 'p (number of threads)'
set grid
set term png
set output 'Times.png'
set datafile separator ","
plot 'out-2000-2000.csv' using 1:2 with linespoints title "2000*2000",'out-3000-3000.csv' using 1:2 with linespoints title "3000*3000",'out-4000-4000.csv' using 1:2 with linespoints title "4000*4000",'out-5000-5000.csv' using 1:2 with linespoints title "5000*5000"

set key bottom right
set ylabel 'Speedup'
set xlabel 'p (number of threads)'
set grid
set term png
set output 'Speedup.png'
set datafile separator ","
plot 'out-2000-2000.csv' using 1:3 with linespoints title "2000*2000",'out-3000-3000.csv' using 1:3 with linespoints title "3000*3000",'out-4000-4000.csv' using 1:3 with linespoints title "4000*4000",'out-5000-5000.csv' using 1:3 with linespoints title "5000*5000"

set key top right
set ylabel 'Efficiency'
set xlabel 'p (number of threads)'
set grid
set term png
set output 'Efficiency.png'
set datafile separator ","
plot 'out-2000-2000.csv' using 1:4 with linespoints title "2000*2000",'out-3000-3000.csv' using 1:4 with linespoints title "3000*3000",'out-4000-4000.csv' using 1:4 with linespoints title "4000*4000",'out-5000-5000.csv' using 1:4 with linespoints title "5000*5000"

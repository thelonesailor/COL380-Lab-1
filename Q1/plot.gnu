unset key

set key top right
set ylabel 'Tp (parallel time)'
set xlabel 'p (number of threads)'
set grid
set term png
set output 'Times.png'
set datafile separator ","
plot 'out-4194304.csv' using 1:2 with linespoints title "n=2^{22}",'out-16777216.csv' using 1:2 with linespoints title "n=2^{24}",'out-67108864.csv' using 1:2 with linespoints title "n=2^{26}",'out-268435456.csv' using 1:2 with linespoints title "n=2^{28}"

set key bottom right
set ylabel 'Speedup'
set xlabel 'p (number of threads)'
set grid
set term png
set output 'Speedup.png'
set datafile separator ","
plot 'out-4194304.csv' using 1:3 with linespoints title "n=2^{22}",'out-16777216.csv' using 1:3 with linespoints title "n=2^{24}",'out-67108864.csv' using 1:3 with linespoints title "n=2^{26}",'out-268435456.csv' using 1:3 with linespoints title "n=2^{28}"

set key top right
set ylabel 'Efficiency'
set xlabel 'p (number of threads)'
set grid
set term png
set output 'Efficiency.png'
set datafile separator ","
plot 'out-4194304.csv' using 1:4 with linespoints title "n=2^{22}",'out-16777216.csv' using 1:4 with linespoints title "n=2^{24}",'out-67108864.csv' using 1:4 with linespoints title "n=2^{26}",'out-268435456.csv' using 1:4 with linespoints title "n=2^{28}"

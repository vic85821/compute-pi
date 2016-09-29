reset
set xlabel 'N'
set ylabel 'time(sec)'
set style fill solid
set key left
set grid
set title 'compute pi time'
set term png enhanced font 'Verdana,10'
set datafile separator ","
set output 'runtime.png'

plot "result_clock_gettime_thread.csv" using 1:3 title 'openmp_2' with lines lt rgb "#FF7700", \
     "" using 1:4 title 'openmp_4' with lines lt rgb "#FFD700", \
     "" using 1:7 title 'openmp_8' with lines lt rgb "#7FFF00", \
     "" using 1:8 title 'openmp_16' with lines lt rgb "#0000FF"


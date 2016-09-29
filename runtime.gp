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

plot  "result_clock_gettime_refine.csv" using 1:2 title 'baseline' with lines lt rgb "#FF0000", \
     "" using 1:3 title 'openmp_2' with lines lt rgb "#FF4500", \
     "" using 1:4 title 'openmp_4' with lines lt rgb "#FFD700", \
     "" using 1:5 title 'avx' with lines lt rgb "#7FFF00", \
     "" using 1:6 title 'avxunroll' with lines lt rgb "#0000FF", \
     "" using 1:7 title 'leibniz_baseline' with lines lt rgb "#4B0082", \
     "" using 1:8 title 'eular_baseline' with lines lt rgb "#8B4513"

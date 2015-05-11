file(x) = sprintf("%s.%s", file, x)

set title file
set xlabel "X-axis"
set xrange [0:3.14159265358979323846]
set ylabel "Y-axis"
set yrange [0:3.14159265358979323846]
set zlabel "u(x,y)"


set term png size 1280,1024
set output file("png")
set grid
set key off
splot file('txt') using 1:2:3 with points palette pointsize 1 pointtype 7

#To get whole directory, run: for f in *.txt; do gnuplot -e "file='${f%.*}'" gnuplot_cmd.gs; done

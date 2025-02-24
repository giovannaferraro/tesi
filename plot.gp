reset
set terminal pngcairo size 800,600
set output "latency_candlestick.png"

set title "Latency Distribution Over 100 CAM Messages"
set xlabel "Sample Index"
set ylabel "Latency (ms)"

set style fill transparent solid 0.4
set boxwidth 0.5 absolute
set grid

# Define quartiles
stats "latency_data.txt" using 1 nooutput
lower_quartile = STATS_min + (STATS_median - STATS_min) * 0.25
upper_quartile = STATS_median + (STATS_max - STATS_median) * 0.25

# Candlestick (boxplot) style
plot "latency_data.txt" using (column(0)):1:(lower_quartile):(upper_quartile):(STATS_max) with candlesticks lw 2 lc rgb "blue" title "Latency Distribution"


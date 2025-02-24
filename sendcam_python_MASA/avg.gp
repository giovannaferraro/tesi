reset
set terminal pngcairo size 800,600
set output "latency_plot_2.png"

# Set plot title and labels
set title "Latency Distribution"
set xlabel "Sample Index"
set ylabel "Latency (ms)"
set grid

# Read latency data from the file and plot
plot "test_5.txt" using 1 with linespoints title "Latencies"

# Calculate the average latency
average_latency = system("awk '{s+= $1} END {print s/NR}' test_5.txt")

# The average_latency is a string, so we need to convert it to a number
# Let's force evaluation of the system result and print it
average_latency = real(average_latency)

# Add a line for the average latency
set arrow from 0, average_latency to 1000, average_latency nohead lw 2 lt rgb "red"
set label sprintf("Avg: %.3f", average_latency) at 10, average_latency+0.5


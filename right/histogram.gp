# Set the output to a JPEG file
set terminal jpeg size 1024,768
set output 'plots_4.jpg'

# Create a 2x1 layout (2 plots stacked vertically)
set multiplot layout 2,1 title "Two Separate Plots" rowsfirst

# First plot for the first column
set title "Plot for First Column"
set xlabel "Index"
set xtics 30
set ylabel "First Column Value"
plot "haura-e9-ef-21_right40.txt" using (column(0)):1 with linespoints title "First Column"



# Second plot for the second column
set title "Plot for Second Column"
set xlabel "Index"
set xtics 30
set ylabel "Second Column Value"
plot "haura-e9-ef-21_right40.txt" using (column(0)):2 with linespoints title "Second Column"

# End the multiplot
unset multiplot

# Close the output
set output


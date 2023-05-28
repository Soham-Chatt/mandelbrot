#!/bin/bash

set -e  # Exit on error

# Define a function that will run when an error occurs
function error_exit {
    echo "An error occurred. Exiting the script."
    exit 1
}

echo "Starting the program."
make animation
./animation
echo "Program completed. Converting the PMMs to an mp4."

ffmpeg -framerate 24 -i frames/mandelbrot_%04d.ppm -c:v libx264 -pix_fmt yuv420p out.mp4
rm -r frames
echo "Conversion completed."
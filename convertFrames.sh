#!/bin/bash

set -e  # Exit on error

# Define a function that will run when an error occurs
function error_exit {
    echo "An error occurred. Exiting the script."
    exit 1
}

ffmpeg -framerate 60 -i frames/mandelbrot_%04d.ppm -c:v libx264 -pix_fmt yuv420p out.mp4
rm -r frames
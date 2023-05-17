#!/bin/bash

set -e  # Exit on error

# Define a function that will run when an error occurs
function error_exit {
    echo "An error occurred. Exiting the script."
    exit 1
}

# Set the trap to call the error_exit function on error
trap error_exit ERR

# Build the program
make

# Run the program
./mandelbrot

# Convert the image
echo "Program completed. Converting the PMM to TIFF."
vips im_vips2tiff output.ppm output.tif
echo "Conversion completed."
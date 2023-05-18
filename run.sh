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

# Select the type and run the program
echo "Select the type: Mandelbrot (1) or Buddhabrot (2)"
read -r choice
if [ "$choice" -eq 1 ]
then
  echo "You selected Mandelbrot. Starting the program."
  ./mandelbrot
elif [ "$choice" -eq 2 ]
then
  echo "You selected Buddhabrot. Starting the program."
  ./buddhabrot
  else
    echo "Invalid input. Exiting the script."
    exit 2
fi

echo "Program completed. Converting the PMM to TIFF."

# Get the latest ppm file and convert it to tiff
latest_ppm=$(find . -maxdepth 1 -name '*.ppm' -printf '%T@ %p\n' | sort -n | tail -1 | cut -f2- -d" ")
vips im_vips2tiff "$latest_ppm" "${latest_ppm%.ppm}.tiff"
rm "$latest_ppm"

echo "Conversion completed. Please check the info.txt file for more information."
#!/bin/bash

set -e  # Exit on error

# Define a function that will run when an error occurs
function error_exit {
    echo "An error occurred. Exiting the script."
    exit 1
}

# Set the trap to call the error_exit function on error
trap error_exit ERR

make clean
make
./mandelbrot

# Get the latest ppm file and convert it to tiff
latest_ppm=$(find . -maxdepth 1 -name '*.ppm' -printf '%T@ %p\n' | sort -n | tail -1 | cut -f2- -d" ")
latest_info=$(find . -maxdepth 1 -name '*.txt' -printf '%T@ %p\n' | sort -n | tail -1 | cut -f2- -d" ")

# Create a variable for the directory name, stripping the .ppm extension from the file
dir_name="${latest_ppm%.ppm}"

vips im_vips2tiff "$latest_ppm" "${dir_name}.tiff"

# For a quick run, we need only the basic name else create a new directory
mkdir "$dir_name"
mv "${dir_name}.tiff" "$dir_name"
rm "$latest_ppm"
mv "$latest_info" "$dir_name"

./transfer.sh "$dir_name"

echo "Conversion completed. Please check the info.txt file for more information."
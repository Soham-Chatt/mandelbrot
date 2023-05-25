#!/bin/bash

set -e  # Exit on error

# Define a function that will run when an error occurs
function error_exit {
    echo "An error occurred. Exiting the script."
    exit 1
}

# Run the program
echo "Starting the program."
make
./mandelbrot
echo "Program completed. Converting the PMM to TIFF."

# Get the latest ppm file and convert it to tiff
latest_ppm=$(find . -maxdepth 1 -name '*.ppm' -printf '%T@ %p\n' | sort -n | tail -1 | cut -f2- -d" ")
latest_info=$(find . -maxdepth 1 -name '*.txt' -printf '%T@ %p\n' | sort -n | tail -1 | cut -f2- -d" ")

filesize_ppm=$(du -h "$latest_ppm" | cut -f1)
echo "PPM filesize: $filesize_ppm" >> "$latest_info"

# Create a variable for the directory name, stripping the .ppm extension from the file
dir_name="${latest_ppm%.ppm}"

vips im_vips2tiff "$latest_ppm" "${dir_name}.tiff"

# Get the size of the TIFF file
filesize_tiff=$(du -h "${dir_name}.tiff" | cut -f1)
echo "TIFF filesize: $filesize_tiff" >> "$latest_info"

# Create a new directory
mkdir "$dir_name"
mv "${dir_name}.tiff" "$dir_name"
rm "$latest_ppm"
mv "$latest_info" "$dir_name"

# Check if nohup.txt exists and create the processing info file
if [ -f "nohup.out" ]; then
    timestamp="${dir_name##*mandelbrot_}"
    awk '/0/,0' nohup.out | head -n -1 > "${dir_name}/processingInfo_${timestamp}.txt"
    rm nohup.out
fi

echo "Conversion completed. Please check the info.txt file in directory ${dir_name} for more information."

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
echo "Quick run? (y/n)"
read -r quick
if [ "$quick" = "y" ]
then
  echo "You selected yes. Deleting all previous output files and building the program."
  make clean
  make
elif [ "$quick" = "n" ]
then
  echo "You selected no. Building the program normally."
  make
else
  echo "Invalid input. Exiting the script."
  exit 2
fi

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
latest_info=$(find . -maxdepth 1 -name '*.txt' -printf '%T@ %p\n' | sort -n | tail -1 | cut -f2- -d" ")

# Create a variable for the directory name, stripping the .ppm extension from the file
dir_name="${latest_ppm%.ppm}"

vips im_vips2tiff "$latest_ppm" "${dir_name}.tiff"

# For a quick run, we need only the basic name else create a new directory
if [ "$quick" = "y" ]
then
  mv "${dir_name}.tiff" "output.tiff"
  mv "$latest_info" "info.txt"
  rm "$latest_ppm"
  else
    mkdir "$dir_name"
      mv "${dir_name}.tiff" "$dir_name"
      rm "$latest_ppm"
      mv "$latest_info" "$dir_name"
fi

echo "Conversion completed. Please check the info.txt file for more information."
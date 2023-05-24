#!/bin/bash

set -e  # Exit on error

# Define a function that will run when an error occurs
function error_exit {
    echo "An error occurred. Exiting the script."
    exit 1
}

# Set the trap to call the error_exit function on error
trap error_exit ERR

# Create the stripped down file
echo "Stripping down the file"
sed '1,2d' nohup.out > processing.txt

# Run the script
echo "Running the script"
source venv/bin/activate
python3 plot.py
deactivate

rm processing.txt

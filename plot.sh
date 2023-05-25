#!/bin/bash
# Create the stripped down file
echo "Stripping down the file"
awk '/Processing/,0' nohup.out > processing.txt

# Run the script
echo "Running the script"
source venv/bin/activate
python3 plot.py
deactivate

rm processing.txt

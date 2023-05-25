#!/bin/bash
# Create the stripped down file
echo "Stripping down the file"
awk '/0/,0' nohup.out > processing.txt

# Run the script
echo "Running the script"
source venv/bin/activate
python3 trainModel.py
deactivate

rm processing.txt

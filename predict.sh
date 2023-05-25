#!/bin/bash
# Run the script
echo "Running the script"
source venv/bin/activate
python3 trainModel.py
deactivate

rm processing.txt

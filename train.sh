#!/bin/bash

while :; do
    nohup ./run.sh

    # Get the newest directory with the name 'mandelbrot_*'
    newest_dir=$(find . -type d -name "mandelbrot_*" -print0 | xargs -0 ls -td | head -n 1)

    # Find the infoMandelbrot_*.txt file in the newest directory
    info_file=$(find "${newest_dir}" -type f -name "infoMandelbrot_*.txt" -print0 | xargs -0 ls -t | head -n 1)

    width=$(grep 'Width' "${info_file}" | awk '{print $2}')
    height=$(grep 'Height' "${info_file}" | awk '{print $2}')
    max_iterations=$(grep 'Max iterations' "${info_file}" | awk '{print $3}')
    palette_size=$(grep 'Palette size' "${info_file}" | awk '{print $3}')
    total_duration=$(grep 'Total duration' "${info_file}" | awk '{print $3}' | sed 's/[^0-9]*//g')

    # Write values to CSV file
    echo "$width,$height,$max_iterations,$palette_size,$total_duration" >> data.csv
    rm -r "$newest_dir"

done
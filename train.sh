#!/bin/bash

for i in {1..5}
do
    echo "Starting run $i"
    nohup ./run.sh

    # Get the newest directory with the name 'mandelbrot_*'
    newest_dir=$(ls -td mandelbrot_*/ | head -n 1)

    # Find the infoMandelbrot_*.txt file in the newest directory
    info_file=$(ls -t "${newest_dir}"infoMandelbrot_*.txt | head -n 1)

    width=$(grep 'Width' "${info_file}" | awk '{print $2}')
    height=$(grep 'Height' "${info_file}" | awk '{print $2}')
    max_iterations=$(grep 'Max iterations' "${info_file}" | awk '{print $3}')
    palette_size=$(grep 'Palette size' "${info_file}" | awk '{print $3}')
    total_duration=$(grep 'Total duration' "${info_file}" | awk '{print $3}' | sed 's/[^0-9]*//g')
    ppm_filesize=$(grep 'PPM filesize' "${info_file}" | awk '{print $3}' | sed 's/[^0-9]*//g')
    tiff_filesize=$(grep 'TIFF filesize' "${info_file}" | awk '{print $3}' | sed 's/[^0-9]*//g')
    # Write values to CSV
    echo "$width,$height,$max_iterations,$palette_size,$ppm_filesize,$tiff_filesize,$total_duration" >> data.csv

    rm "$newest_dir"
    i=$((i+1))
done
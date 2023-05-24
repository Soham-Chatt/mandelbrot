#!/bin/bash

pid=$(pidof mandelbrot)

while :; do
    # Check if process is running
    if ! ps -p "$pid" > /dev/null; then
        echo "Process $pid no longer exists. Exiting script."
        exit 1
    fi

    # Check if disk space is running low
    low_space=$(df | awk '$1 == "/dev/root" && $4 < 500000 { print "low" }')

    if [ "$low_space" = "low" ]; then
        echo "Too little disk space remaining. Killing the program."
        kill -9 "$pid"
        echo "Script successfully exited"
        exit 0
    fi

    sleep 1m;
done

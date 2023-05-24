#!/bin/bash
pid=$(pidof mandelbrot)

while :; do
    # Check if process is running
    if ! ps -p $pid > /dev/null; then
        echo "Process $pid no longer exists. Exiting script."
        # Send an email when process is no longer running
        echo "Process $pid is no longer running." | mail -s "Mandelbrot rendering has finished" neel.delft@gmail.com
        exit 1
    fi
    sleep 15m;
done
#!/bin/bash
pid=$(pidof mandelbrot)
pid2=$(pidof vips)
attachment=$(find . -maxdepth 1 -name '*.txt' -printf '%T@ %p\n' | sort -n | tail -1 | cut -f2- -d" ")

while :; do
    # Check if process is running
    if ! ps -p "$pid" > /dev/null; then
      if ! ps -p "$pid2" > /dev/null; then
        echo "Process $pid no longer exists. Exiting script."
        # Send an email when process is no longer running
        echo "Process $pid is no longer running." | mutt -s "Mandelbrot rendering has finished" -a "$attachment" -- neel.delft@gmail.com
        exit 1
      fi
    fi
    sleep 15m;
done
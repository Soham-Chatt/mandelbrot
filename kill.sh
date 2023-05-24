#!/bin/bash
pid=11330

while :; do
    # Check if process is running
    if ! ps -p $pid > /dev/null; then
        echo "Process $pid no longer exists. Exiting script."
        exit 1
    fi

    # Check if disk space is running low
    df | awk '
    if ($1 == "/dev/root" && $4 < 500000) {
        echo "Too little disk space remaining. Killing the program.";
        exit 1;
    }'

    if [ $? -eq 1 ]; then
        kill -9 $pid;
        echo "Script successfully exited"
        exit 0;
    fi

    sleep 1m;
done

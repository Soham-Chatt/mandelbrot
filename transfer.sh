#!/bin/bash
username="soham"
password="Soham_2018"
host="172.21.181.190"
base_dir="/home/soham/documents/github/mandelbrot_data/"

# Check if directory name argument is provided
if [ "$1" -eq 0 ]; then
    echo "No directory name provided. Usage: ./script.sh <directory_name>"
    exit 1
fi


/usr/bin/expect << EOF
spawn scp -r $username@$host:$1 $base_dir
expect {
    "password:" {
        send "$password\r"
    }
    "yes/no" {
        send "yes\r"
        exp_continue
    }
}
interact
EOF
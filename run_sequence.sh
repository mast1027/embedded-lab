#!/bin/bash

# Directory containing the .txt files
directory="./satellite_data"
executable="./cmake-build-debug/embedded_lab"

# Loop over every .txt file in the specified directory
for file in "$directory"/*.txt; do
    # Check if the file exists to handle the case of no matching files
    if [ -e "$file" ]; then
        absPath=$(realpath "$file")

        echo "###################### Processing $absPath ################################"
        $executable "$file"
        echo
    else
        echo "No .txt files found in $directory."
        break
    fi
done
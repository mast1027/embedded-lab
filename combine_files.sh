#!/bin/bash
# This script combines all header and source files into a single C++ file, appending main.cpp last.

# Create or empty the combined file
combined_file="combined_main.cpp"
if [ -f $combined_file ]; then
    rm $combined_file
fi
echo "// Combined C++ source file" > $combined_file

# Append all header files content
for file in *.h; do
    echo "// Content from $file" >> $combined_file
    cat $file >> $combined_file
    echo "" >> $combined_file # Adding a newline for better separation
done

# Append all source files content, except main.cpp
for file in $(ls *.cpp | grep -v "main.cpp"); do
    echo "// Content from $file" >> $combined_file
    cat $file >> $combined_file
    echo "" >> $combined_file # Adding a newline for better separation
done

# Append main.cpp last
echo "// Content from main.cpp" >> $combined_file
cat main.cpp >> $combined_file

# remove #include "timer.h" from combined file
sed -i '/#include "timer.h"/d' $combined_file
# remove #include #include "Satellite.h" from combined file
sed -i '/#include "Satellite.h"/d' $combined_file
# remove #include "globals.h" from combined file
sed -i '/#include "globals.h"/d' $combined_file
# remove #include "SatelliteNetwork.h" from combined file globally
sed -i '/#include "SatelliteNetwork.h"/d' $combined_file

echo "" >> $combined_file # Adding a newline for better separation

echo "All files have been combined into $combined_file."
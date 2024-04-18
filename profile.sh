#!/bin/bash
set-e

EXECUTABLE_FOLDER="./cmake-build-release"
EXECUTABLE="${EXECUTABLE_FOLDER}/embedded_lab"
INPUT_FILE="satellite_data/gps_sequence_1.txt"
DATE_PREFIX=$(date +"%Y-%m-%d_%H-%M-%S")
SUBFOLDER="05_use_double_sequence_storage"
PROFILING_DATA_FOLDER="profiling_data/${SUBFOLDER}"
mkdir -p $PROFILING_DATA_FOLDER
GPROF_OUTPUT="${PROFILING_DATA_FOLDER}/${DATE_PREFIX}_gprof_output.txt"
CALLGRIND_OUTPUT="${PROFILING_DATA_FOLDER}/${DATE_PREFIX}_callgrind.out"
PERF_OUTPUT="${PROFILING_DATA_FOLDER}/${DATE_PREFIX}_perf.data"
TEMP_STDOUT="${PROFILING_DATA_FOLDER}/temp_stdout.txt"
OUT_TXT="${PROFILING_DATA_FOLDER}/${DATE_PREFIX}_internal.txt"

# assert EXECUTABLE exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "EXECUTABLE not found: $EXECUTABLE"
    exit 1
fi

# assert gprof exists
if ! command -v gprof &> /dev/null; then
    echo "gprof not found"
    exit 1
fi

# assert valgrind exists
if ! command -v valgrind &> /dev/null; then
    echo "valgrind not found"
    exit 1
fi

# assert kcachegrind exists
if ! command -v kcachegrind &> /dev/null; then
    echo "kcachegrind not found"
    exit 1
fi

# run executable with valgrind
echo "################# Running executable with valgrind... ################# "
valgrind --tool=callgrind --callgrind-out-file="$CALLGRIND_OUTPUT" "$EXECUTABLE" "$INPUT_FILE"
echo "Callgrind output saved to: $CALLGRIND_OUTPUT"
sleep 2

# generate gprof output
echo "################# Generating gprof output... ################# "
"$EXECUTABLE" "$INPUT_FILE"
gprof -b "$EXECUTABLE" gmon.out > "$GPROF_OUTPUT"
echo "GPROF output saved to: $GPROF_OUTPUT"

# generate perf output
echo "################# Generating perf output... ################# "
perf record -o "$PERF_OUTPUT" -g -F 99 -- "$EXECUTABLE" "$INPUT_FILE" > "$TEMP_STDOUT"
grep -- '--------->' "$TEMP_STDOUT" > "$OUT_TXT"
echo "Perf output saved to: $PERF_OUTPUT"
echo "Internal output saved to: $OUT_TXT"

rm gmon.out $TEMP_STDOUT
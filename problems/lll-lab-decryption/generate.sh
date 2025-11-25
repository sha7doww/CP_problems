#!/bin/bash

# Data generation script for lll-lab-decryption problem

# Change to script directory to ensure data is generated in the correct location
cd "$(dirname "$0")"

echo "Generating test data for LLL Lab Decryption Challenge..."

# Create data directory if it doesn't exist
mkdir -p data

echo "Generating sample data..."

# Sample 1: 有解 (770 77 5 -> 2 385)
echo "770 5 77" > data/sample_1.in

# Sample 2: 无解 (633 1 211 -> NO)
echo "633 211 1" > data/sample_2.in

echo "Generating test data..."

# Small data (10 tests, all have solutions)
echo "Generating small data (1-10)..."
for i in {1..10}; do
    ./generator small $i > data/small_$i.in
done

# Medium data (20 tests, 18 have solutions, 2 no solution)
echo "Generating medium data (1-20)..."
for i in {1..18}; do
    ./generator medium $i > data/medium_$i.in
done

# Medium 19-20: no solution
for i in {19..20}; do
    ./generator no_solution $i > data/medium_$i.in
done

# Large data (20 tests, 17 have solutions, 3 no solution)
echo "Generating large data (1-20)..."
for i in {1..17}; do
    ./generator large $i > data/large_$i.in
done

# Large 18-20: no solution
for i in {18..20}; do
    ./generator no_solution $((i + 20)) > data/large_$i.in
done

echo "Generated $(find data -name "*.in" | wc -l) input files."

# List generated files
echo "Generated input files:"
ls -la data/*.in | wc -l
echo "files created."

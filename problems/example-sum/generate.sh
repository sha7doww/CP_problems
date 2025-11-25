#!/bin/bash

# Data generation script for example-sum problem

echo "Generating test data for example-sum problem..."

# Create data directory if it doesn't exist
mkdir -p data

# Generate different types of test cases
echo "Generating test cases..."

# Test 1: Simple positive numbers
./generator positive > data/test_1.in

# Test 2: Mixed positive and negative
./generator random > data/test_2.in

# Test 3: Maximum values
./generator max > data/max.in

# Test 4: Minimum values
./generator min > data/min.in

# Test 5: Zero values
./generator zero > data/zero.in

# Test 6-8: More random tests
for i in {6..8}; do
    ./generator random > data/random_$i.in
done

# Test 9: Large positive numbers
echo "999999999 888888888" > data/large_pos.in

# Test 10: Large negative numbers
echo "-999999999 -888888888" > data/large_neg.in

echo "Generated $(find data -name "*.in" | wc -l) input files."

# List generated files
echo "Generated input files:"
ls -la data/*.in
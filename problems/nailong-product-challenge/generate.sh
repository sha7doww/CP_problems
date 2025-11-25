#!/bin/bash

# Data generation script for nailong-product-challenge problem

# Change to script directory to ensure data is generated in the correct location
cd "$(dirname "$0")"

echo "Generating test data for nailong-product-challenge problem..."

# Create data directory if it doesn't exist
mkdir -p data

# Generate different types of test cases
echo "Generating test cases..."

# Sample test cases (must match statement.md)
echo "Generating sample data..."
echo "1 2 3 4 5 6 7 8 9 10" > data/sample_1.in
./generator primes > data/sample_2.in

# Real test cases (use descriptive names, NOT 'sample' prefix)
echo "Generating test data..."

# Test 1: All ones - should output 1
./generator all_ones > data/all_ones.in

# Test 2: Contains zero - should output 0
./generator zero > data/zero.in

# Test 3: Small numbers - should not exceed 10^9
./generator small > data/small.in

# Test 4: Medium numbers - might exceed 10^9
./generator medium > data/medium.in

# Test 5: Large numbers - definitely exceed 10^9
./generator large > data/large.in

# Test 6: Maximum values - should output -1
./generator max > data/max.in

# Test 7: Boundary case - exactly 10^9
./generator boundary > data/boundary.in

# Test 8: Mixed small and large numbers
./generator mixed > data/mixed.in

# Test 9: Custom edge case - multiple zeros
echo "0 0 0 0 0 0 0 0 0 0" > data/all_zeros.in

# Test 10-14: Random tests for thoroughness
# Pass different seed to each random test to generate different data
# random_1 to random_4: safe random (product <= 10^9, output specific value)
# random_5: large random (product > 10^9, output -1)
for i in {1..4}; do
    ./generator random_safe $i > data/random_$i.in
done
./generator random 5 > data/random_5.in

# Test 15: All maximum - should definitely output -1
for i in {1..10}; do
    echo -n "1000000000"
    if [ $i -lt 10 ]; then
        echo -n " "
    fi
done > data/all_max.in
echo "" >> data/all_max.in

# Test 16: Decreasing sequence
echo "10 9 8 7 6 5 4 3 2 1" > data/decreasing.in

echo "Generated $(find data -name "*.in" | wc -l) input files."

# List generated files
echo "Generated input files:"
ls -la data/*.in
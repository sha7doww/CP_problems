#!/bin/bash

# Data generation script for nailong-quantum-entanglement problem
# Total: 2 samples + 20 test cases = 22 files
# Non-sample test cases: 20 (each worth 5 points, total 100 points)

# Change to script directory
cd "$(dirname "$0")"

echo "Generating test data for nailong-quantum-entanglement..."

# Create data directory if it doesn't exist
mkdir -p data

# Clean up old data
rm -f data/*.in data/*.out

# ============================================
# Sample test cases (must match statement.md)
# ============================================
echo "Generating sample data..."

# Sample 1: N=4, K=1 (has solution)
echo "4 1" > data/sample_1.in
echo "1 2 3 4" > data/sample_1.out

# Sample 2: N=3, K=3 (impossible - pigeonhole)
echo "3 3" > data/sample_2.in
echo "-1" > data/sample_2.out

# ============================================
# Test cases: 20 total (100 points)
# ============================================

# --- Boundary tests: 2 cases (10 points) ---
echo "Generating boundary tests..."
./generator boundary_min > data/test_01.in      # N=1, K=0
./generator boundary_n1_k1 > data/test_02.in    # N=1, K=1 (impossible)

# --- Small tests: 4 cases (20 points) ---
echo "Generating small tests..."
./generator small 1 > data/test_03.in
./generator small 2 > data/test_04.in
./generator small 3 > data/test_05.in
./generator small 4 > data/test_06.in

# --- Medium tests: 4 cases (20 points) ---
echo "Generating medium tests..."
./generator medium 1 > data/test_07.in
./generator medium 2 > data/test_08.in
./generator medium 3 > data/test_09.in
./generator medium 4 > data/test_10.in

# --- Large tests: 5 cases (25 points) ---
echo "Generating large tests..."
./generator large 1 > data/test_11.in
./generator large 2 > data/test_12.in
./generator large 3 > data/test_13.in
./generator large 4 > data/test_14.in
./generator large_max_k > data/test_15.in       # N=1000, K=250000 (max)

# --- Impossible tests: 2 cases (10 points) ---
echo "Generating impossible tests..."
./generator impossible_exceed 1 > data/test_16.in       # K > K_max
./generator specific 5 7 > data/test_17.in              # N=5, K=7 (pigeonhole)

# --- K=0 tests: 1 case (5 points) ---
echo "Generating K=0 tests..."
./generator k_zero 1 > data/test_18.in

# --- Random solvable tests: 2 cases (10 points) ---
echo "Generating random tests..."
./generator random_solvable 1 > data/test_19.in
./generator random_solvable 2 > data/test_20.in

# ============================================
# Summary
# ============================================
echo ""
echo "Generated files:"
echo "  - 2 sample files (sample_1, sample_2)"
echo "  - 20 test files (test_01 to test_20)"
echo ""
echo "Point distribution:"
echo "  - Boundary:    2 cases × 5 = 10 points"
echo "  - Small:       4 cases × 5 = 20 points"
echo "  - Medium:      4 cases × 5 = 20 points"
echo "  - Large:       5 cases × 5 = 25 points"
echo "  - Impossible:  2 cases × 5 = 10 points"
echo "  - K=0:         1 case  × 5 =  5 points"
echo "  - Random:      2 cases × 5 = 10 points"
echo "  - Total:      20 cases     = 100 points"
echo ""
ls -la data/*.in

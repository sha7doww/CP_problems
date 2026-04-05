#!/bin/bash

# Sample data (manually created)
cat > data/sample_1.in << 'EOF'
4 5
1 2 1
2 3 2
3 4 3
1 4 10
2 4 4
EOF

cat > data/sample_2.in << 'EOF'
3 2
1 2 5
2 3 5
EOF

# Small test cases with second-best MST (5 cases)
./generator random 5 8 100 1 > data/small_1.in
./generator random 10 20 1000 2 > data/small_2.in
./generator random 20 50 10000 3 > data/small_3.in
./generator random 50 100 100000 4 > data/small_4.in
./generator random 100 300 1000000 5 > data/small_5.in

# Cases with no second-best MST (tree only) (3 cases)
./generator tree 10 9 1000 6 > data/tree_1.in
./generator tree 100 99 1000000 7 > data/tree_2.in
./generator tree 1000 999 1000000000 8 > data/tree_3.in

# Cases with same weight edges (2 cases)
./generator sameweight 100 200 1000 9 > data/same_1.in
./generator sameweight 1000 2000 1000000 10 > data/same_2.in

# Medium test cases (5 cases)
./generator random 5000 15000 1000000000 11 > data/medium_1.in
./generator random 10000 30000 1000000000 12 > data/medium_2.in
./generator random 20000 60000 1000000000 13 > data/medium_3.in
./generator random 30000 90000 1000000000 14 > data/medium_4.in
./generator random 50000 150000 1000000000 15 > data/medium_5.in

# Large test cases (5 cases)
./generator random 100000 300000 1000000000 16 > data/large_1.in
./generator random 80000 240000 1000000000 17 > data/large_2.in
./generator random 100000 200000 1000000000 18 > data/large_3.in
./generator random 90000 270000 1000000000 19 > data/large_4.in
./generator random 100000 300000 1000000000 20 > data/large_5.in

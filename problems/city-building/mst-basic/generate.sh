#!/bin/bash

# Sample data (manually created)
cat > data/sample_1.in << 'EOF'
4 5
1 2 3
1 3 5
2 3 1
2 4 6
3 4 4
EOF

cat > data/sample_2.in << 'EOF'
3 3
1 2 10
2 3 20
1 3 15
EOF

# Small test cases (5 cases)
./generator random 5 5 100 1 > data/small_1.in
./generator random 10 15 1000 2 > data/small_2.in
./generator chain 10 9 100 3 > data/small_3.in
./generator random 20 30 10000 4 > data/small_4.in
./generator random 50 100 100000 5 > data/small_5.in

# Medium test cases (5 cases)
./generator random 1000 2000 1000000 6 > data/medium_1.in
./generator random 5000 10000 100000000 7 > data/medium_2.in
./generator chain 5000 4999 1000000000 8 > data/medium_3.in
./generator random 10000 20000 1000000000 9 > data/medium_4.in
./generator random 10000 30000 1000000000 10 > data/medium_5.in

# Large test cases (5 cases)
./generator random 50000 80000 1000000000 11 > data/large_1.in
./generator random 100000 100000 1000000000 12 > data/large_2.in
./generator chain 100000 99999 1000000000 13 > data/large_3.in
./generator random 80000 100000 1000000000 14 > data/large_4.in
./generator random 100000 100000 1000000000 15 > data/large_5.in

# Edge cases (5 cases)
./generator random 2 1 1 16 > data/edge_min.in
./generator random 100000 99999 1000000000 17 > data/edge_sparse.in
./generator chain 1000 999 1 18 > data/edge_same_weight.in
./generator random 50000 100000 1000000000 19 > data/edge_dense.in
./generator random 100000 100000 1 20 > data/edge_all_one.in

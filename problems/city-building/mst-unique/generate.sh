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
4 5
1 2 3
1 3 3
2 3 1
2 4 4
3 4 4
EOF

# Small test cases - unique MST (5 cases)
./generator random 5 5 100 1 > data/small_unique_1.in
./generator random 10 15 1000 2 > data/small_unique_2.in
./generator random 20 30 10000 3 > data/small_unique_3.in
./generator random 50 100 100000 4 > data/small_unique_4.in
./generator random 100 200 1000000 5 > data/small_unique_5.in

# Small test cases - not unique MST (5 cases)
./generator notunique 10 15 100 6 > data/small_notunique_1.in
./generator sameweight 20 30 1 7 > data/small_notunique_2.in
./generator notunique 50 100 1000 8 > data/small_notunique_3.in
./generator sameweight 100 200 1 9 > data/small_notunique_4.in
./generator notunique 100 200 10000 10 > data/small_notunique_5.in

# Medium test cases (5 cases)
./generator random 5000 10000 1000000000 11 > data/medium_1.in
./generator notunique 5000 10000 100000 12 > data/medium_2.in
./generator random 10000 20000 1000000000 13 > data/medium_3.in
./generator notunique 10000 20000 1000000 14 > data/medium_4.in
./generator sameweight 10000 30000 1 15 > data/medium_5.in

# Large test cases (5 cases)
./generator random 100000 100000 1000000000 16 > data/large_1.in
./generator notunique 100000 100000 1000000 17 > data/large_2.in
./generator random 80000 100000 1000000000 18 > data/large_3.in
./generator notunique 80000 100000 100000 19 > data/large_4.in
./generator sameweight 50000 100000 1 20 > data/large_5.in

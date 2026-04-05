#!/bin/bash

# Sample data
cat > data/sample_1.in << EOF
6
1 3 5 4 7 8
EOF

cat > data/sample_2.in << EOF
5
5 4 3 2 1
EOF

# Small test cases
./generator random 5 100 1 > data/small_1.in
./generator random 10 100 2 > data/small_2.in
./generator increasing 10 100 3 > data/small_3.in
./generator decreasing 10 100 4 > data/small_4.in

# Medium test cases
./generator random 100 1000 5 > data/medium_1.in
./generator random 200 10000 6 > data/medium_2.in
./generator increasing 150 10000 7 > data/medium_3.in
./generator decreasing 150 10000 8 > data/medium_4.in
./generator zigzag 100 1000 9 > data/medium_5.in
./generator same 100 1000 10 > data/medium_6.in

# Large test cases
./generator random 1000 1000000 11 > data/large_1.in
./generator random 1000 1000000 12 > data/large_2.in
./generator random 1000 1000000 13 > data/large_3.in
./generator increasing 1000 1000000 14 > data/large_4.in
./generator decreasing 1000 1000000 15 > data/large_5.in
./generator zigzag 1000 1000000 16 > data/large_6.in
./generator same 1000 1000000 17 > data/large_7.in
./generator random 500 500000 18 > data/large_8.in
./generator random 800 800000 19 > data/large_9.in
./generator random 999 999999 20 > data/large_10.in

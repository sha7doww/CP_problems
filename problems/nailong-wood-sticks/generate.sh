#!/bin/bash

# 样例数据（手动创建，与题目描述一致）
cat > data/sample_1.in << EOF
4 11
802 743 457 539
EOF

cat > data/sample_2.in << EOF
3 5
100 50 30
EOF

# 测试数据生成
# 小数据
./generator small 5 3 50 1 > data/small_1.in
./generator small 10 8 100 2 > data/small_2.in

# 中等数据
./generator uniform 100 50 10000 3 > data/medium_1.in
./generator uniform 500 200 50000 4 > data/medium_2.in

# 大数据
./generator large 1000 500 100000 5 > data/large_1.in
./generator large 5000 2500 10000000 6 > data/large_2.in
./generator large 10000 5000 100000000 7 > data/large_max.in

# 边界数据
./generator edge 10000 10000 100000000 8 > data/edge_all_same.in
./generator uniform 10000 1 100000000 9 > data/edge_k_min.in
./generator small 1 1 100000000 10 > data/edge_n_min.in

# 随机数据
./generator random 1000 500 1000000 11 > data/random_1.in
./generator random 2000 1000 5000000 12 > data/random_2.in
./generator random 3000 1500 10000000 13 > data/random_3.in

# 特殊数据：k 很大
./generator uniform 100 99 1000 14 > data/special_k_large.in

# 特殊数据：所有木棒长度为 1
cat > data/special_all_one.in << EOF
100 50
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
EOF

# 无解数据：k > n 的所有木棒总数
cat > data/impossible.in << EOF
3 20
10 10 10
EOF

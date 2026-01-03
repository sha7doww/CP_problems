#!/bin/bash

# 样例数据 1
cat > data/sample_1.in << 'EOF'
3
7 0 2
15 1 3
1000000000 10 20
EOF

# 样例数据 2
cat > data/sample_2.in << 'EOF'
4
5 0 0
5 1 1
5 2 2
5 0 2
EOF

# 小数据测试
./generator small 10 1 > data/small_1.in
./generator small 20 2 > data/small_2.in

# 随机数据测试
./generator random 50 3 > data/random_1.in
./generator random 100 4 > data/random_2.in
./generator random 500 5 > data/random_3.in

# 大数据测试
./generator large 100 6 > data/large_1.in
./generator large 1000 7 > data/large_2.in

# 边界测试：全 0
./generator edge_zero 50 8 > data/edge_zero.in

# 边界测试：最大值
./generator edge_max 50 9 > data/edge_max.in

# 边界测试：范围测试
./generator edge_range 90 10 > data/edge_range.in

# 特殊测试：2 的幂次
./generator power_of_two 100 11 > data/power_of_two.in

# 特殊测试：全 1 的数
./generator all_ones 100 12 > data/all_ones.in

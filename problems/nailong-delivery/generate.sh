#!/bin/bash

# ========================================
# 样例数据（手动创建，与题目描述一致）
# ========================================

# 样例1：展示陷阱（贪心路径被阻断）
cat > data/sample_1.in << EOF
4 4
1 2 1 10 2
1 2 2 20 1
2 3 0 5 2
3 4 1 7 3
EOF

# 样例2：简单链式路径
cat > data/sample_2.in << EOF
3 2
1 2 1 10 5
2 3 0 8 3
EOF

# ========================================
# 小数据 (4个测试点)
# ========================================
./generator random 10 15 100 50 1 > data/small_1.in
./generator chain 8 10 100 50 2 > data/small_2.in
./generator trap 6 8 100 50 3 > data/small_3.in
./generator random 100 300 1000 500 4 > data/small_4.in

# ========================================
# 链状图 (2个测试点)
# ========================================
./generator chain 1000 1500 10000 5000 5 > data/chain_1.in
./generator chain 50000 75000 1000000 500000 6 > data/chain_2.in

# ========================================
# 陷阱数据 (4个测试点)
# ========================================
./generator trap 100 200 1000 500 7 > data/trap_1.in
./generator trap 1000 3000 100000 50000 8 > data/trap_2.in
./generator trap 10000 30000 500000 200000 9 > data/trap_3.in
./generator trap 50000 100000 1000000 1000000 10 > data/trap_4.in

# ========================================
# 随机数据 (6个测试点)
# ========================================
./generator random 5000 15000 100000 50000 11 > data/random_1.in
./generator random 10000 40000 500000 200000 12 > data/random_2.in
./generator random 30000 80000 1000000 500000 13 > data/random_3.in
./generator random 50000 120000 1000000 1000000 14 > data/random_4.in
./generator random 80000 180000 1000000 1000000 15 > data/random_5.in
./generator random 100000 200000 1000000 1000000 16 > data/random_6.in

# ========================================
# 大数据 (2个测试点)
# ========================================
./generator dense 1000 100000 1000000 1000000 17 > data/large_1.in
./generator random 100000 200000 1000000 1000000 18 > data/large_2.in

# ========================================
# 无解数据 (2个测试点)
# ========================================
./generator unreachable 1000 5000 100000 50000 19 > data/unreachable_1.in
./generator unreachable 100000 200000 1000000 1000000 20 > data/unreachable_2.in

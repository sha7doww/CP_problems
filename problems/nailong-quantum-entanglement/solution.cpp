/**
 * 题目: 奶龙的量子纠缠构造 (修正版)
 * 修正点: 修复了贪心策略中对剩余容量的估算错误。
 * 之前的估算假设剩余空间必须二分，实际上如果剩余空间 <= Limit，可以作为一个整体。
 */
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// 计算组合数 C(n, 2)
long long nCr2(long long n) {
    if (n < 2) return 0;
    return n * (n - 1) / 2;
}

// 修正后的最大容量计算函数
// 计算在给定 slots 个空位，且任意单一堆大小不能超过 limit 的情况下，
// 能凑出的最大对数（最大 K）。
// 策略：尽可能多地使用大小为 limit 的堆。
long long max_k_with_limit(int slots, int limit) {
    if (slots <= 0) return 0;
    // 如果剩余空间本身就小于等于 limit，直接作为一个大堆最划算
    if (slots <= limit) {
        return nCr2(slots);
    }
    // 否则，贪心地填满 limit 大小的堆
    long long num_full = slots / limit;
    long long remainder = slots % limit;
    return num_full * nCr2(limit) + nCr2(remainder);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    long long K;
    if (!(cin >> N >> K)) return 0;

    int total_slots = N + 1;
    // 关键约束：任意数值出现的次数不能超过总长度的一半（向上取整）
    // 只有这样才能保证相邻元素不重复
    int limit = (total_slots + 1) / 2;

    // 初始可行性检查
    if (K > max_k_with_limit(total_slots, limit)) {
        cout << "-1" << endl;
        return 0;
    }

    vector<int> counts;
    int current_slots = total_slots;
    long long current_k = K;

    while (current_slots > 0) {
        // 如果 K 已经凑够了，剩下的空位全部填 1（贡献为 0）
        if (current_k == 0) {
            while (current_slots > 0) {
                counts.push_back(1);
                current_slots--;
            }
            break;
        }

        bool found = false;
        // 贪心：尝试找最大的合法 v
        int start_v = min(current_slots, limit);
        
        for (int v = start_v; v >= 1; --v) {
            long long pairs = nCr2(v);
            
            // 条件1: 当前堆产生的对数不能超过剩余所需的 K
            if (pairs <= current_k) {
                // 条件2: 选了 v 之后，剩余的空位是否有能力凑出剩下的 K？
                long long rem_k = current_k - pairs;
                int rem_slots = current_slots - v;
                
                if (rem_k <= max_k_with_limit(rem_slots, limit)) {
                    counts.push_back(v);
                    current_slots -= v;
                    current_k -= pairs;
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            cout << "-1" << endl;
            return 0;
        }
    }

    // --- 构造 P 数组 ---
    // 为了满足相邻不相等，我们将出现次数最多的数填在偶数位，其余填奇数位
    vector<int> P(total_slots);
    
    // (次数, 数值ID)
    vector<pair<int, int>> val_counts;
    for (int i = 0; i < counts.size(); ++i) {
        val_counts.push_back({counts[i], i + 1});
    }
    // 降序排列，确保大堆先填
    sort(val_counts.rbegin(), val_counts.rend());

    int p_idx = 0;
    for (auto p : val_counts) {
        int count = p.first;
        int val = p.second;
        for (int k = 0; k < count; ++k) {
            if (p_idx >= total_slots) {
                p_idx = 1; // 偶数位填满，转奇数位
            }
            P[p_idx] = val;
            p_idx += 2;
        }
    }

    // --- 构造 A 数组 ---
    // A[i] = P[i] ^ P[i-1]
    for (int i = 1; i <= N; ++i) {
        cout << (P[i] ^ P[i - 1]) << (i == N ? "" : " ");
    }
    cout << endl;

    return 0;
}
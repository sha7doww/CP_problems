#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> L;

// 检查是否能切出至少 k 根长度为 len 的木棒
bool check(int len) {
    long long count = 0;
    for (int i = 0; i < n; i++) {
        count += L[i] / len;
        if (count >= k) return true; // 提前退出优化
    }
    return count >= k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    L.resize(n);

    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        cin >> L[i];
        maxLen = max(maxLen, L[i]);
    }

    // 二分答案
    int left = 1, right = maxLen;
    int ans = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            ans = mid;
            left = mid + 1;  // 尝试更大的长度
        } else {
            right = mid - 1; // 尝试更小的长度
        }
    }

    cout << ans << endl;

    return 0;
}

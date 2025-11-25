#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, d, e;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d >> e;

    // m = p + q = n - d*e + 2
    int m = n - d * e + 2;

    // 判别式 delta = m^2 - 4n
    int delta = m * m - 4 * n;

    // delta 必须非负
    if (delta < 0) {
        cout << "NO\n";
        return 0;
    }

    // 计算 sqrt(delta)，需要判断是否为完全平方数
    int sqrtDelta = (int)sqrtl(delta);

    // 检查是否为完全平方数（考虑精度问题，检查 sqrtDelta-1, sqrtDelta, sqrtDelta+1）
    bool isPerfectSquare = false;
    for (int candidate = max(0LL, sqrtDelta - 1); candidate <= sqrtDelta + 1; candidate++) {
        if (candidate * candidate == delta) {
            sqrtDelta = candidate;
            isPerfectSquare = true;
            break;
        }
    }

    if (!isPerfectSquare) {
        cout << "NO\n";
        return 0;
    }

    // 检查 (m + sqrtDelta) 和 (m - sqrtDelta) 是否都能被 2 整除
    if ((m + sqrtDelta) % 2 != 0 || (m - sqrtDelta) % 2 != 0) {
        cout << "NO\n";
        return 0;
    }

    // 检查是否满足 m > sqrtDelta（保证 p > 0）
    if (m <= sqrtDelta) {
        cout << "NO\n";
        return 0;
    }

    // 计算 p 和 q
    int p = (m - sqrtDelta) / 2;
    int q = (m + sqrtDelta) / 2;

    // 输出结果（保证 p <= q）
    cout << p << " " << q << "\n";

    return 0;
}

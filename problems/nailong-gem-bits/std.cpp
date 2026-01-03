#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x, l, r;
        cin >> x >> l >> r;

        int count = 0;
        // 统计第 l 位到第 r 位中 1 的数量
        for (int j = l; j <= r; j++) {
            if ((x >> j) & 1) {
                count++;
            }
        }

        cout << count << "\n";
    }

    return 0;
}

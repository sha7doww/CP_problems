#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n + 1);
    vector<int> f(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        for (int j = 1; j < i; j++) {
            if (a[i] > a[j]) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = max(res, f[i]);
    }

    cout << res << endl;

    return 0;
}

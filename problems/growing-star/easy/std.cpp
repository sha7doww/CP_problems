#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int maxLen = 1;
    int curLen = 1;

    for (int i = 1; i < n; i++) {
        if (a[i] > a[i - 1]) {
            curLen++;
            maxLen = max(maxLen, curLen);
        } else {
            curLen = 1;
        }
    }

    cout << maxLen << endl;

    return 0;
}

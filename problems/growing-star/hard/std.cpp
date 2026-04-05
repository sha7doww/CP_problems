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

    vector<int> ends;

    for (int i = 0; i < n; i++) {
        auto it = lower_bound(ends.begin(), ends.end(), a[i]);
        if (it == ends.end()) {
            ends.push_back(a[i]);
        } else {
            *it = a[i];
        }
    }

    cout << ends.size() << endl;

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long long LIMIT = 1000000000LL; // 10^9
    long long product = 1;

    for (int i = 0; i < 10; i++) {
        long long x;
        cin >> x;
        product *= x;

        // Early termination if product exceeds limit
        if (product > LIMIT) {
            cout << -1 << endl;
            return 0;
        }
    }

    cout << product << endl;

    return 0;
}
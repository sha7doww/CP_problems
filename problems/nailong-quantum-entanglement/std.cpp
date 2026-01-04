#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long K;
    cin >> N >> K;

    int M = N + 1;                 // number of prefix xors
    int L = (M + 1) / 2;           // ceil(M/2)

    // Calculate maximum possible K given the constraint that adjacent prefix
    // values must be different (since A[i] != 0)
    auto maxK = [&](int M) -> long long {
        if (M % 2 == 0) {
            long long m = M / 2;
            return m * (m - 1);
        } else {
            long long m = (M - 1) / 2;
            return m * m;
        }
    };

    long long Kmax = maxK(M);
    if (K > Kmax) {
        cout << -1 << "\n";
        return 0;
    }

    // Complete knapsack: dp[k] = minimal length to achieve k pairs using group
    // sizes 2..L
    const int INF = 1e9;
    int Kint = (int)K;
    vector<int> dp(Kint + 1, INF), preK(Kint + 1, -1), preS(Kint + 1, -1);
    dp[0] = 0;

    for (int s = 2; s <= L; s++) {
        int w = s * (s - 1) / 2;
        for (int k = w; k <= Kint; k++) {
            if (dp[k - w] != INF && dp[k - w] + s < dp[k]) {
                dp[k] = dp[k - w] + s;
                preK[k] = k - w;
                preS[k] = s;
            }
        }
    }

    if (dp[Kint] > M) {
        cout << -1 << "\n";
        return 0;
    }

    // Reconstruct group sizes (counts of each distinct prefix value)
    vector<int> groups;
    int cur = Kint;
    while (cur > 0) {
        int s = preS[cur];
        if (s == -1) { // should not happen
            cout << -1 << "\n";
            return 0;
        }
        groups.push_back(s);
        cur = preK[cur];
    }
    int used = 0;
    for (int x : groups) used += x;
    groups.insert(groups.end(), M - used, 1); // fill with 1s (no extra pairs)

    // Make the largest group be the "0" value so we can start with P0=0 safely.
    int idxMax = 0;
    for (int i = 1; i < (int)groups.size(); i++) {
        if (groups[i] > groups[idxMax]) idxMax = i;
    }
    swap(groups[0], groups[idxMax]);

    int G = (int)groups.size();

    // Map group id -> concrete prefix xor value
    const int BASE = 1 << 28; // < 2^29, safe
    vector<int> val(G);
    val[0] = 0;
    for (int i = 1; i < G; i++) val[i] = BASE + i;

    // Build prefix-id sequence of length M with no adjacent equal, starting with
    // id 0.
    vector<int> cnt = groups;
    priority_queue<pair<int, int>> pq; // (remaining, id)
    cnt[0]--;                          // place first
    for (int i = 0; i < G; i++) {
        if (cnt[i] > 0) pq.push({cnt[i], i});
    }

    vector<int> pid;
    pid.reserve(M);
    pid.push_back(0);
    int prev = 0;

    for (int pos = 1; pos < M; pos++) {
        if (pq.empty()) {
            cout << -1 << "\n";
            return 0;
        }

        auto [c1, i1] = pq.top();
        pq.pop();
        if (i1 == prev) {
            if (pq.empty()) {
                cout << -1 << "\n";
                return 0;
            }
            auto [c2, i2] = pq.top();
            pq.pop();

            // use i2
            pid.push_back(i2);
            prev = i2;
            c2--;
            if (c2 > 0) pq.push({c2, i2});

            // put back i1
            pq.push({c1, i1});
        } else {
            pid.push_back(i1);
            prev = i1;
            c1--;
            if (c1 > 0) pq.push({c1, i1});
        }
    }

    // Convert to prefix values
    vector<int> P(M);
    for (int i = 0; i < M; i++) P[i] = val[pid[i]];

    // Output A[i] = P[i-1] xor P[i]
    for (int i = 1; i < M; i++) {
        int a = P[i - 1] ^ P[i];
        // a is guaranteed nonzero and < 2^29 < 1e9
        if (i > 1) cout << ' ';
        cout << a;
    }
    cout << "\n";
    return 0;
}

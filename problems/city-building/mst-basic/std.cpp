#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;

struct edge {
    int u, v, w;
    bool operator<(const edge &a) const {
        return w < a.w;
    }
} E[maxn];

int pa[maxn];

int find(int x) {
    return pa[x] == x ? x : pa[x] = find(pa[x]);
}

void unite(int x, int y) {
    pa[find(x)] = find(y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) pa[i] = i;

    for (int i = 1; i <= m; i++) {
        cin >> E[i].u >> E[i].v >> E[i].w;
    }

    sort(E + 1, E + m + 1);

    long long ans = 0;
    int cnt = 0;

    for (int i = 1; i <= m; i++) {
        int u = E[i].u, v = E[i].v, w = E[i].w;
        if (find(u) != find(v)) {
            unite(u, v);
            ans += w;
            cnt++;
        }
        if (cnt == n - 1) break;
    }

    cout << ans << endl;

    return 0;
}

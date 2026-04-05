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
    int flag = 0;

    for (int i = 1; i <= m; i++) {
        int u = E[i].u, v = E[i].v, w = E[i].w;
        int j = i;

        // Find all edges with same weight
        while (j <= m && E[j].w == w) j++;

        int cnt1 = 0, cnt2 = 0;

        // Count edges that can potentially be added
        for (int k = i; k < j; k++) {
            if (find(E[k].u) != find(E[k].v)) {
                cnt1++;
            }
        }

        // Actually add edges
        for (int k = i; k < j; k++) {
            if (find(E[k].u) != find(E[k].v)) {
                unite(E[k].u, E[k].v);
                ans += E[k].w;
                cnt2++;
                cnt++;
            }
        }

        // If more edges could be added than were added, MST is not unique
        if (cnt1 > cnt2) {
            flag = 1;
        }

        i = j - 1;
    }

    cout << ans << endl;
    if (flag)
        cout << "not unique" << endl;
    else
        cout << "unique" << endl;

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 3e5 + 10;
const int LOG = 20;
const ll INF = 0x3f3f3f3f3f3f3f3fLL;

struct edge {
    int u, v;
    ll w;
    bool operator<(const edge &a) const {
        return w < a.w;
    }
} E[maxn];

struct tree {
    int v;
    ll w;
};

int n, m;
vector<tree> T[maxn];
int pa[maxn];

int find(int x) {
    return pa[x] == x ? x : pa[x] = find(pa[x]);
}

void unite(int x, int y) {
    pa[find(x)] = find(y);
}

int dep[maxn], f[maxn][LOG + 1], vis[maxn];
ll vx[maxn][LOG + 1], vx1[maxn][LOG + 1];  // max and second max on path

void dfs_lca(int now, int fa, ll val) {
    dep[now] = dep[fa] + 1;
    f[now][0] = fa;
    vx[now][0] = val;
    vx1[now][0] = -INF;  // Use -INF to indicate no second max

    for (int i = 1; i <= LOG; i++) {
        f[now][i] = f[f[now][i-1]][i-1];
        // Merge max and second max from two segments
        ll vals[4] = {vx[now][i-1], vx1[now][i-1], vx[f[now][i-1]][i-1], vx1[f[now][i-1]][i-1]};
        sort(vals, vals + 4, greater<ll>());
        vx[now][i] = vals[0];
        // Second max must be strictly less than max
        vx1[now][i] = -INF;
        for (int j = 1; j < 4; j++) {
            if (vals[j] < vals[0]) {
                vx1[now][i] = vals[j];
                break;
            }
        }
    }

    for (auto &e : T[now]) {
        if (e.v != fa) {
            dfs_lca(e.v, now, e.w);
        }
    }
}

// Find max edge on path from x to y that is strictly less than z
// If all edges >= z or path is empty, return -INF
pair<ll, ll> query_path(int x, int y) {
    // Returns (max, second_max) on path from x to y
    if (dep[x] < dep[y]) swap(x, y);

    vector<ll> vals;
    int d = dep[x] - dep[y];

    for (int i = 0; i <= LOG; i++) {
        if ((1 << i) & d) {
            vals.push_back(vx[x][i]);
            vals.push_back(vx1[x][i]);
            x = f[x][i];
        }
    }

    if (x != y) {
        for (int i = LOG; i >= 0; i--) {
            if (f[x][i] != f[y][i]) {
                vals.push_back(vx[x][i]);
                vals.push_back(vx1[x][i]);
                vals.push_back(vx[y][i]);
                vals.push_back(vx1[y][i]);
                x = f[x][i];
                y = f[y][i];
            }
        }
        vals.push_back(vx[x][0]);
        vals.push_back(vx1[x][0]);
        vals.push_back(vx[y][0]);
        vals.push_back(vx1[y][0]);
    }

    sort(vals.begin(), vals.end(), greater<ll>());
    ll mx1 = -INF, mx2 = -INF;
    for (ll v : vals) {
        if (v <= -INF) continue;
        if (mx1 == -INF) {
            mx1 = v;
        } else if (v < mx1 && mx2 == -INF) {
            mx2 = v;
            break;
        }
    }
    return {mx1, mx2};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) pa[i] = i;

    for (int i = 1; i <= m; i++) {
        cin >> E[i].u >> E[i].v >> E[i].w;
        if (E[i].u == E[i].v) {
            i--;
            m--;
        }
    }

    sort(E + 1, E + m + 1);

    ll mst_cost = 0;
    int cnt = 0;

    for (int i = 1; i <= m; i++) {
        int u = E[i].u, v = E[i].v;
        ll w = E[i].w;
        if (find(u) != find(v)) {
            unite(u, v);
            mst_cost += w;
            cnt++;
            vis[i] = 1;
            T[u].push_back({v, w});
            T[v].push_back({u, w});
        }
        if (cnt == n - 1) break;
    }

    // Build LCA structure
    for (int i = 1; i <= n; i++) {
        if (!dep[i]) dfs_lca(i, 0, 0);
    }

    ll ans = INF;

    // Try adding each non-MST edge
    for (int i = 1; i <= m; i++) {
        if (!vis[i]) {
            auto [mx1, mx2] = query_path(E[i].u, E[i].v);
            // For strict second-best MST, we need E[i].w - max_edge > 0
            // If E[i].w == mx1, we must use mx2 (the second max)
            ll max_edge;
            if (E[i].w > mx1) {
                max_edge = mx1;
            } else if (E[i].w == mx1 && mx2 > -INF) {
                max_edge = mx2;
            } else {
                continue;  // Cannot form strict second-best MST with this edge
            }

            if (max_edge > -INF) {
                ll diff = E[i].w - max_edge;
                if (diff > 0) {
                    ans = min(ans, diff);
                }
            }
        }
    }

    if (ans == INF) {
        cout << -1 << endl;
    } else {
        cout << mst_cost + ans << endl;
    }

    return 0;
}

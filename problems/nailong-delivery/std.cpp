#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // 邻接表：adj[u] = {(v, bridge_color, base_time, k), ...}
    vector<vector<tuple<int, int, int, int>>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, c, t, k;
        cin >> u >> v >> c >> t >> k;
        adj[u].push_back({v, c, t, k});
    }

    // 分层图最短路：dist[node][color] 表示到达 node 且当前颜色为 color 的最短时间
    // color: 0=红, 1=绿, 2=蓝
    vector<vector<long long>> dist(n + 1, vector<long long>(3, INF));

    // 优先队列：(距离, 节点, 颜色)
    priority_queue<tuple<long long, int, int>,
                   vector<tuple<long long, int, int>>,
                   greater<tuple<long long, int, int>>> pq;

    // 初始状态：站点1，颜色0（红色），时间0
    dist[1][0] = 0;
    pq.push({0, 1, 0});

    while (!pq.empty()) {
        auto [d, u, curr_color] = pq.top();
        pq.pop();

        // 剪枝：如果当前状态已经被更优的路径更新过，跳过
        if (d > dist[u][curr_color]) continue;

        // 遍历所有出边
        for (auto& [v, bridge_color, base_time, k] : adj[u]) {
            // 规则1：同色禁止通行
            if (curr_color == bridge_color) continue;

            // 规则2：计算变色后的新颜色
            // 0+1+2=3，所以新颜色 = 3 - 当前颜色 - 桥颜色
            int next_color = 3 - curr_color - bridge_color;

            // 规则3：计算通行时间（使用变色后的颜色）
            long long cost = base_time + (long long)k * next_color;

            // 更新最短距离
            if (dist[v][next_color] > d + cost) {
                dist[v][next_color] = d + cost;
                pq.push({dist[v][next_color], v, next_color});
            }
        }
    }

    // 答案：到达站点n的最短时间（任意颜色状态都可以）
    long long ans = min({dist[n][0], dist[n][1], dist[n][2]});

    if (ans == INF) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}

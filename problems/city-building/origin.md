# 城镇修建

> 原题来源：最小生成树系列问题

---

## 难度一：基础最小生成树

### 题目描述

Z 市是一个荒芜未经开发的新区划，里面的 $n$ 个城镇间，村民们只能通过原本的 $m$ 条狭窄的小路进行通行，十分的不方便。Z 市政府决定，花钱请施工队，对其中的 $n-1$ 条路进行重新修建，将小路修建成为大路，以确保每个城镇之间通行方便。

但是 Z 市政府希望能尽可能省钱的方式完成施工，于是找到了你，请你为他们选择一条合适的修建方案，告诉他们修建的开销。

### 输入格式

输入的第一行有两个整数 $n$ 和 $m$，表示有 $n$ 个城镇，$m$ 条初始的狭窄小路。

紧接着的 $m$ 行，每行 3 个整数 $u$，$v$，$w$，表示城镇 $u$ 和 $v$ 间存在一条小路，将其修建成大路的开销是 $w$。

**数据范围：**
对于 $100\%$ 的数据，保证 $1 \le n \le 10^5$，$n-1 \le m \le 10^5$，$1 \le u, v \le n$，$1 \le w \le 10^9$。保证图连通，可能存在重边，不存在自环。

### 输出格式

输出一行，这一行只包含一个整数，表示本次修建的开销。

### 参考做法

#### Prim 算法

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
struct edge{
    int v, w;
    bool operator<(const edge &a)const{
        return w > a.w;
    }
};
vector<edge> E[maxn];
int vis[maxn], dis[maxn];

int main(){
    int n, m;
    cin >> n >> m;
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3f, sizeof(dis));
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        E[u].push_back({v, w});
        E[v].push_back({u, w});
    }
    int ans = 0;
    priority_queue<edge, vector<edge>> q;
    q.push({1, 0});
    dis[1] = 0;
    int cnt = 0;
    while(!q.empty()){
        if (cnt >= n) break;
        int u = q.top().v;
        int d = q.top().w;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        ++cnt;
        ans += d;
        for(auto e : E[u]){
            int v = e.v;
            int w = e.w;
            if (vis[v]) continue;
            if (w < dis[v]){
                dis[v] = w;
                q.push({v, dis[v]});
            }
        }
    }
    cout << ans;
}
```

#### Kruskal 算法

前提：并查集

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
struct edge{
    int u, v, w;
    bool operator<(const edge &a)const{
        return w < a.w;
    }
} E[maxn];
int pa[maxn];

int find(int x){
    return pa[x] == x ? x : pa[x] = find(pa[x]);
}

void unite(int x, int y) {
    pa[find(x)] = find(y);
}

int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) pa[i] = i;
    for(int i = 1; i <= m; i++){
        cin >> E[i].u >> E[i].v >> E[i].w;
    }
    sort(E + 1, E + m + 1);
    int ans = 0;
    int cnt = 0;
    for(int i = 1; i <= m; i++){
        int u = E[i].u, v = E[i].v, w = E[i].w;
        if(find(u) != find(v)){
            unite(u, v);
            ans += w;
            cnt++;
        }
    }
    cout << ans;
}
```

---

## 难度二：最小生成树是否唯一

### 题目描述

Z 市是一个荒芜未经开发的新区划，里面的 $n$ 个城镇间，村民们只能通过原本的 $m$ 条狭窄的小路进行通行，十分的不方便。Z 市政府决定，花钱请施工队，对其中的 $n-1$ 条路进行重新修建，将小路修建成为大路，以确保每个城镇之间通行方便。

Z 市政府对你设计的最省钱方案的开销很满意，但是对你设计的修建路线不是很满意，想要知道是否存在其他的方案使得仍然可以通过同样的开销完成修建。

### 输入格式

输入的第一行有两个整数 $n$ 和 $m$，表示有 $n$ 个城镇，$m$ 条初始的狭窄小路。

紧接着的 $m$ 行，每行 3 个整数 $u$，$v$，$w$，表示城镇 $u$ 和 $v$ 间存在一条小路，将其修建成大路的开销是 $w$。

**数据范围：**
对于 $100\%$ 的数据，保证 $1 \le n \le 10^5$，$n-1 \le m \le 10^5$，$1 \le u, v \le n$，$1 \le w \le 10^9$。保证图连通，可能存在重边，不存在自环。

### 输出格式

输出两行：
- 第一行只包含一个整数，表示本次修建的最小开销。
- 第二行输出最小生成树是否唯一，如果唯一，输出 `unique`，否则输出 `not unique`。

### 参考做法

- **法一**：暴力，每次删一个有效边接着跑最小生成树，然后比 ans
- **法二**：Kruskal 打个 tag，Prim 同一时刻看值相同的有没有

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
struct edge{
    int u, v, w;
    bool operator<(const edge &a)const{
        return w < a.w;
    }
} E[maxn];
int pa[maxn];

int find(int x){
    return pa[x] == x ? x : pa[x] = find(pa[x]);
}

void unite(int x, int y) {
    pa[find(x)] = find(y);
}

int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) pa[i] = i;
    for(int i = 1; i <= m; i++){
        cin >> E[i].u >> E[i].v >> E[i].w;
    }
    sort(E + 1, E + m + 1);
    int ans = 0;
    int cnt = 0;
    int flag = 0;
    for(int i = 1; i <= m; i++){
        int u = E[i].u, v = E[i].v, w = E[i].w;
        int j = i;
        while(j <= m && E[j].w == w)
            j++;
        int cnt1, cnt2;
        cnt1 = cnt2 = 0;
        for(int k = i; k < j; k++){
            if(find(E[k].u) != find(E[k].v)){
                cnt1++;
            }
        }
        for(int k = i; k < j; k++){
            if(find(E[k].u) != find(E[k].v)){
                unite(E[k].u, E[k].v);
                ans += E[k].w;
                cnt2++;
                cnt++;
            }
        }
        if(cnt1 > cnt2){
            flag = 1;
        }
    }
    cout << ans << endl;
    if(flag)
        cout << "not unique";
    else
        cout << "unique";
}
```

---

## 难度三：次小生成树（严格）

### 题目描述

Z 市是一个荒芜未经开发的新区划，里面的 $n$ 个城镇间，村民们只能通过原本的 $m$ 条狭窄的小路进行通行，十分的不方便。Z 市政府决定，花钱请施工队，对其中的 $n-1$ 条路进行重新修建，将小路修建成为大路，以确保每个城镇之间通行方便。

因为得知 Z 市政府选择的是最便宜的方案，引起了居民们的热议。为了稳住居民们的内心，Z 市政府决定不能再用任何开销等于最便宜开销的方案，但是同样也不希望花太多的钱。因此，你需要为他设计出仅次于最便宜开销的方案（严格大于最小开销），并输出此时的开销。

### 输入格式

输入的第一行有两个整数 $n$ 和 $m$，表示有 $n$ 个城镇，$m$ 条初始的狭窄小路。

紧接着的 $m$ 行，每行 3 个整数 $u$，$v$，$w$，表示城镇 $u$ 和 $v$ 间存在一条小路，将其修建成大路的开销是 $w$。

**数据范围：**
对于 $100\%$ 的数据，保证 $1 \le n \le 10^5$，$n-1 \le m \le 3 \times 10^5$，$1 \le u, v \le n$，$1 \le w \le 10^9$。保证图连通，可能存在重边，不存在自环。

### 输出格式

输出一行，只包含一个整数。如果存在严格次小生成树，输出其开销；否则输出 $-1$。

### 参考做法

- **法一**：暴力，每次删一个有效边接着跑最小生成树，然后比 ans
- **法二**：Kruskal + LCA 倍增（或者树剖）：遍历所有的无效边 $(u, v, w)$，加入 MST 后会多出一个环，找生成树上环路径最大的边 $w'$，减去，更新 ans（但是为了确保是严格次小的，所以加入的边的值和最大的 $w'$ 的值不能一样，LCA 需要维护最大和次大的边）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 10;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
#define int long long
#define fast ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)

struct edge{
    int u, v, w;
    bool operator<(const edge &a)const{
        return w < a.w;
    }
} E[maxn];

struct tree{
    int v, w;
};

int n, m;
vector<tree> T[maxn];
int pa[maxn];

int find(int x){
    return pa[x] == x ? x : pa[x] = find(pa[x]);
}

void unite(int x, int y) {
    pa[find(x)] = find(y);
}

int dep[maxn], f[maxn][21], sz[maxn], vx[maxn][21], vx1[maxn][21];
int vis[maxn];

void dfs_lca(int now, int fa, int val){
    dep[now] = dep[fa] + 1;
    f[now][0] = fa;
    vx[now][0] = val;
    vx1[now][0] = 0;
    for (int i = 1; (1 << i) <= dep[now]; i++){
        f[now][i] = f[f[now][i-1]][i-1];
        vx[now][i] = max(vx[f[now][i - 1]][i - 1], vx[now][i - 1]);
        if(vx[now][i-1] == vx[f[now][i-1]][i-1]){
            vx1[now][i] = max(max(vx1[f[now][i - 1]][i - 1], vx1[now][i - 1]), 0ll);
        } else {
            vx1[now][i] = max(max(vx1[f[now][i - 1]][i - 1], vx1[now][i - 1]),
                min(vx[now][i - 1], vx[f[now][i - 1]][i - 1]));
        }
    }
    for(auto i : T[now]){
        if(i.v != fa){
            dfs_lca(i.v, now, i.w);
        }
    }
}

int lca(int x, int y, int z){
    if(dep[x] < dep[y]) swap(x, y);
    int ans = 0, d = dep[x] - dep[y];
    for (int i = 0; (1 << i) <= d; i++){
        if(1 << i & d){
            ans = max(ans, (vx[x][i] == z ? vx1[x][i] : vx[x][i]));
            x = f[x][i];
        }
    }
    if(x == y) return ans;
    for(int i = log2(dep[x]); i >= 0; i--){
        if(f[x][i] != f[y][i]){
            ans = max(max(vx[x][i], vx[y][i]) == z ? vx1[x][i] : max(vx[x][i], vx[y][i]), ans);
            x = f[x][i];
            y = f[y][i];
        }
    }
    return (max(max(vx[x][0], vx[y][0]) == z ? max(max(vx1[x][0], vx1[y][0]), ans) : max(vx[x][0], vx[y][0]), ans));
}

int ans = INF;

signed main(){
    fast;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) pa[i] = i;
    for(int i = 1; i <= m; i++){
        cin >> E[i].u >> E[i].v >> E[i].w;
        if(E[i].u == E[i].v){
            i--;
            m--;
        }
    }
    sort(E + 1, E + m + 1);
    int anss = 0;
    int cnt = 0;
    for(int i = 1; i <= m; i++){
        int u = E[i].u, v = E[i].v, w = E[i].w;
        if(find(u) != find(v)){
            unite(u, v);
            anss += w;
            cnt++;
            vis[i] = 1;
            T[u].push_back({v, w});
            T[v].push_back({u, w});
        }
        if(cnt == n - 1)
            break;
    }
    for (int i = 1; i <= n; i++)
        if (!dep[i]) dfs_lca(i, 0, 0);
    for(int i = 1; i <= m; i++){
        if(!vis[i]){
            int x = lca(E[i].u, E[i].v, E[i].w);
            if(E[i].w - x != 0){
                ans = min(ans, E[i].w - x);
            }
        }
    }
    if(ans == INF)
        cout << -1;
    else
        cout << anss + ans;
}
```

---

## 备注

本题包含三个难度等级：
1. **难度一**：基础最小生成树（Prim / Kruskal）
2. **难度二**：判断最小生成树是否唯一
3. **难度三**：严格次小生成树（Kruskal + LCA 倍增）

#include "testlib.h"
#include <iostream>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // 参数：./generator <mode> <n> <m> <maxT> <maxK> [seed]
    // mode: random, chain, trap, dense, sparse, unreachable

    string mode = argv[1];
    int n = atoi(argv[2]);
    int m = atoi(argv[3]);
    int maxT = atoi(argv[4]);
    int maxK = atoi(argv[5]);

    cout << n << " " << m << endl;

    set<pair<int, int>> used_edges;

    auto add_edge = [&](int u, int v) -> bool {
        if (u == v) return false;
        if (used_edges.count({u, v})) return false;
        used_edges.insert({u, v});
        int c = rnd.next(0, 2);
        int t = rnd.next(1, maxT);
        int k = rnd.next(0, maxK);
        cout << u << " " << v << " " << c << " " << t << " " << k << endl;
        return true;
    };

    if (mode == "chain") {
        // 链状图：1 -> 2 -> 3 -> ... -> n
        // 确保颜色交替以便可达
        for (int i = 1; i < n && (int)used_edges.size() < m; i++) {
            int c = i % 3;  // 颜色交替
            int t = rnd.next(1, maxT);
            int k = rnd.next(0, maxK);
            if (!used_edges.count({i, i + 1})) {
                used_edges.insert({i, i + 1});
                cout << i << " " << i + 1 << " " << c << " " << t << " " << k << endl;
            }
        }
        // 填充剩余边
        while ((int)used_edges.size() < m) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            add_edge(u, v);
        }
    } else if (mode == "trap") {
        // 陷阱图：贪心路径被阻断
        // 构造：1 -> 2 有两条边（短但死路 vs 长但可达）
        //       2 -> 3 有一条边
        //       3 -> n 只能特定颜色通过

        if (n >= 4 && m >= 4) {
            // 短路但死路：1->2 绿桥(1)，会变成蓝(2)
            cout << "1 2 1 " << rnd.next(1, maxT / 2) << " " << rnd.next(0, maxK) << endl;
            used_edges.insert({1, 2});

            // 长路但可达：1->2 蓝桥(2)，会变成绿(1)
            cout << "1 2 2 " << rnd.next(maxT / 2, maxT) << " " << rnd.next(0, maxK) << endl;

            // 2->3 红桥(0)
            cout << "2 3 0 " << rnd.next(1, maxT) << " " << rnd.next(0, maxK) << endl;
            used_edges.insert({2, 3});

            // 3->n 绿桥(1)，只有蓝色(2)奶龙能通过
            cout << "3 " << n << " 1 " << rnd.next(1, maxT) << " " << rnd.next(0, maxK) << endl;
            used_edges.insert({3, n});

            int edges_added = 4;

            // 填充剩余边
            while (edges_added < m) {
                int u = rnd.next(1, n);
                int v = rnd.next(1, n);
                if (add_edge(u, v)) edges_added++;
            }
        } else {
            // 回退到随机模式
            while ((int)used_edges.size() < m) {
                int u = rnd.next(1, n);
                int v = rnd.next(1, n);
                add_edge(u, v);
            }
        }
    } else if (mode == "dense") {
        // 稠密图：尽量多的边
        for (int i = 1; i <= n && (int)used_edges.size() < m; i++) {
            for (int j = 1; j <= n && (int)used_edges.size() < m; j++) {
                if (i != j) {
                    add_edge(i, j);
                }
            }
        }
    } else if (mode == "sparse") {
        // 稀疏图：确保连通性，然后少量随机边
        // 先建一条链
        for (int i = 1; i < n && (int)used_edges.size() < m; i++) {
            add_edge(i, i + 1);
        }
        // 再加少量随机边
        while ((int)used_edges.size() < m) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            add_edge(u, v);
        }
    } else if (mode == "unreachable") {
        // 无解图：让终点不可达
        // 只生成 1 到 n-1 之间的边
        while ((int)used_edges.size() < m) {
            int u = rnd.next(1, n - 1);
            int v = rnd.next(1, n - 1);
            add_edge(u, v);
        }
    } else {
        // random：完全随机
        while ((int)used_edges.size() < m) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            add_edge(u, v);
        }
    }

    return 0;
}

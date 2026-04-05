#include "testlib.h"
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Usage: ./generator <mode> <n> <m> <maxW>
    // mode: random, unique, notunique, sameweight
    string mode = argv[1];
    int n = atoi(argv[2]);
    int m = atoi(argv[3]);
    int maxW = atoi(argv[4]);

    cout << n << " " << m << endl;

    set<pair<int, int>> edges;
    vector<tuple<int, int, int>> edgeList;

    // First ensure connectivity with a spanning tree
    vector<int> perm(n);
    for (int i = 0; i < n; i++) perm[i] = i + 1;
    shuffle(perm.begin(), perm.end());

    if (mode == "sameweight") {
        // All edges have same weight - likely not unique
        for (int i = 1; i < n; i++) {
            int u = perm[i];
            int v = perm[rnd.next(0, i - 1)];
            edgeList.push_back({u, v, 1});
            edges.insert({min(u, v), max(u, v)});
        }
        int extra = m - (n - 1);
        int attempts = 0;
        while (extra > 0 && attempts < 1000000) {
            attempts++;
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u == v) continue;
            if (u > v) swap(u, v);
            if (edges.count({u, v})) continue;
            edgeList.push_back({u, v, 1});
            edges.insert({u, v});
            extra--;
        }
    } else if (mode == "notunique") {
        // Generate edges with many duplicate weights to increase chance of non-unique MST
        for (int i = 1; i < n; i++) {
            int u = perm[i];
            int v = perm[rnd.next(0, i - 1)];
            int w = rnd.next(1, maxW / 10 + 1) * 10;  // Round weights
            edgeList.push_back({u, v, w});
            edges.insert({min(u, v), max(u, v)});
        }
        int extra = m - (n - 1);
        int attempts = 0;
        while (extra > 0 && attempts < 1000000) {
            attempts++;
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u == v) continue;
            if (u > v) swap(u, v);
            if (edges.count({u, v})) continue;
            int w = rnd.next(1, maxW / 10 + 1) * 10;
            edgeList.push_back({u, v, w});
            edges.insert({u, v});
            extra--;
        }
    } else {
        // Random or unique mode
        for (int i = 1; i < n; i++) {
            int u = perm[i];
            int v = perm[rnd.next(0, i - 1)];
            int w = rnd.next(1, maxW);
            edgeList.push_back({u, v, w});
            edges.insert({min(u, v), max(u, v)});
        }
        int extra = m - (n - 1);
        int attempts = 0;
        while (extra > 0 && attempts < 1000000) {
            attempts++;
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u == v) continue;
            if (u > v) swap(u, v);
            if (edges.count({u, v})) continue;
            int w = rnd.next(1, maxW);
            edgeList.push_back({u, v, w});
            edges.insert({u, v});
            extra--;
        }
    }

    // Shuffle and output edges
    shuffle(edgeList.begin(), edgeList.end());
    for (auto& e : edgeList) {
        cout << get<0>(e) << " " << get<1>(e) << " " << get<2>(e) << endl;
    }

    return 0;
}

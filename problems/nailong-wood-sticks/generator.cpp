#include "testlib.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // 参数：./generator <mode> <n> <k> <maxL> [seed]
    // mode: random, small, large, edge

    string mode = argv[1];
    int n = atoi(argv[2]);
    int k = atoi(argv[3]);
    int maxL = atoi(argv[4]);

    cout << n << " " << k << endl;

    if (mode == "small") {
        // 小数据，长度较小
        for (int i = 0; i < n; i++) {
            cout << rnd.next(1, min(100, maxL));
            if (i < n - 1) cout << " ";
        }
        cout << endl;
    } else if (mode == "large") {
        // 大数据，长度较大
        for (int i = 0; i < n; i++) {
            cout << rnd.next(max(1, maxL / 2), maxL);
            if (i < n - 1) cout << " ";
        }
        cout << endl;
    } else if (mode == "edge") {
        // 边界数据，所有木棒长度相同
        int len = rnd.next(1, maxL);
        for (int i = 0; i < n; i++) {
            cout << len;
            if (i < n - 1) cout << " ";
        }
        cout << endl;
    } else if (mode == "uniform") {
        // 均匀分布
        for (int i = 0; i < n; i++) {
            cout << rnd.next(1, maxL);
            if (i < n - 1) cout << " ";
        }
        cout << endl;
    } else { // random
        // 随机数据
        for (int i = 0; i < n; i++) {
            cout << rnd.next(1, maxL);
            if (i < n - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}

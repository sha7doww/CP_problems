#include "testlib.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // 参数: ./generator <mode> <n>
    string mode = argv[1];
    int n = atoi(argv[2]);

    cout << n << endl;

    if (mode == "small") {
        // 小数据：x 较小，范围较小
        for (int i = 0; i < n; i++) {
            int x = rnd.next(0, 100);
            int l = rnd.next(0, 6);
            int r = rnd.next(l, 6);
            cout << x << " " << l << " " << r << endl;
        }
    } else if (mode == "random") {
        // 随机数据
        for (int i = 0; i < n; i++) {
            int x = rnd.next(0, 1000000000);
            int l = rnd.next(0, 29);
            int r = rnd.next(l, 29);
            cout << x << " " << l << " " << r << endl;
        }
    } else if (mode == "large") {
        // 大数据：x 接近最大值
        for (int i = 0; i < n; i++) {
            int x = rnd.next(900000000, 1000000000);
            int l = rnd.next(0, 29);
            int r = rnd.next(l, 29);
            cout << x << " " << l << " " << r << endl;
        }
    } else if (mode == "edge_zero") {
        // 边界：全是 0
        for (int i = 0; i < n; i++) {
            int l = rnd.next(0, 29);
            int r = rnd.next(l, 29);
            cout << "0 " << l << " " << r << endl;
        }
    } else if (mode == "edge_max") {
        // 边界：最大值
        for (int i = 0; i < n; i++) {
            int l = rnd.next(0, 29);
            int r = rnd.next(l, 29);
            cout << "1000000000 " << l << " " << r << endl;
        }
    } else if (mode == "edge_range") {
        // 边界：范围测试
        for (int i = 0; i < n; i++) {
            int x = rnd.next(0, 1000000000);
            if (i % 3 == 0) {
                // 单个位
                int pos = rnd.next(0, 29);
                cout << x << " " << pos << " " << pos << endl;
            } else if (i % 3 == 1) {
                // 从 0 开始
                int r = rnd.next(0, 29);
                cout << x << " 0 " << r << endl;
            } else {
                // 到 29 结束
                int l = rnd.next(0, 29);
                cout << x << " " << l << " 29" << endl;
            }
        }
    } else if (mode == "power_of_two") {
        // 特殊：2 的幂次
        for (int i = 0; i < n; i++) {
            int power = rnd.next(0, 29);
            int x = (1 << power);
            int l = rnd.next(0, 29);
            int r = rnd.next(l, 29);
            cout << x << " " << l << " " << r << endl;
        }
    } else if (mode == "all_ones") {
        // 特殊：二进制全是 1 的数
        for (int i = 0; i < n; i++) {
            int bits = rnd.next(1, 29);
            int x = (1 << bits) - 1;
            int l = rnd.next(0, 29);
            int r = rnd.next(l, 29);
            cout << x << " " << l << " " << r << endl;
        }
    }

    return 0;
}

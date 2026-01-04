#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 读取第一行：n 和 m
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    // 读取 m 条边
    for (int i = 0; i < m; i++) {
        // u: 起点
        inf.readInt(1, n, format("u[%d]", i + 1));
        inf.readSpace();

        // v: 终点
        inf.readInt(1, n, format("v[%d]", i + 1));
        inf.readSpace();

        // c: 颜色 (0, 1, 2)
        inf.readInt(0, 2, format("c[%d]", i + 1));
        inf.readSpace();

        // t: 基础时间
        inf.readInt(1, 1000000, format("t[%d]", i + 1));
        inf.readSpace();

        // k: 倍率因子
        inf.readInt(0, 1000000, format("k[%d]", i + 1));
        inf.readEoln();
    }

    // 确保文件结束
    inf.readEof();

    return 0;
}

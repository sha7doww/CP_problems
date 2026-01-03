#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 读取第一行：n
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    // 读取 n 行查询
    for (int i = 0; i < n; i++) {
        int x = inf.readInt(0, 1000000000, format("x[%d]", i + 1));
        inf.readSpace();
        int l = inf.readInt(0, 29, format("l[%d]", i + 1));
        inf.readSpace();
        int r = inf.readInt(0, 29, format("r[%d]", i + 1));
        inf.readEoln();

        // 验证 l <= r（这是格式约束）
        ensure(l <= r);
    }

    // 确保文件结束
    inf.readEof();

    return 0;
}

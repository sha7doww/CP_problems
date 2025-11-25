#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 读取第一行：n 和 k
    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 10000, "k");
    inf.readEoln();

    // 读取第二行：n 个木棒长度
    for (int i = 0; i < n; i++) {
        inf.readInt(1, 100000000, format("L[%d]", i + 1));
        if (i < n - 1) {
            inf.readSpace();
        }
    }
    inf.readEoln();

    // 确保文件结束
    inf.readEof();

    return 0;
}

#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(n - 1, 300000, "m");
    inf.readEoln();

    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, format("u[%d]", i + 1));
        inf.readSpace();
        int v = inf.readInt(1, n, format("v[%d]", i + 1));
        inf.readSpace();
        inf.readInt(1, 1000000000, format("w[%d]", i + 1));
        inf.readEoln();
    }

    inf.readEof();

    return 0;
}

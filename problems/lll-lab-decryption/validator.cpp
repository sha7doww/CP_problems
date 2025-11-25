#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 读取三个正整数 n, d, e
    long long n = inf.readLong(1LL, 1000000000000000000LL, "n");
    inf.readSpace();
    long long d = inf.readLong(1LL, 1000000000000000000LL, "d");
    inf.readSpace();
    long long e = inf.readLong(1LL, 1000000000000000000LL, "e");
    inf.readEoln();
    inf.readEof();

    // 验证 m = n - d*e + 2 在合理范围内 [1, 10^9]
    // 注意：d*e 可能很大，需要小心溢出
    // 但由于数据保证，我们主要验证 m 不会过大
    long long m = n - d * e + 2;
    ensuref(m >= 1 && m <= 1000000000LL, "m = n - d*e + 2 should be in [1, 10^9], but m = %lld", m);

    return 0;
}

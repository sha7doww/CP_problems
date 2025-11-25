#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read two integers with validation
    long long a = inf.readLong(-1000000000LL, 1000000000LL, "a");
    inf.readSpace();
    long long b = inf.readLong(-1000000000LL, 1000000000LL, "b");
    inf.readEoln();
    inf.readEof();

    return 0;
}
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Validate exactly 10 integers
    for (int i = 0; i < 10; i++) {
        long long x = inf.readLong(0LL, 1000000000LL, "x");
        if (i < 9) {
            inf.readSpace();
        }
    }
    inf.readEoln();
    inf.readEof();

    return 0;
}
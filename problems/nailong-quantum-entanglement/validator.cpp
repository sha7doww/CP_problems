#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    long long K = inf.readLong(0LL, 500000LL, "K");
    inf.readEoln();

    // Ensure end of file
    inf.readEof();

    return 0;
}

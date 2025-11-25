#include "testlib.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Get test case type from command line
    string test_type = argc >= 2 ? argv[1] : "random";

    if (test_type == "random") {
        // Random test case
        long long a = rnd.next(-1000000000LL, 1000000000LL);
        long long b = rnd.next(-1000000000LL, 1000000000LL);
        cout << a << " " << b << endl;
    }
    else if (test_type == "max") {
        // Maximum values
        cout << "1000000000 1000000000" << endl;
    }
    else if (test_type == "min") {
        // Minimum values
        cout << "-1000000000 -1000000000" << endl;
    }
    else if (test_type == "zero") {
        // Zero values
        cout << "0 0" << endl;
    }
    else if (test_type == "positive") {
        // Positive values only
        cout << rnd.next(1, 1000000000) << " " << rnd.next(1, 1000000000) << endl;
    }
    else if (test_type == "negative") {
        // Negative values only
        cout << -rnd.next(1, 1000000000) << " " << -rnd.next(1, 1000000000) << endl;
    }
    else {
        // Default random if unknown type
        long long a = rnd.next(-1000000000LL, 1000000000LL);
        long long b = rnd.next(-1000000000LL, 1000000000LL);
        cout << a << " " << b << endl;
    }

    return 0;
}
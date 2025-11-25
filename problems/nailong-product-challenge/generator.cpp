#include "testlib.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Get test case type from command line
    string test_type = argc >= 2 ? argv[1] : "random";

    if (test_type == "all_ones") {
        // All ones - product = 1
        for (int i = 0; i < 10; i++) {
            cout << 1;
            if (i < 9) cout << " ";
        }
        cout << endl;
    }
    else if (test_type == "zero") {
        // Contains zero - product = 0
        for (int i = 0; i < 10; i++) {
            if (i == 0) cout << 0;
            else cout << rnd.next(1, 1000);
            if (i < 9) cout << " ";
        }
        cout << endl;
    }
    else if (test_type == "small") {
        // Small numbers - product <= 10^9
        for (int i = 0; i < 10; i++) {
            cout << rnd.next(1, 10);
            if (i < 9) cout << " ";
        }
        cout << endl;
    }
    else if (test_type == "medium") {
        // Medium numbers - might exceed 10^9
        for (int i = 0; i < 10; i++) {
            cout << rnd.next(100, 1000);
            if (i < 9) cout << " ";
        }
        cout << endl;
    }
    else if (test_type == "large") {
        // Large numbers - definitely exceed 10^9
        for (int i = 0; i < 10; i++) {
            cout << rnd.next(10000, 100000);
            if (i < 9) cout << " ";
        }
        cout << endl;
    }
    else if (test_type == "max") {
        // Maximum values
        for (int i = 0; i < 10; i++) {
            cout << 1000000000;
            if (i < 9) cout << " ";
        }
        cout << endl;
    }
    else if (test_type == "boundary") {
        // Boundary case - product close to 10^9
        cout << "1000000000 1 1 1 1 1 1 1 1 1" << endl;
    }
    else if (test_type == "mixed") {
        // Mixed small and large numbers
        for (int i = 0; i < 10; i++) {
            if (i < 5) {
                cout << rnd.next(1, 100);
            } else {
                cout << rnd.next(1000, 10000);
            }
            if (i < 9) cout << " ";
        }
        cout << endl;
    }
    else if (test_type == "primes") {
        // Prime numbers
        int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        for (int i = 0; i < 10; i++) {
            cout << primes[i];
            if (i < 9) cout << " ";
        }
        cout << endl;
    }
    else if (test_type == "random_safe") {
        // Random numbers that won't exceed 10^9 when multiplied
        // Strategy: use numbers 1-6, since 6^10 = 60,466,176 < 10^9
        for (int i = 0; i < 10; i++) {
            cout << rnd.next(1, 6);
            if (i < 9) cout << " ";
        }
        cout << endl;
    }
    else {
        // Default random case - large numbers that will likely exceed 10^9
        for (int i = 0; i < 10; i++) {
            cout << rnd.next(0, 1000000000);
            if (i < 9) cout << " ";
        }
        cout << endl;
    }

    return 0;
}
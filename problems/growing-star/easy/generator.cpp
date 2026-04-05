#include "testlib.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string mode = argv[1];
    int n = atoi(argv[2]);
    int maxValue = atoi(argv[3]);

    cout << n << endl;

    if (mode == "random") {
        for (int i = 0; i < n; i++) {
            cout << rnd.next(1, maxValue);
            if (i < n - 1) cout << " ";
        }
        cout << endl;
    } else if (mode == "increasing") {
        // Strictly increasing sequence
        int cur = rnd.next(1, maxValue / 2);
        for (int i = 0; i < n; i++) {
            cout << cur;
            if (i < n - 1) cout << " ";
            cur += rnd.next(1, 10);
            if (cur > maxValue) cur = maxValue;
        }
        cout << endl;
    } else if (mode == "decreasing") {
        // Strictly decreasing sequence
        int cur = rnd.next(maxValue / 2, maxValue);
        for (int i = 0; i < n; i++) {
            cout << cur;
            if (i < n - 1) cout << " ";
            cur -= rnd.next(1, 10);
            if (cur < 1) cur = 1;
        }
        cout << endl;
    } else if (mode == "zigzag") {
        // Zigzag pattern: up, down, up, down...
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                cout << rnd.next(1, maxValue / 2);
            } else {
                cout << rnd.next(maxValue / 2 + 1, maxValue);
            }
            if (i < n - 1) cout << " ";
        }
        cout << endl;
    } else if (mode == "same") {
        // All same values
        int val = rnd.next(1, maxValue);
        for (int i = 0; i < n; i++) {
            cout << val;
            if (i < n - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}

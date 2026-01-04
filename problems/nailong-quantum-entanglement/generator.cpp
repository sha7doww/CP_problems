#include "testlib.h"
#include <iostream>
using namespace std;

// Calculate maximum K for given N
long long maxK(int N) {
    int M = N + 1;
    if (M % 2 == 0) {
        long long m = M / 2;
        return m * (m - 1);
    } else {
        long long m = (M - 1) / 2;
        return m * m;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string mode = argc >= 2 ? argv[1] : "random";

    if (mode == "small") {
        // Small N with valid K
        int N = rnd.next(3, 10);
        long long Kmax = maxK(N);
        long long K = rnd.next(0LL, Kmax);
        cout << N << " " << K << endl;
    }
    else if (mode == "medium") {
        // Medium N with valid K
        int N = rnd.next(50, 100);
        long long Kmax = maxK(N);
        long long K = rnd.next(0LL, Kmax);
        cout << N << " " << K << endl;
    }
    else if (mode == "large") {
        // Large N with valid K
        int N = rnd.next(900, 1000);
        long long Kmax = maxK(N);
        long long K = rnd.next(0LL, Kmax);
        cout << N << " " << K << endl;
    }
    else if (mode == "large_max_k") {
        // Large N with maximum K
        int N = 1000;
        long long K = maxK(N);
        cout << N << " " << K << endl;
    }
    else if (mode == "impossible_exceed") {
        // K exceeds maximum possible
        int N = rnd.next(10, 100);
        long long Kmax = maxK(N);
        long long K = Kmax + rnd.next(1, 100);
        cout << N << " " << K << endl;
    }
    else if (mode == "impossible_pigeonhole") {
        // Pigeonhole principle impossible cases
        // These are cases where K can't be achieved due to arrangement constraints
        // For small N, some K values are impossible even if K <= Kmax
        int N = 3;  // N=3, M=4, Kmax=1
        int K = 3;  // Requires C(3,2)=3 but max frequency is 2
        cout << N << " " << K << endl;
    }
    else if (mode == "boundary_min") {
        // Minimum boundary: N=1, K=0
        cout << "1 0" << endl;
    }
    else if (mode == "boundary_n1_k1") {
        // N=1, K=1 is impossible
        cout << "1 1" << endl;
    }
    else if (mode == "boundary_n2_k0") {
        // N=2, K=0
        cout << "2 0" << endl;
    }
    else if (mode == "boundary_n2_k1") {
        // N=2, K=1 is impossible (Kmax=0 for N=2, M=3)
        cout << "2 1" << endl;
    }
    else if (mode == "k_zero") {
        // K=0 cases (should always be solvable)
        int N = rnd.next(1, 1000);
        cout << N << " 0" << endl;
    }
    else if (mode == "specific") {
        // Specific N and K from command line
        int N = argc >= 3 ? atoi(argv[2]) : 10;
        long long K = argc >= 4 ? atoll(argv[3]) : 0;
        cout << N << " " << K << endl;
    }
    else if (mode == "random_solvable") {
        // Random but guaranteed solvable
        int N = rnd.next(5, 500);
        long long Kmax = maxK(N);
        // Use triangular numbers that are easily achievable
        int s = rnd.next(2, min(10, (N + 2) / 2));
        long long K = (long long)s * (s - 1) / 2;
        if (K > Kmax) K = Kmax;
        cout << N << " " << K << endl;
    }
    else {
        // Default: completely random (may or may not be solvable)
        int N = rnd.next(1, 1000);
        long long K = rnd.next(0LL, 500000LL);
        cout << N << " " << K << endl;
    }

    return 0;
}

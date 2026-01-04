#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input
    int N = inf.readInt();
    long long K = inf.readLong();

    // In testlib:
    // ouf = participant's output (Output File)
    // ans = jury's answer (Answer File)

    // Read jury answer first token
    string juryFirst = ans.readToken();

    // Read participant answer first token
    string partFirst = ouf.readToken();

    // Check if jury says -1
    if (juryFirst == "-1") {
        if (partFirst != "-1") {
            // Participant claims solution exists, let's verify
            vector<long long> A;
            A.push_back(stoll(partFirst));
            for (int i = 1; i < N; i++) {
                long long x = ouf.readLong();
                A.push_back(x);
            }

            // Verify constraints
            for (int i = 0; i < N; i++) {
                if (A[i] < 1 || A[i] > 1000000000LL) {
                    quitf(_wa, "Element A[%d] = %lld is out of range [1, 10^9]",
                          i + 1, A[i]);
                }
            }

            // Count subarrays with XOR sum = 0
            long long count = 0;
            for (int l = 0; l < N; l++) {
                long long xorSum = 0;
                for (int r = l; r < N; r++) {
                    xorSum ^= A[r];
                    if (xorSum == 0) count++;
                }
            }

            if (count == K) {
                // Participant found a valid solution that jury missed!
                quitf(_ok, "Participant found valid solution (jury claimed -1)");
            } else {
                quitf(_wa, "Participant output has %lld zero-xor subarrays, expected %lld",
                      count, K);
            }
        }
        quitf(_ok, "Correctly identified no solution");
    }

    // Jury has a solution
    if (partFirst == "-1") {
        quitf(_wa, "Participant says -1 but solution exists");
    }

    // Parse participant's array
    vector<long long> A;
    A.push_back(stoll(partFirst));
    for (int i = 1; i < N; i++) {
        long long x = ouf.readLong();
        A.push_back(x);
    }

    // Verify array length
    if ((int)A.size() != N) {
        quitf(_wa, "Expected %d elements, got %d", N, (int)A.size());
    }

    // Verify constraints: all elements must be in [1, 10^9]
    for (int i = 0; i < N; i++) {
        if (A[i] < 1 || A[i] > 1000000000LL) {
            quitf(_wa, "Element A[%d] = %lld is out of range [1, 10^9]",
                  i + 1, A[i]);
        }
    }

    // Count subarrays with XOR sum = 0
    long long count = 0;
    for (int l = 0; l < N; l++) {
        long long xorSum = 0;
        for (int r = l; r < N; r++) {
            xorSum ^= A[r];
            if (xorSum == 0) count++;
        }
    }

    if (count != K) {
        quitf(_wa, "Participant output has %lld zero-xor subarrays, expected %lld",
              count, K);
    }

    quitf(_ok, "Correct: %lld zero-xor subarrays", count);
    return 0;
}

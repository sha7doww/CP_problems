#include "testlib.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 辅助函数：获取一个数的所有因子
vector<long long> getFactors(long long num) {
    vector<long long> factors;
    for (long long i = 1; i * i <= num; i++) {
        if (num % i == 0) {
            factors.push_back(i);
            if (i != num / i) {
                factors.push_back(num / i);
            }
        }
    }
    return factors;
}

// 生成有解数据
void generateSolution(long long minVal, long long maxVal, long long maxSum) {
    long long p, q, n, ed, e, d;
    int attempts = 0;
    const int MAX_ATTEMPTS = 10000;

    while (attempts < MAX_ATTEMPTS) {
        attempts++;

        // 随机生成 p ≤ q
        p = rnd.next(minVal, maxVal);
        q = rnd.next(p, maxVal);

        // 检查 p + q 不超过限制
        if (p + q > maxSum) continue;

        // 计算 n = p * q
        // 注意溢出检查
        if (p > 1e18 / q) continue; // 避免溢出
        n = p * q;

        // 计算 ed = (p-1)(q-1) + 1
        long long p1 = p - 1;
        long long q1 = q - 1;
        if (p1 > 1e18 / q1) continue; // 避免溢出
        ed = p1 * q1 + 1;

        // 随机分解 ed = e * d
        vector<long long> factors = getFactors(ed);
        if (factors.empty()) continue;

        // 随机选择一个因子作为 e
        e = factors[rnd.next(0, (int)factors.size() - 1)];
        d = ed / e;

        // 验证 m = n - e*d + 2 在合理范围内
        long long m = n - e * d + 2;
        if (m < 1 || m > 1000000000LL) continue;

        // 输出结果
        cout << n << " " << d << " " << e << endl;
        return;
    }

    // 如果多次尝试失败，输出一个简单的有解数据
    p = minVal;
    q = minVal;
    n = p * q;
    ed = (p - 1) * (q - 1) + 1;
    cout << n << " " << ed << " " << 1 << endl;
}

// 生成无解数据
void generateNoSolution() {
    // 策略：生成 n, e, d 使得 delta = m^2 - 4n 不是完全平方数
    long long n, e, d, m, delta;
    int attempts = 0;
    const int MAX_ATTEMPTS = 10000;

    while (attempts < MAX_ATTEMPTS) {
        attempts++;

        // 随机生成参数
        n = rnd.next(100LL, 1000000000LL);
        e = rnd.next(1LL, 100000LL);
        d = rnd.next(1LL, 100000LL);

        m = n - e * d + 2;
        if (m < 1 || m > 1000000000LL) continue;

        delta = m * m - 4 * n;
        if (delta < 0) {
            // delta 为负，必定无解
            cout << n << " " << d << " " << e << endl;
            return;
        }

        // 检查是否为完全平方数
        long long sqrtDelta = (long long)sqrtl(delta);
        bool isPerfectSquare = false;
        for (long long candidate = max(0LL, sqrtDelta - 1); candidate <= sqrtDelta + 1; candidate++) {
            if (candidate * candidate == delta) {
                isPerfectSquare = true;
                break;
            }
        }

        if (!isPerfectSquare) {
            // 不是完全平方数，无解
            cout << n << " " << d << " " << e << endl;
            return;
        }

        // 如果是完全平方数，检查是否满足整除条件
        if ((m + sqrtDelta) % 2 != 0) {
            // 不能被2整除，无解
            cout << n << " " << d << " " << e << endl;
            return;
        }
    }

    // 如果多次尝试失败，输出一个明确的无解数据
    // 例如：n 是质数，无法分解为两个大于1的因子
    cout << "633 1 211" << endl;  // 样例2的无解数据
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // 获取测试类型
    string testType = argc >= 2 ? argv[1] : "small";

    if (testType == "small") {
        // 小数据：p, q ∈ [2, 1000]
        generateSolution(2, 1000, 1e9);
    }
    else if (testType == "medium") {
        // 中数据：p, q ∈ [2, 1e6]
        generateSolution(2, 1000000, 1e9);
    }
    else if (testType == "large") {
        // 大数据：p, q ∈ [2, 1e9]，控制 p+q ≤ 1e9
        generateSolution(2, 500000000, 1e9);
    }
    else if (testType == "no_solution") {
        // 无解数据
        generateNoSolution();
    }
    else {
        // 默认：小数据
        generateSolution(2, 1000, 1e9);
    }

    return 0;
}

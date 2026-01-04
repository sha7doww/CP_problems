# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) and other AI agents when working with code in this repository.

## Project Overview

This is a competitive programming problem management system built around the **testlib** library. The system provides standardized tools for creating, testing, and validating algorithm competition problems with automated data generation and validation pipelines.

---

## Step-by-Step Guide: Creating a New Problem from Scratch

Follow these steps when creating a new competitive programming problem:

### Step 1: Create Problem Directory Structure

```bash
# Create the problem directory and data folder
mkdir -p problems/problem-name/data

# The problem-name should use lowercase letters and hyphens (e.g., nailong-wood-sticks)
```

### Step 2: Write Problem Statement (statement.md)

Create `problems/problem-name/statement.md` following this structure:

```markdown
# 题目标题

## 题目描述
[详细的题目背景和要求]

## 输入格式
[详细说明输入格式]
第一行包含...
第二行包含...

**数据范围：**
对于 $100\%$ 的数据，保证 $1 \le n \le 10^4$，$1 \le a_i \le 10^9$。

## 输出格式
[详细说明输出格式]

## 样例输入 1
```
[样例输入内容]
```

## 样例输出 1
```
[样例输出内容]
```

## 样例输入 2
```
[样例输入内容]
```

## 样例输出 2
```
[样例输出内容]
```

## 提示

**样例 1 解释：**
[解释样例 1 的输入输出关系]

**样例 2 解释：**
[解释样例 2 的输入输出关系]
```

**CRITICAL Statement Writing Rules:**

1. **LaTeX for Math**: Use `$10^9$`, `$O(n \log n)$`, `$1 \le n \le 10^5$`
2. **Chinese Typography**: Add spaces between numbers/expressions and Chinese characters
   - Correct: "有 10 个数字"
   - Correct: "不超过 $10^9$"
   - Wrong: "有10个数字"
3. **Maximum 2 Sample Cases**: No more than 2 sample test cases
4. **Sample Explanations in 提示 Section**: Put all sample explanations in the "提示" section, NOT after each sample
5. **No Algorithm Hints**: Do NOT give hints about algorithms, time complexity, or solution approaches in the "提示" section
6. **Data Range in 输入格式 Section**: Put data range ("数据范围") at the END of "输入格式" section, NOT in "提示" section

### Step 3: Write Standard Solution (std.cpp)

Create `problems/problem-name/std.cpp`:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read input
    int n;
    cin >> n;

    // Solution logic

    // Output result
    cout << result << endl;

    return 0;
}
```

**Requirements:**
- Must be correct and efficient
- Should handle all edge cases
- Use standard competitive programming style

### Step 4: Write Generator (generator.cpp)

Create `problems/problem-name/generator.cpp`:

```cpp
#include "testlib.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Parse command-line arguments
    // Example: ./generator <mode> <n> <maxValue> [seed]
    string mode = argv[1];
    int n = atoi(argv[2]);
    int maxValue = atoi(argv[3]);

    // Output based on mode
    cout << n << endl;

    if (mode == "random") {
        for (int i = 0; i < n; i++) {
            cout << rnd.next(1, maxValue);
            if (i < n - 1) cout << " ";
        }
        cout << endl;
    } else if (mode == "small") {
        // Generate small test cases
    } else if (mode == "large") {
        // Generate large test cases
    }

    return 0;
}
```

**Key Points:**
- Use `registerGen(argc, argv, 1)` at the beginning
- Use `rnd.next(l, r)` for random number generation in range [l, r]
- Use `rnd.any(...)` for other random operations
- Parameters are passed via command line: `./generator arg1 arg2 arg3 ...`

### Step 5: Write Validator (validator.cpp)

Create `problems/problem-name/validator.cpp`:

```cpp
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate first line
    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    // Read and validate second line
    for (int i = 0; i < n; i++) {
        inf.readInt(1, 1000000000, format("a[%d]", i + 1));
        if (i < n - 1) {
            inf.readSpace();
        }
    }
    inf.readEoln();

    // Ensure end of file
    inf.readEof();

    return 0;
}
```

**CRITICAL Validator Rules:**

1. **Only Validate Format and Range**: Validator should ONLY check:
   - Input format (spaces, newlines, EOF)
   - Data type and range (e.g., 1 ≤ n ≤ 10000)

2. **Do NOT Validate Business Logic**: Validator should NOT check:
   - Relationships between variables (e.g., k ≤ n, unless explicitly required by problem constraints)
   - Problem-specific constraints that depend on solution logic
   - Whether the input is "solvable" or not

3. **Example of What NOT to Do**:
   ```cpp
   // WRONG: Don't validate business logic in validator
   int n = inf.readInt(1, 10000, "n");
   int k = inf.readInt(1, 10000, "k");
   ensure(k <= n);  // ❌ This is business logic, not format validation
   ```

4. **testlib Functions:**
   - `inf.readInt(min, max, name)` - Read and validate integer
   - `inf.readEoln()` - Ensure end of line
   - `inf.readSpace()` - Ensure single space
   - `inf.readEof()` - Ensure end of file
   - `ensure(condition)` - Assert a condition (ONLY takes 1 parameter, no error message)

5. **Common Mistake with `ensure` macro**:
   ```cpp
   // WRONG: ensure only takes 1 parameter
   ensure(k <= n, "k must be less than or equal to n");  // ❌ Compilation error

   // CORRECT: ensure takes only the condition
   ensure(k <= n);  // ✓ But still wrong if this is business logic!
   ```

### Step 6: Write Data Generation Script (generate.sh)

Create `problems/problem-name/generate.sh`:

```bash
#!/bin/bash

# Sample data (manually created)
cat > data/sample_1.in << EOF
4 11
802 743 457 539
EOF

cat > data/sample_2.in << EOF
3 5
100 50 30
EOF

# Test data (generated by generator)
./generator small 5 100 1 > data/small_1.in
./generator random 100 10000 2 > data/medium_1.in
./generator large 10000 1000000000 3 > data/large_1.in

# Edge cases
./generator edge 10000 1000000000 4 > data/edge_max.in
```

**File Naming Rules:**
- Sample files: `sample_1.in`, `sample_1.out`, `sample_2.in`, `sample_2.out` (MUST use `sample_` prefix)
- Test files: Descriptive names WITHOUT `sample_` prefix
  - Examples: `small_1.in`, `medium_1.in`, `large_1.in`, `edge_max.in`, `random_1.in`
- Output files: Same base name with `.out` extension (e.g., `small_1.in` → `small_1.out`)

**Test Case Count Rule:**
- The number of **non-sample** test cases MUST be divisible by 100
- This ensures each test case has an integer point value (e.g., 20 cases = 5 points each, 25 cases = 4 points each)
- Example distributions:
  - 20 test cases: 5 points each (recommended)
  - 25 test cases: 4 points each
  - 10 test cases: 10 points each
- Sample test cases (sample_1, sample_2) do NOT count toward points

### Step 7: Run the Pipeline

```bash
# Make generate.sh executable
chmod +x problems/problem-name/generate.sh

# Run the pipeline from project root
./scripts/pipeline.sh problems/problem-name

# Or run from problem directory
cd problems/problem-name
../../scripts/pipeline.sh
```

**Pipeline Process:**
1. Compiles all C++ components (std, generator, validator, checker if present)
2. Runs `generate.sh` to create `.in` files
3. Validates all `.in` files using validator
4. Generates `.out` files by running std program
5. Verifies outputs using checker (if present)

### Step 8: Fix Any Issues

If pipeline fails:

1. **Compilation Errors**: Check C++ syntax, testlib.h path
2. **Validation Errors**:
   - Check if validator is too strict (removing business logic checks)
   - Verify data ranges in validator match problem statement
3. **Runtime Errors**: Check std.cpp logic, handle edge cases

---

## Project Architecture

### Directory Structure

```
CP_problems/
├── README.md                   # User documentation (for humans)
├── CLAUDE.md                   # This file (for AI agents)
├── testlib.h                   # Testlib library header
├── scripts/
│   └── pipeline.sh             # Automation script
└── problems/
    └── problem-name/
        ├── statement.md        # Problem statement
        ├── std.cpp             # Standard solution (required)
        ├── std.py              # Python solution (optional)
        ├── generator.cpp       # Test data generator
        ├── validator.cpp       # Input validator
        ├── checker.cpp         # Output checker (optional, for multi-solution problems)
        ├── generate.sh         # Data generation script
        └── data/               # Test data directory
            ├── sample_1.in     # Sample input 1
            ├── sample_1.out    # Sample output 1
            ├── sample_2.in     # Sample input 2
            ├── sample_2.out    # Sample output 2
            ├── small_1.in      # Small test case
            ├── small_1.out
            └── ...
```

### Data Flow Pipeline

1. **Generation Phase**:
   - `generate.sh` script runs
   - Calls `generator` executable with different parameters
   - Creates all `.in` files in `data/` directory

2. **Validation Phase**:
   - `validator` checks each `.in` file
   - Ensures format compliance and range validity
   - Fails if any `.in` file is invalid

3. **Solution Phase**:
   - `std` program runs on each `.in` file
   - Generates corresponding `.out` files
   - Never manually create `.out` files!

4. **Verification Phase** (if checker exists):
   - `checker` validates outputs
   - Useful for problems with multiple valid solutions

---

## Testlib Integration Details

### Key testlib Functions

**Generator (`registerGen`):**
```cpp
registerGen(argc, argv, 1);
int x = rnd.next(1, 100);           // Random int in [1, 100]
long long y = rnd.next(1LL, 1e18);  // Random long long
double z = rnd.next(0.0, 1.0);      // Random double
```

**Validator (`registerValidation`):**
```cpp
registerValidation(argc, argv);
int n = inf.readInt(1, 1000, "n");  // Read int in [1, 1000]
inf.readSpace();                     // Expect single space
inf.readEoln();                      // Expect end of line
inf.readEof();                       // Expect end of file
ensure(condition);                   // Assert condition (1 parameter only!)
```

**Checker (`registerTestlibCmd`):**
```cpp
registerTestlibCmd(argc, argv);
int jury_ans = ouf.readInt();       // Read from jury output
int part_ans = ans.readInt();       // Read from participant output
quitf(_ok, "Correct");              // Accept
quitf(_wa, "Wrong answer");         // Wrong answer
```

### Common testlib Pitfalls

1. **`ensure` macro only takes 1 parameter**:
   ```cpp
   // ❌ WRONG - Compilation error
   ensure(k <= n, "error message");

   // ✓ CORRECT
   ensure(k <= n);
   ```

2. **Don't confuse validator and checker**:
   - Validator: Checks INPUT format
   - Checker: Checks OUTPUT correctness

3. **Validator should not validate business logic**:
   - Only check format, data types, and basic ranges
   - Don't check problem-specific constraints that depend on solution

---

## Compilation Details

### Manual Compilation Commands

```bash
# Compile standard solution with debug flags
g++ -std=c++17 -O2 -Wall -Wextra -D_GLIBCXX_DEBUG std.cpp -o std

# Compile testlib components WITHOUT debug flags (faster compilation)
g++ -std=c++17 -O2 -Wall -Wextra generator.cpp -o generator
g++ -std=c++17 -O2 -Wall -Wextra validator.cpp -o validator
g++ -std=c++17 -O2 -Wall -Wextra checker.cpp -o checker
```

**Note**: Testlib components compile very slowly with `-D_GLIBCXX_DEBUG`, so avoid using it for generator/validator/checker.

### testlib.h Setup

If `testlib.h` is missing from project root:

```bash
wget https://raw.githubusercontent.com/MikeMirzayanov/testlib/master/testlib.h
```

---

## Common Issues and Solutions

### Issue 1: Validator Compilation Error with `ensure`

**Error Message:**
```
validator.cpp:14:55: error: macro "ensure" passed 2 arguments, but takes just 1
```

**Cause:** Trying to pass error message to `ensure` macro

**Solution:** Use `ensure` with only the condition:
```cpp
// Change from:
ensure(k <= n, "k must be less than or equal to n");

// To:
ensure(k <= n);
```

### Issue 2: Sample Data Validation Failure

**Error Message:**
```
[ERROR] ✗ sample_1.in is INVALID
FAIL Condition failed: "k <= n"
```

**Cause:** Validator checking business logic instead of format

**Problem:** Sample has k=11, n=4 (k > n), but this is valid for the problem (cutting wood sticks allows k > n)

**Solution:** Remove business logic checks from validator:
```cpp
// Remove this line if it's business logic:
ensure(k <= n);

// Only keep format and basic range checks:
int n = inf.readInt(1, 10000, "n");
int k = inf.readInt(1, 10000, "k");
```

### Issue 3: Wrong Data Range in Problem Statement

**Problem:** Statement says "k ≤ n" but samples have k > n

**Solution:** Update data range in `statement.md` to reflect actual constraints:
```markdown
对于 $100\%$ 的数据，保证 $1 \le n \le 10^4$，$1 \le k \le 10^4$，$1 \le L_i \le 10^8$。
```

---

## Best Practices

### For Problem Creation

1. **Start with Simple Samples**: Create 1-2 representative samples that clearly demonstrate I/O format
2. **Write std.cpp First**: Ensure your solution is correct before generating test data
3. **Generate Data Systematically**: Cover small, medium, large, edge cases, and random cases
4. **Validate Early**: Run validator on each `.in` file as you create it
5. **Test std Program**: Manually test std on samples before running pipeline

### For Validators

1. **Keep It Simple**: Only validate what's necessary (format + basic ranges)
2. **No Business Logic**: If a constraint depends on the solution, don't check it in validator
3. **Clear Variable Names**: Use descriptive names in error messages
4. **Test Validator**: Run it on both valid and invalid inputs to ensure it works

### For Data Generation

1. **Cover All Cases**:
   - Minimum values (n=1, values=1)
   - Maximum values (n=10000, values=10^9)
   - Edge cases (all same, all different, sorted, reverse sorted)
   - Random cases (various sizes and distributions)

2. **Use Descriptive Filenames**: `edge_all_same.in`, `random_large_1.in`, `boundary_min.in`

3. **Reproducibility**: Same generator parameters should produce same output (testlib ensures this)

---

## Quick Reference

### Problem Creation Checklist

- [ ] Create directory: `problems/problem-name/data`
- [ ] Write `statement.md` (max 2 samples, LaTeX math, proper formatting)
- [ ] Write `std.cpp` (correct and efficient)
- [ ] Write `generator.cpp` (using testlib)
- [ ] Write `validator.cpp` (format only, no business logic)
- [ ] Write `generate.sh` (sample data + generated test data)
- [ ] Run `chmod +x generate.sh`
- [ ] Run `./scripts/pipeline.sh problems/problem-name`
- [ ] Fix any validation or compilation errors
- [ ] Verify all `.out` files are correct

### testlib Quick Reference

```cpp
// Generator
registerGen(argc, argv, 1);
rnd.next(l, r)              // Random int in [l, r]

// Validator
registerValidation(argc, argv);
inf.readInt(l, r, "name")   // Read and validate int
inf.readSpace()              // Expect space
inf.readEoln()               // Expect newline
inf.readEof()                // Expect EOF
ensure(condition)            // Assert (1 param only!)

// Checker
registerTestlibCmd(argc, argv);
ouf.readInt()                // Read jury output
ans.readInt()                // Read participant output
quitf(_ok, "message")        // Accept
quitf(_wa, "message")        // Reject
```

---

## Additional Notes

- **Output Generation**: NEVER manually create `.out` files. Always use: `./std < input.in > output.out`
- **Sample Files**: Must use `sample_` prefix for sample data files
- **Pipeline Script**: Handles compilation, generation, validation, and output creation automatically
- **Testlib Path**: Ensure `testlib.h` is in project root or current directory when compiling

---

**Last Updated**: 2025-11-25
**Target Audience**: AI agents (Claude Code, etc.)

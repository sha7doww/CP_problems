# CP Problems - 算法竞赛题目管理系统

基于 **testlib** 库的标准化算法竞赛题目管理系统，提供自动化的题目创建、测试数据生成和验证流程。

---

## ✨ 特性

- 🤖 **AI 辅助创建**：支持使用 Claude Code 等 AI 工具自动创建题目
- 🔄 **自动化流水线**：一键编译、生成、验证和测试数据
- 📝 **标准化格式**：基于 testlib 的规范化题目结构
- ✅ **数据验证**：自动验证输入格式和输出正确性
- 🎯 **完整模板**：包含示例题目，可直接复制使用

---

## 📦 项目结构

```
CP_problems/
├── README.md                   # 本文档（用户指南）
├── CLAUDE.md                   # AI Agent 指南（供 Claude Code 使用）
├── testlib.h                   # Testlib 库头文件
├── scripts/
│   └── pipeline.sh             # 自动化流水线脚本
└── problems/
    ├── example-sum/            # 示例题目
    └── problem-name/           # 你的题目
        ├── statement.md        # 题面描述
        ├── std.cpp             # C++ 标准程序（必需）
        ├── std.py              # Python 标准程序（可选）
        ├── generator.cpp       # 测试数据生成器
        ├── validator.cpp       # 输入验证器
        ├── checker.cpp         # 输出检查器（多解题需要）
        ├── generate.sh         # 数据生成脚本
        └── data/               # 测试数据目录
            ├── sample_1.in     # 样例输入 1
            ├── sample_1.out    # 样例输出 1
            ├── sample_2.in     # 样例输入 2
            ├── sample_2.out    # 样例输出 2
            └── ...             # 其他测试数据
```

---

## 🚀 快速开始

### 方式 1：使用 Claude Code 创建题目（推荐）

如果你有 Claude Code 或其他 AI code agent：

1. **打开 Claude Code**，导航到项目根目录

2. **告诉 AI 你想创建的题目**，例如：
   ```
   请帮我创建一道关于二分查找的算法题目，
   背景是奶龙和小七的故事
   ```

3. **AI 会自动完成**：
   - 创建问题目录结构
   - 编写题面描述 (`statement.md`)
   - 实现标准解答 (`std.cpp`)
   - 编写数据生成器 (`generator.cpp`)
   - 编写验证器 (`validator.cpp`)
   - 生成测试数据脚本 (`generate.sh`)
   - 运行 pipeline 生成所有测试数据

4. **检查结果**：
   ```bash
   ls problems/your-problem-name/data/
   # 应该看到生成的 .in 和 .out 文件
   ```

**注意**：AI 会自动参考 `CLAUDE.md` 文档来正确创建题目，无需手动干预。

### 方式 2：手动创建题目

如果你想手动创建题目：

#### 步骤 1：创建目录结构

```bash
mkdir -p problems/my-problem/data
cd problems/my-problem
```

#### 步骤 2：创建必需文件

至少需要以下文件：
- `statement.md` - 题面描述（参考 `problems/example-sum/statement.md`）
- `std.cpp` - C++ 标准程序
- `generate.sh` - 数据生成脚本

可选文件：
- `generator.cpp` - 自动化数据生成器（推荐）
- `validator.cpp` - 输入验证器（推荐）
- `checker.cpp` - 输出检查器（多解题需要）
- `std.py` - Python 标准程序

#### 步骤 3：运行自动化流水线

```bash
# 方式 A：从项目根目录运行
./scripts/pipeline.sh problems/my-problem

# 方式 B：从题目目录运行
cd problems/my-problem
../../scripts/pipeline.sh
```

流水线会自动：
1. 编译所有 C++ 组件
2. 运行 `generate.sh` 生成 `.in` 文件
3. 使用 `validator` 验证所有输入文件
4. 运行 `std` 程序生成 `.out` 文件
5. 使用 `checker` 验证输出（如果存在）

---

## 📝 文件说明

### 1. 题面描述 (statement.md)

题面使用 Markdown 格式，必须包含以下部分：

- 题目描述
- 输入格式（包含数据范围）
- 输出格式
- 样例输入/输出（最多 2 个样例）
- 提示（仅包含样例解释）

**格式要求**：
- 数学表达式使用 LaTeX：`$10^9$`、`$O(n \log n)$`
- 中文排版：数字/表达式和汉字之间加空格
- 样例数量：最多 2 个
- 样例解释：放在"提示"部分，不要放在样例后面
- **数据范围**：放在"输入格式"部分的末尾，不要放在"提示"部分

### 2. 标准程序 (std.cpp)

标准解答程序，必须：
- 正确处理所有测试数据
- 时间复杂度合理（通常 < 1 秒）
- 使用标准竞赛编程风格

### 3. 数据生成器 (generator.cpp)

使用 testlib 库生成随机或特定测试数据：

```cpp
#include "testlib.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);
    cout << n << endl;

    for (int i = 0; i < n; i++) {
        cout << rnd.next(1, 1000000) << " ";
    }
    cout << endl;

    return 0;
}
```

### 4. 输入验证器 (validator.cpp)

验证输入数据格式和范围：

```cpp
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readInt(1, 1000000, "a[i]");
        if (i < n - 1) inf.readSpace();
    }
    inf.readEoln();
    inf.readEof();

    return 0;
}
```

**重要**：验证器只检查格式和基本范围，不检查业务逻辑。

### 5. 数据生成脚本 (generate.sh)

自动生成所有测试数据：

```bash
#!/bin/bash

# 样例数据（手动创建）
cat > data/sample_1.in << EOF
5
1 2 3 4 5
EOF

cat > data/sample_2.in << EOF
3
10 20 30
EOF

# 测试数据（使用生成器）
./generator 10 1 > data/small_1.in
./generator 1000 2 > data/medium_1.in
./generator 100000 3 > data/large_1.in
```

---

## 🔧 手动操作指南

### 编译程序

```bash
# 编译标准程序（使用调试标志）
g++ -std=c++17 -O2 -Wall -Wextra -D_GLIBCXX_DEBUG std.cpp -o std

# 编译 testlib 组件（不使用调试标志，编译更快）
g++ -std=c++17 -O2 -Wall -Wextra generator.cpp -o generator
g++ -std=c++17 -O2 -Wall -Wextra validator.cpp -o validator
g++ -std=c++17 -O2 -Wall -Wextra checker.cpp -o checker
```

### 生成测试数据

```bash
# 使用生成器创建输入文件
./generator 100 > data/test_1.in

# 验证输入文件
./validator < data/test_1.in

# 生成输出文件（NEVER手动创建！）
./std < data/test_1.in > data/test_1.out

# 使用检查器验证答案（可选）
./checker data/test_1.in data/test_1.out data/test_1.out
```

### 测试程序

```bash
# 测试标准程序
./std < data/sample_1.in

# 使用 Python 标准程序
python3 std.py < data/sample_1.in
```

---

## 📋 测试数据命名规范

### 必须遵守的规则

1. **样例数据**：必须使用 `sample_` 前缀
   - `sample_1.in`, `sample_1.out`
   - `sample_2.in`, `sample_2.out`

2. **测试数据**：使用描述性名称，不使用 `sample_` 前缀
   - 小数据：`small_1.in`, `small_2.in`
   - 中等数据：`medium_1.in`, `medium_2.in`
   - 大数据：`large_1.in`, `large_2.in`, `large_max.in`
   - 边界数据：`edge_min.in`, `edge_max.in`, `edge_all_same.in`
   - 随机数据：`random_1.in`, `random_2.in`

3. **输出文件**：与输入文件同名，扩展名为 `.out`
   - `small_1.in` → `small_1.out`

4. **输出文件生成**：所有 `.out` 文件必须通过标准程序生成，禁止手动创建

5. **测试点数量**：非样例测试点数量必须能整除 100
   - 这样每个测试点的分值为整数（如 20 个测试点 = 每个 5 分）
   - 推荐：20 个（每个 5 分）、25 个（每个 4 分）、10 个（每个 10 分）
   - 样例（sample_1, sample_2）不计入分数

---

## 🛠️ 环境配置

### 安装 testlib.h

testlib.h 应该已经在项目根目录中。如果缺失：

```bash
wget https://raw.githubusercontent.com/MikeMirzayanov/testlib/master/testlib.h
```

### 系统要求

- **编译器**：g++ 支持 C++17（推荐 g++ 7.0+）
- **操作系统**：Linux / macOS / WSL
- **Python**（可选）：Python 3.6+ （如果使用 Python 标准程序）

---

## 🤖 使用 AI Agent 的优势

使用 Claude Code 或其他 AI code agent 创建题目有以下优势：

1. **自动化流程**：AI 会自动完成所有步骤，无需手动操作
2. **规范化代码**：AI 会参考 `CLAUDE.md` 确保代码符合规范
3. **完整测试**：AI 会生成多种测试数据（小、中、大、边界、随机）
4. **错误修复**：AI 会自动检测和修复编译/验证错误
5. **背景故事**：可以要求 AI 创建有趣的题目背景

**示例对话**：

```
用户：请创建一道关于动态规划的题目，背景是奶龙收集宝石

AI：我来帮你创建一道动态规划题目...
    [自动创建所有文件]
    [运行 pipeline]
    题目已创建完成！位于 problems/nailong-gems/
```

---

## 📚 常见问题

### Q: 如何处理多组测试数据？

每组测试数据应该是独立的 `.in` 和 `.out` 文件对。pipeline 会自动处理所有文件。

### Q: validator 是必需的吗？

不是必需的，但强烈推荐。它可以帮助发现数据生成器的 bug，确保数据合法性。

### Q: checker 和 validator 有什么区别？

- **validator**：验证**输入数据**是否合法（格式、范围）
- **checker**：验证选手的**输出答案**是否正确（用于多解题）

### Q: 为什么样例数量限制在 2 个以内？

- 控制篇幅：过多样例会让题面冗长
- 突出重点：1-2 个代表性样例足以说明格式
- 避免暗示：过多样例可能无意中透露解题思路
- 行业标准：大多数竞赛平台都采用类似限制

### Q: 为什么不能手动创建 .out 文件？

手动创建容易出错。所有输出文件必须通过标准程序生成，确保正确性和一致性。

### Q: 如何创建交互题？

交互题需要特殊的 `interactor.cpp`，这是 testlib 的高级用法。请参考 testlib 官方文档。

### Q: pipeline 脚本失败了怎么办？

1. 检查编译错误（C++ 语法、testlib.h 路径）
2. 检查验证错误（validator 是否太严格）
3. 检查运行时错误（std.cpp 逻辑是否正确）
4. 查看错误信息，通常会指出具体问题

---

## 🎯 最佳实践

### 题目创建建议

1. **从示例开始**：复制 `problems/example-sum` 作为模板
2. **先写样例**：确保样例清晰展示输入输出格式
3. **测试标准程序**：在生成测试数据前确保 std.cpp 正确
4. **覆盖所有情况**：生成小、中、大、边界和随机测试数据
5. **验证输出**：检查生成的 `.out` 文件是否正确

### 数据生成建议

测试数据应该覆盖：
- **最小值**：n=1, values=1
- **最大值**：n=10^5, values=10^9
- **边界情况**：全部相同、全部不同、已排序、逆序
- **随机情况**：各种规模和分布

### 题面编写建议

1. **背景有趣**：使用生动的故事背景（如奶龙和小七）
2. **描述清晰**：避免歧义，明确说明输入输出格式
3. **数学规范**：所有数学表达式使用 LaTeX 格式
4. **样例代表性**：选择能体现题意的典型样例
5. **不要剧透**：提示部分不要透露算法和解法

---

## 🔗 相关资源

- [Testlib 官方仓库](https://github.com/MikeMirzayanov/testlib)
- [Codeforces Polygon 平台](https://polygon.codeforces.com/)
- [ICPC 题目标准](https://icpc.io/problem-package-format/)
- [Claude Code 官网](https://claude.ai/code)

---

## 📞 获取帮助

遇到问题时：

1. 查看本文档的常见问题部分
2. 参考 `CLAUDE.md` 了解详细的技术细节
3. 检查 `problems/example-sum/` 示例题目
4. 查看 testlib 官方文档

---

## 🎉 开始创建你的第一道题目

**推荐方式**：使用 Claude Code
```
打开 Claude Code，告诉它：
"请帮我创建一道关于[算法主题]的题目，背景是[故事背景]"
```

**手动方式**：
```bash
mkdir -p problems/my-first-problem/data
cd problems/my-first-problem
# 编写 statement.md, std.cpp, generate.sh
chmod +x generate.sh
../../scripts/pipeline.sh
```

**从模板开始**：
```bash
cp -r problems/example-sum problems/my-problem
cd problems/my-problem
# 修改文件内容
../../scripts/pipeline.sh
```

---

**维护者**：sha7dow
**最后更新**：2025-11-25
**版本**：1.0.0

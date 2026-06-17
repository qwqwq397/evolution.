# Copilot 使用指南 (仓库特定)

本文件面向来此仓库协助编码的 AI 助手，提供快速上手的项目结构、构建/运行流程、以及代码风格与常见模式说明。请严格遵守并在不确定处询问开发者。

- **项目类型**：Windows 本地 Win32 GUI 应用，纯 C++ (C++11)，通过 MinGW/g++ 构建，UI 使用原生 Win32 API（owner-draw 按钮、ListBox、tooltips 等）。主要入口：[src/main.cpp](src/main.cpp)。
- **关键模块**：
  - UI 层：`Window` 类负责全部窗口和控件，[src/ui/Window.cpp](src/ui/Window.cpp) / [include/ui/Window.h](include/ui/Window.h)。
  - 游戏状态：状态字段与 `GameState` 结构位于 `Window` 类内，历史/回滚以 `history_` 向量保存。
  - 兼容/遗留：有 `unused/LegacyComponents.h` 被包含以作参考但非活动依赖（见 [src/main.cpp](src/main.cpp)）。

- **构建 & 运行（重要）**：
  - 静态发布（一键脚本）：运行 `工具/编译游戏.bat`，会在当前目录生成静态链接的 `EvolutionGame.exe`（使用 `-static` 标志）。
  - 开发/调试任务：工作区提供名为 `build EvolutionGame` 的 VS Code 任务（使用 g++ 编译到 `build\\EvolutionGame.exe`，参考任务配置）。
  - 启动：`工具/启动游戏.bat` 会以 `start EvolutionGame.exe` 启动可执行文件。
  - 环境：依赖 Windows SDK（Win32 API）与 MinGW g++ 工具链；在 CI/贡献说明前先确认本机能编译 GUI 程序（mwindows 选项）。

- **代码风格 / 项目约定（可被 AI 采用）**：
  - 以 `Evolution` 命名空间为主；类/方法名 PascalCase，私有字段以 `_` 结尾（例如 `hwnd_`）。
  - UI 控件通过固定整数 ID（`ID_*`）管理，添加/修改控件时请同步更新头文件中的 ID 列表（在 `include/ui/Window.h`）。
  - 使用 `DEBUG_ASSERT(...)` 宏在 debug 下触发断点，AI 在修改代码时保留这些断言以帮助本地调试。
  - 避免引入外部 GUI 框架或 STL-heavy 改动；项目以最小依赖（Windows 原生 API + 基础 STL）为目标。

- **常见实现模式（示例）**：
  - 窗口类绑定：`WinMain` 创建 `Window` 实例并调用 `Create`，窗口过程通过 `WM_NCCREATE` 将 `this` 绑定到 `GWLP_USERDATA`（见 [src/ui/Window.cpp](src/ui/Window.cpp)）。
  - 控件布局：按三列（左、中央、右）布局，改变窗口大小通过 `ResizeControls` 调整位置与尺寸。
  - Tooltip / 日志：使用原生 `LISTBOX` 作为日志视图并通过 `InitTooltips`/`AddTooltip` 管理提示文本。

- **修改/扩展约束**：
  - 任何改变控件 ID、消息处理或窗口类名必须同时更新 `include/ui/Window.h` 与 `src/ui/Window.cpp`，以避免运行时错误。
  - 新增依赖（第三方库）必须在文档中说明并提供静态/动态构建说明；默认优先保持目前的纯 Win32 + g++ 可移植性。

- **调试提示**：
  - 在调试构建中保留 `_CrtDbgBreak()` 风格断点（`DEBUG_ASSERT`）以便本地调试器捕获。
  - 要快速运行：先用 `工具/编译游戏.bat` 或 VS Code 的 `build EvolutionGame` 任务构建，再运行 `工具/启动游戏.bat`。

- **变更合并策略（当 AI 修改代码时）**：
  - 小范围改动：尽量将更改限制在单一文件并附带清晰注释（在 commit 信息中说明改动目的）。
  - 结构性改动：在实现前先提出设计建议并等待人类确认（例如：拆分 `Window` 大类、引入消息分发器等）。

如果有不明确的地方（例如希望重构 UI 或添加新依赖），请先向我询问以获得确认再提交更大改动。反馈或补充请说明你希望我重点展开的部分。

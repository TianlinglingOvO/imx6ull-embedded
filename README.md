# imx6ull-embedded

嵌入式原理课程期末大作业仓库（基于正点原子 I.MX6ULL 开发板，Linux 4.1.15 + Linaro GCC 4.9.4）。

> 本仓库用于版本化管理大作业过程中的自研代码、U-Boot/内核改动与补丁、设备树、开机画面资源、驱动与应用（含 Qt）、构建脚本以及进度文档。大型上游源码压缩包与编译产物已通过 [`.gitignore`](./.gitignore) 忽略。

## 目录规划

```text
.
├── README.md                 # 项目说明
├── TASKS.md                  # 阶段任务清单
├── CHANGELOG.md              # 按时间倒序的变更日志
├── .gitignore                # 嵌入式构建产物与大文件忽略规则
└── scripts/
    └── git-hooks/
        └── pre-commit        # 提交前检查是否同步更新 TASKS.md / CHANGELOG.md
```

*(后续将按任务逐步新增 `uboot/`、`kernel/`、`psplash/`、`mfgtool/`、`drivers/`、`apps/` 等子目录。)*

## 开发与编译环境

- **宿主机**：Ubuntu 24.04 LTS (x86_64)
- **交叉编译器**：`arm-linux-gnueabihf-gcc`（Linaro 4.9.4）
- **目标平台**：NXP I.MX6ULL（eMMC 版本）

## 仓库工作流

1. 克隆或初始化后启用仓库内置的 Git 钩子（用于提交前提醒同步进度文档）：
   ```bash
   git config core.hooksPath scripts/git-hooks
   ```
   *(若某次微小提交确实无需更新日志，可使用 `SKIP_PROGRESS_CHECK=1 git commit ...` 跳过检查。)*
2. 查看当前进度与历史记录：
   - 任务清单：[`TASKS.md`](./TASKS.md)
   - 变更日志：[`CHANGELOG.md`](./CHANGELOG.md)

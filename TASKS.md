# 嵌入式原理期末大作业 — 任务清单 (TASKS)

> **工作区**：`~/linux/finalhomework/`（与平时实验严格隔离）
> **共享资料目录**：`/mnt/hgfs/linux_share/finalhomework/`（仅此目录及子目录可读写，上级目录及往期 `Lab*` 目录只读）
> **变更日志**：见 [`CHANGELOG.md`](./CHANGELOG.md)

状态说明：`[ ]` 待办 · `[-]` 进行中 · `[x]` 已完成 · `[!]` 阻塞/待确认

---

## 阶段 0：环境与工程初始化

- [x] 检查交叉编译工具链、基础命令与工作目录隔离
- [x] 创建独立大作业工作区 `~/linux/finalhomework/`
- [x] 安装开发辅助工具（`gh`、图像处理与 `psplash` 编译依赖、解压与代码索引工具等）
- [x] 建立任务清单（`TASKS.md`）与变更日志（`CHANGELOG.md`）跟踪机制
- [x] 配置 Antigravity 生命周期 Hook、工作区规则（`AGENTS.md`）与 Git `pre-commit` 钩子模板
- [x] 配置 Git 身份信息（`user.name` / `user.email`）并完成 `gh auth login` 登录 GitHub
- [x] 在 `~/linux/finalhomework/` 初始化 Git 仓库与 `.gitignore`，启用 `pre-commit` 钩子并关联 GitHub 远程仓库（已完成首次推送至 `origin/main`）

## 阶段 1：预热任务（来自 `期末大作业考核要求.md`）

- [x] **预热 1 — U-Boot 自定义命令**
  - [x] 准备独立的大作业 U-Boot 源码与编译脚本
  - [x] 修改 U-Boot 源码，实现自定义命令（`ciallo`、`myinfo`）并在开发板 U-Boot 命令行通过 `uuu` 纯内存启动验证执行
- [x] **预热 2 — 修改内核开机画面与进度条动画**
  - [x] 准备独立的大作业 Linux 内核源码（正点原子 v2.7）与编译配置
  - [x] 制作并替换自定义内核开机 Logo（`1024x600` 全屏 `deepseeks`）及 `fbmem.c`/`fbcon.c` 全屏显示验证
  - [x] 拉取、定制配色与图片（`deepseek_taffy` + 蓝白进度条）并交叉编译 `psplash`，通过 `uuu` 纯内存 `initramfs` 实机验证 0%→100% 动画效果
- [ ] **预热 3 — 制作专属 MfgTool 烧录工具**
  - [ ] 获取 MfgTool 基础包（若复用 `Lab2` 资源需先经确认）
  - [ ] 修改 U-Boot 与设备树 `.dtb` 文件名为包含个人信息的文件，并更新烧录脚本配置
  - [ ] 实机验证专属 MfgTool 烧录流程

## 阶段 2：期末大作业主体（待确定选题后细化）

- [ ] 明确最终大作业考核细则与选题方向
- [ ] 设计系统架构（驱动层 / Linux C 应用层 / Qt 加分界面）
- [ ] 分模块实现、板端联调与文档整理
- [ ] 整理代码与交付材料并推送至 GitHub

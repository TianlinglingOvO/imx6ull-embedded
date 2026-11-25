# 变更日志 (CHANGELOG)

本文件按时间倒序记录嵌入式原理期末大作业（`~/linux/finalhomework/`）的环境变更、源码改动、编译配置与验证结果。

---

## [2026-11-25] 初始化本地 Git 仓库并完成首次推送

### 新增与验证
- 新增嵌入式项目专用 `.gitignore`（忽略编译产物、固件镜像、大体积压缩包、上游源码目录 `upstream/`、Qt 临时文件及敏感凭证）。
- 新增项目说明文档 `README.md`。
- 在 `~/linux/finalhomework/` 初始化 Git 仓库（默认分支 `main`），启用 `core.hooksPath = scripts/git-hooks`，关联远程仓库 `https://github.com/TianlinglingOvO/imx6ull-embedded.git`。
- 完成首次推送并校验 `main...origin/main` 同步正常，阶段 0 准备工作全部完成。

---

## [2026-11-25] 完成 Git 与 GitHub CLI 认证配置

### 完成
- 配置全局 Git 身份信息（`user.name` / `user.email`）并完成 `gh auth login --insecure-storage` 登录账号 `TianlinglingOvO`（HTTPS 协议，`repo` / `workflow` 等权限就绪）。
- 执行 `gh auth setup-git`，确保后续 `git push` / `git pull` 自动走 `gh` 认证。

---

## [2026-11-25] 配置 Antigravity Hook 与工作区规则

### 新增
- 新增工作区规则 `/home/cjz/AGENTS.md`，固化期末大作业与平时实验的目录隔离红线、只读权限约束及 `TASKS.md` / `CHANGELOG.md` 同步维护规范。
- 新增全局 Antigravity 钩子配置 `~/.gemini/config/hooks.json` 及 3 个脚本（`~/.gemini/config/hooks/`）：
  - `session_start_brief.py`（`SessionStart`）：新开对话自动读取并注入 `TASKS.md` 待办进度与最新 `CHANGELOG.md` 记录。
  - `pre_tool_guard.py`（`PreToolUse`，匹配 `write_file|edit_file`）：对 `/mnt/hgfs/linux_share/`（`finalhomework/` 以外）、平时实验目录及 `/rootfs` 的写入操作强制弹出确认（`force_ask`）。
  - `stop_progress_check.py`（`Stop`）：智能检测 `~/linux/finalhomework/` 下的实质文件变动，仅在有文件变动且 `TASKS.md` 与 `CHANGELOG.md` 均未更新时提醒检查一次（支持 Git/非 Git 模式，内置 `continuationActive` 防循环）。
- 在 `~/linux/finalhomework/scripts/git-hooks/pre-commit` 预置 Git 提交前检查钩子模板（建库时通过 `git config core.hooksPath scripts/git-hooks` 即可启用）。

---

## [2026-11-25] 环境与工具初始化

### 新增
- 创建独立大作业工作目录 `~/linux/finalhomework/`，与平时实验目录（`uboot`、`kernel`、`busybox`、`tftp`、`/rootfs`）完全隔离。
- 安装 GitHub CLI `gh` `v2.105.0` 至 `/usr/local/bin/gh`。
- 在 `~/.local/bin` 建立便捷软链接：`fd` -> `fdfind`、`bat` -> `batcat`，并将 `~/.local/bin` 追加到 `~/.bashrc` 的 `PATH` 末尾（保持 Linaro 4.9.4 交叉编译器优先级不变）。
- 通过 `apt` 安装大作业所需的辅助工具与构建依赖：
  - 图像与开机画面工具：`netpbm`、`imagemagick`、`libgdk-pixbuf-2.0-dev`
  - 构建系统依赖：`autoconf`、`automake`、`libtool`
  - 代码与文件处理：`dos2unix`、`universal-ctags`、`p7zip-full`、`unar`、`picocom`
- 创建项目跟踪文件 `TASKS.md` 与 `CHANGELOG.md`。

### 检查记录
- 确认系统已预装：`git 2.43.0`、`rg`、`tree`、`jq`、`pdftotext`、`pdfinfo`、`dtc`、`mkimage`、`bison`、`flex`、`libncurses-dev`、`libssl-dev`、`bc`、`cpio`、`rsync`、`lzop`、`xxd`、`patch`、`arm-linux-gnueabihf-gcc (Linaro 4.9.4)`、`python3` + `Pillow`。
- 只读查阅 `/mnt/hgfs/linux_share/实验进度记录.md` 与 `/mnt/hgfs/linux_share/finalhomework/期末大作业考核要求.md`，未改动任何共享目录上级或往期实验文件。

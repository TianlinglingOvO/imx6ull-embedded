# 变更日志 (CHANGELOG)

本文件按时间倒序记录嵌入式原理期末大作业（`~/linux/finalhomework/`）的环境变更、源码改动、编译配置与验证结果。

---

## [2026-11-25] 完成预热 1：U-Boot 自定义命令（`ciallo` / `myinfo`）与实机验证

### 新增与修改
- 解压正点原子 U-Boot (`uboot-imx-rel_imx_4.1.15_2.1.0_ga_alientek_v2.4`) 至独立目录 `uboot/`（原始压缩包存放于 `pkg/`）。
- 新增自定义命令 `ciallo`（`uboot/cmd/ciallo.c`）：在 U-Boot 命令行输出 `Ciallo～(∠・ω < )⌒ ☆`，支持回车重复执行，并针对 SecureCRT 东亚模糊宽度字符排版调整间距。
- 新增自定义命令 `myinfo`（`uboot/cmd/myinfo.c`）：打印个人标识 `chenjunzhe-202410214103`，基于 U-Boot 原生 `cli_readline()` 实现交互式 `y/n` 确认、首尾空白裁剪、空输入与非法字符拦截及 `Ctrl+C` 中断退出。
- 在 `uboot/cmd/Makefile` 注册 `ciallo.o` 与 `myinfo.o`。
- 更新 `.gitignore`：忽略 `pkg/` 及 `uboot/` 大型上游源码树，仅精准跟踪 `uboot/cmd/ciallo.c`、`uboot/cmd/myinfo.c` 与 `uboot/cmd/Makefile`。
- 同步更新 `TASKS.md` 与 `README.md`（补充 U-Boot 编译与 `uuu` 纯内存调试说明）。

### 验证与交付
- 使用 `mx6ull_alientek_emmc_defconfig` 交叉编译生成 `uboot/u-boot.imx`（415 KB），`nm`/`strings` 校验 `_u_boot_list_2_cmd_2_ciallo`、`_u_boot_list_2_cmd_2_myinfo` 符号与字符串均正确链接。
- Ubuntu 宿主机安装 NXP 官方 `uuu` 工具，开发板拨码 `01000000`（USB 模式）执行 `sudo uuu SDP: boot -f uboot/u-boot.imx` 纯内存启动（零改写 eMMC），通过 SecureCRT（UTF-8 + 新宋体）实机验证 `help ciallo`、`ciallo`、`help myinfo`、`myinfo` 各分支全部通过。
- 已将最终编译产物拷贝至 Windows 共享目录 `/mnt/hgfs/linux_share/finalhomework/u-boot.imx`。

---

## [2026-11-25] 补充 README 同步检查机制

### 更新
- 在 `/home/cjz/AGENTS.md` 补充 `README.md` 同步维护规范（新增顶层模块/目录、完成阶段功能或调整编译/烧录方式时同步更新）。
- 升级 `~/.gemini/config/hooks/stop_progress_check.py`：在保留原有 `TASKS.md` / `CHANGELOG.md` 智能检测的基础上，新增“顶层模块目录新增”与“构建脚本变动”检测，仅在结构或构建方式变化且 `README.md` 未更新时触发轻量提醒。

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

# imx6ull-embedded

嵌入式原理课程期末大作业仓库（基于正点原子 I.MX6ULL 开发板，Linux 4.1.15 + Linaro GCC 4.9.4）。

> 本仓库用于版本化管理大作业过程中的自研代码、U-Boot/内核改动与补丁、设备树、开机画面资源、驱动与应用（含 Qt）、构建脚本以及进度文档。大型上游源码压缩包与编译产物已通过 [`.gitignore`](./.gitignore) 忽略。

## 目录规划

```text
.
├── README.md                 # 项目说明
├── TASKS.md                  # 阶段任务清单
├── CHANGELOG.md              # 按时间倒序的变更日志
├── .gitignore                # 构建产物、上游源码树与大文件忽略规则
├── assets/                   # 开机画面与进度条轻量 PNG 素材
│   ├── logo/                 # 内核全屏开机 Logo（1024x600）
│   └── psplash/              # psplash 主图（420x420）与蓝白进度条框（460x28）
├── pkg/                      # 原始源码压缩包（已忽略，不入库）
├── build/                    # 临时演示镜像等构建输出（已忽略，不入库）
├── uboot/                    # 正点原子 U-Boot 源码树（仅精准跟踪自研改动文件）
│   ├── Makefile              # EXTRAVERSION = -sutady
│   ├── include/configs/mx6ull_alientek_emmc.h  # 默认 fdt_file = imx6ull-sutady-emmc-7-1024x600.dtb
│   └── cmd/
│       ├── ciallo.c          # 自定义命令：ciallo
│       ├── myinfo.c          # 自定义交互命令：myinfo
│       └── Makefile          # 注册自定义命令编译目标
├── kernel/                   # 正点原子 Linux 4.1.15 v2.7 源码树（仅精准跟踪改动文件）
│   ├── Makefile              # 默认 ARCH=arm / CROSS_COMPILE=arm-linux-gnueabihf-
│   ├── drivers/video/console/fbcon.c      # 取消旧居中高度偏移以支持全屏 Logo
│   ├── drivers/video/fbdev/core/fbmem.c   # 恢复全屏 Logo 起始坐标 (0, y)
│   └── scripts/dtc/dtc-lexer.lex.c_shipped # GCC 13 兼容（extern yylloc）
├── psplash/                  # Yocto psplash 源码树（仅精准跟踪配色与构建改动）
│   ├── psplash-colors.h      # 纯白背景 + 蓝白进度条配色
│   └── configure.ac          # AC_CONFIG_HEADERS 兼容 Ubuntu 24.04 automake
├── mfgtool/                  # 专属 MfgTool（sutady）核心配置留档
│   ├── Mfgtool2-sutady-eMMC.vbs           # Windows 一键烧录入口（-l eMMC-sutady）
│   └── ucl2.xml              # 含 <LIST name="eMMC-sutady"> 一条龙烧录配置
└── scripts/
    ├── boot_ram.uuu          # uuu 纯内存加载 U-Boot + zImage + dtb 脚本
    └── git-hooks/
        └── pre-commit        # 提交前检查是否同步更新 TASKS.md / CHANGELOG.md
```

*(后续将按任务逐步新增 `drivers/`、`apps/` 等子目录。)*

## 开发与编译环境

- **宿主机**：Ubuntu 24.04 LTS (x86_64)
- **交叉编译器**：`arm-linux-gnueabihf-gcc`（Linaro 4.9.4）
- **目标平台**：NXP I.MX6ULL（正点原子 ALPHA eMMC 版本，7 寸 `1024x600` 屏）
- **无损调试工具**：NXP `uuu`（支持 USB OTG 纯内存加载 U-Boot / 内核 / `initramfs`，不覆写 eMMC）

## 编译与板端测试

### 1. U-Boot（自定义命令 `ciallo` / `myinfo`）

```bash
# 首次全量编译（生成 uboot/u-boot.imx）
cd ~/linux/finalhomework/uboot && ./mx6ull_alientek_emmc.sh

# 仅修改命令源码后的快速增量编译
cd ~/linux/finalhomework/uboot && make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j12

# USB OTG 纯内存启动验证（开发板拨码 01000000，USB_OTG 接入 Ubuntu，USB_TTL 接串口终端）
uuu SDP: boot -f ~/linux/finalhomework/uboot/u-boot.imx
```

### 2. Linux 内核（全屏 `1024x600` 开机 Logo）

```bash
# 1. 由 PNG 生成 224 色 ASCII PPM 并替换内核 Logo
pngtopnm ~/linux/finalhomework/assets/logo/deepseeks_1024x600.png \
  | pnmquant -fs 224 | pnmtoplainpnm \
  > ~/linux/finalhomework/kernel/drivers/video/logo/logo_linux_clut224.ppm

# 2. 配置并编译 zImage 与 7 寸电容屏设备树（已在 Makefile 配置好 ARCH/CROSS_COMPILE）
cd ~/linux/finalhomework/kernel
make imx_v7_defconfig
make zImage imx6ull-14x14-emmc-7-1024x600-c.dtb -j12

# 3. 通过 uuu 纯内存加载 U-Boot + zImage + dtb（不写 eMMC）
uuu ~/linux/finalhomework/scripts/boot_ram.uuu
# 在串口 U-Boot 命令行中执行（不 saveenv）：
#   setenv bootargs 'console=ttymxc0,115200 root=/dev/mmcblk1p2 rootwait rw'
#   bootz 80800000 - 83000000
```

### 3. `psplash`（开机进度条动画）

```bash
cd ~/linux/finalhomework/psplash
cp ../assets/psplash/deepseek_taffy_420x420.png base-images/psplash-poky.png
cp ../assets/psplash/psplash_bar_460x28.png base-images/psplash-bar.png
autoreconf -fi
./configure --host=arm-linux-gnueabihf CC=arm-linux-gnueabihf-gcc
make
```

### 4. 专属 MfgTool（`sutady` 一条龙烧录包）

- 完整 Windows 可执行烧录包位于共享目录 `/mnt/hgfs/linux_share/finalhomework/mfgtool-sutady/`（核心配置 `Mfgtool2-sutady-eMMC.vbs` 与 `ucl2.xml` 已留档在仓库 `mfgtool/` 目录）。
- 实机烧录方式：开发板拨码至 **USB 模式（`01000000`）**，将 `USB_OTG` 直接连接 Windows 主机，在 Windows 下双击 **`Mfgtool2-sutady-eMMC.vbs`** 点击 Start；烧录完成后断电拨回 **eMMC（`10100110`）** 上电启动。

## 仓库工作流

1. 克隆或初始化后启用仓库内置的 Git 钩子（用于提交前提醒同步进度文档）：
   ```bash
   git config core.hooksPath scripts/git-hooks
   ```
   *(若某次微小提交确实无需更新日志，可使用 `SKIP_PROGRESS_CHECK=1 git commit ...` 跳过检查。)*
2. 查看当前进度与历史记录：
   - 任务清单：[`TASKS.md`](./TASKS.md)
   - 变更日志：[`CHANGELOG.md`](./CHANGELOG.md)

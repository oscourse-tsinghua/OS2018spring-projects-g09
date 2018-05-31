# OS2018spring-projects-g09
http://os.cs.tsinghua.edu.cn/oscourse/OS2018spring/projects/g09

* riscv-pk fd2ddce557a9085ccdba1a455eded4808e7466c6

**实验平台为ubuntu 17.10**

# RISC-V 64 工具链搭建

先设置环境变量，推荐将以下代码写入文件vars.sh，之后每次启动shell直接指向source vars.sh就可以载入环境变量：

```sh
export RISCV=path/to/riscv_toolchain
export PATH=$RISCV/bin:$PATH
```

安装工具链（请最好准备10G空间，至少准备8G空间）：

```sh
sudo apt-get install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev libusb-1.0-0-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev device-tree-compiler pkg-config
git clone https://github.com/riscv/riscv-tools.git
cd riscv-tools
git submodule update --init --recursive
./build.sh # 最好确保gcc版本为7.2.0
cd ..
```

编译qemu：

```sh
sudo apt install libgtk-3-dev libsdl2-dev
cd riscv-tools/riscv-gnu-toolchain/riscv-qemu
./configure --target-list=riscv64-softmmu
make
cp riscv64-softmmu/qemu-system-riscv64 $RISCV/bin
```

以上，RISC-V包括代码编译/调试/运行的工具都生成了，有两种方式可以运行RISC-V程序：

方法一，使用spike+pk的方式：

```sh
echo -e '#include <stdio.h>\n int main(void) { printf("Hello world!\\n"); return 0; }' > hello.c
riscv64-unknown-elf-gcc -o hello hello.c
spike pk hello
```

方法二，用qemu加载RISC-V操作系统：

```sh
wget https://people.eecs.berkeley.edu/~skarandikar/host/qemu/1.9.1/bblvmlinuxinitramfs_dynamic
./riscv64-softmmu/qemu-system-riscv64 -kernel bblvmlinuxinitramfs_dynamic -nographic
```

# RISCVEMU安装

依赖：

```sh
sudo apt install openssl libcurl3 libsdl2-dev libssl-dev libcurl4-gnutls-dev
sudo apt-get install libsdl2-dev
```

下载源代码：

```sh
wget https://bellard.org/riscvemu/riscvemu-2017-08-06.tar.gz
tar -xf riscvemu-2017-08-06.tar.gz
cd riscvemu-2017-08-06
```

修改Makefile:

1. 将CONFIG_SDL=y注释掉

2. 将CFLAGS=-O2 -Wall -g -Werror -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -MMD中的-Werror去掉

编译运行:

```sh
make
[sudo make install]
./riscvemu https://bellard.org/jslinux/buildroot-riscv64.cfg
```

# 编译&运行

注：上面“RISCVEMU安装”不是必须的，但是由于编译运行需要一些依赖，所以最好将“RISCVEMU安装”一节中的内容完整执行一遍。

```sh
git clone https://github.com/oscourse-tsinghua/OS2018spring-projects-g09.git
cd OS2018spring-projects-g09
git submodule update --init --recursive
```

```sh
export RISCV=path/to/riscv_toolchain
export PATH=$RISCV/bin:$PATH
cd hv6
./run.sh
```

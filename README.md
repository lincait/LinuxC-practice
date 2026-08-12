# LinuxC编程代码

## 关于本仓库

本仓库是学习 C语言、数据结构和Linux C 编程过程中的所有练习代码。
所有程序均在 Ubuntu 环境下编译通过。

## 目录结构

- `01_C_basics/`        - C语言基础练习
    - `io_test.c`       - 输入输出
    - `ctrl_test.c`     - 流程控制
    - `array.c`         - 数组
    - `pointer.c`       - 指针
    - `function.c`      - 函数
    - `struct_sty.c`    - 构造类型
    - `memory.c`        - 动态内存管理
    - `Makefile`
- `02_Data_Structure`   - 数据结构练习
    - `Linked_List/`    - 链表（单链表、双向链表）
    - `Stack/`          - 栈（网站浏览记录）
    - `Queue/`          - 队列（医院排队叫号）
    - `Tree/`           - 二叉搜索树（图书信息管理）
- `03_File_IO`          - 文件I/O练习
    - `mycopy.c/h`      - 文件复制工具（支持偏移量复制）
    - `main.c`          - mycopy 主程序
- `04_Process_Handle`   - 进程处理练习
    - `process_hde.c/h` - 子进程创建、回收与状态管理
    - `main.c`          - 多进程管理演示
- `05_IPC`              - 进程间通信练习
    - `pipe_test.c`     - 无名管道（子进程转大写）
    - `msg_send.c`      - POSIX 消息队列（发送端）
    - `msg_recv.c`      - POSIX 消息队列（接收端）
    - `shm_test.c`      - 共享内存（父子进程统计文件）
    - `input.txt`       - 测试数据
    - `Makefile`

## 环境说明

- 操作系统：Ubuntu 22.04
- 编译器：GCC
- 编辑工具：VS Code + Remote-SSH
- 版本管理：Git + GitHub

## 相关仓库

- 笔记整理：[Embedded-notes](https://github.com/lincait/Embedded-notes)
- 代码练习：[LinuxC-practice](https://github.com/lincait/LinuxC-practice)
- 开发板学习：
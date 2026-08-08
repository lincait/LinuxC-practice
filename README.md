# LinuxC编程代码

## 关于本仓库

本仓库是学习 C语言、数据结构和Linux C 编程过程中的所有练习代码。
所有程序均在 Ubuntu 环境下编译通过。

## 目录结构

- `01_C_basics/`           - C语言基础练习
    - `io_test.c`          - 输入输出
    - `ctrl_test.c`        - 流程控制
    - `array.c`            - 数组
    - `pointer.c`          - 指针
    - `function.c`         - 函数
    - `struct_sty.c`       - 构造类型
    - `memory.c`           - 动态内存管理
    - `Makefile`
- `02_Data_Structure/`     - 数据结构练习
    - `Linked_List/`       - 链表
        - `SLlist.c/.h`    - 单链表
        - `DLlist.c/.h`    - 双链表
        - `llist_test.c`   - 链表测试
        - `Makefile`
    - `Stack/`             - 栈
        - `stack.c/.h`     - 栈实现
        - `stack_test.c`   - 栈测试
        - `libmystack.so`  - 动态库
        - `Makefile`
    - `Queue/`             - 队列
        - `queue.c/.h`     - 队列实现
        - `queue_test.c`   - 队列测试
        - `libmyqueue.a`   - 静态库
        - `Makefile`
    - `Tree/`              - 二叉树
        - `tree.c/.h`      - 二叉树实现
        - `tree_test.c`    - 二叉树测试
        - `Makefile`
- `03_File_IO/`            - 文件 I/O 练习
    - `mycopy.c/.h`        - 文件复制与统计
    - `main.c`             - 测试入口
    - `Makefile`
- `04_Process_Handle/`     - 进程管理练习
    - `process_hde.c/.h`   - 多进程创建与回收
    - `main.c`             - 测试入口
    - `Makefile`
- `05_IPC/`                - 进程间通信练习
    - `pipe_test.c`        - 匿名管道
    - `msg_send.c`         - POSIX 消息队列发送
    - `msg_recv.c`         - POSIX 消息队列接收
    - `shm_test.c`         - POSIX 共享内存
    - `input.txt`          - 测试文件
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
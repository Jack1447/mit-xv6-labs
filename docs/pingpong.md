# 实验：Ping-Pong 用户程序

## 🔍 实验目的

通过实现一个简单的父子进程通信程序，理解 xv6 中系统调用的使用，包括：

- 管道（pipe）
- 进程创建（fork）
- 读写（read/write）
- 获取进程 ID（getpid）
- 等待进程（wait）
- 程序退出（exit）

本实验帮助理解用户空间与内核空间的交互机制，以及父子进程之间如何通过管道进行同步和数据传输。

---

## 📁 程序文件位置

源代码位于：`user/pingpong.c`

---

## 📌 实验要求

> 编写一个用户级程序，该程序使用 xv6 系统调用在两个进程之间通过一对管道来回传递一个字节进行“ping-pong”操作。

### 具体要求：
- 父进程向子进程发送一个字节
- 子进程打印：`<pid>: received ping`，然后发送该字节回父进程
- 父进程读取该字节后打印：`<pid>: received pong`

---

## 🔨 实现说明

程序中使用了两个管道：
- `pipe1`：用于父进程向子进程发送数据
- `pipe2`：用于子进程向父进程发送数据

使用 `fork()` 创建子进程。

子进程流程：
- 从 `pipe1` 中读取父进程发送的字节
- 打印 "received ping"
- 将字节写入 `pipe2`，传回父进程
- 退出

父进程流程：
- 向 `pipe1` 写入一个字节（例如 'x'）
- 从 `pipe2` 中读取该字节
- 打印 "received pong"

---

## ✅ 程序输出样例

```bash
$ pingpong
4: received ping
3: received pong
```

---

## 🔗 编译与运行

1. 在 `Makefile` 中添加：

```
  _pingpong\
```

2. 编译并运行 xv6：

```bash
make qemu
```

3. 在 xv6 shell 中执行：

```bash
pingpong
```

---

## 🧠 实验收获

- 熟悉了 `pipe()` 与 `fork()` 的配合使用
- 了解了如何在用户态打印进程号（使用 `getpid()`）
- 掌握了如何实现简单的进程间同步通信
- 熟悉了 `xv6` 用户态程序的开发、编译与执行流程

---

## 📚 参考资料

- MIT xv6 官方仓库：[https://github.com/mit-pdos/xv6-riscv](https://github.com/mit-pdos/xv6-riscv)
- [xv6 中文文档](https://xv6.dgs.zone/)

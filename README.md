# 考试系统

> 一个基于 C++ 与 MySQL 的命令行考试系统，支持学生模拟考试、辅导员成绩管理、管理员题库维护。

![Linux](https://img.shields.io/badge/OS-Linux-green)
![C++17](https://img.shields.io/badge/C++-17-blue?logo=c%2b%2b)
![MySQL](https://img.shields.io/badge/Database-MySQL-orange?logo=mysql)
![MySQL Connector/C++](https://img.shields.io/badge/Driver-MySQL__Connector%2FC%2B%2B-red?logo=mysql)

---

## 📌 功能特性

- **多角色登录**：学生 / 辅导员 / 管理员
- **智能考试**：
  - 随机抽取 20 题（单选题 *10 + 多选题 *5 + 判断题 *5）
  - 45 分钟倒计时自动交卷
- **数据管理**：
  - 管理员可增删改查题库
  - 导出学生信息, 教师信息, 题库信息 为 CSV（Excel 可直接打开）
- **错题本**：自动记录答错题目供复习

---

## ⚙️ 环境要求

- **操作系统**：Linux (Ubuntu 20.04+ / CentOS 7+)
- **编译器**：GCC 9.0+ 或 Clang 10+
- **依赖库**：
  - `libmysqlcppconn-dev` （MySQL C++ 连接器）
  - `CMake` （构建工具）

---
## 🗂️ 项目结构

```text
exam_sys/
├── CMakeLists.txt  # 项目根 CMake 配置文件
├── bin/            # 编译生成的可执行文件
├── build/          # CMake 构建目录
├── data/           # 运行时生成的数据文件（如成绩 CSV）
├── include/        # C++ 头文件（接口声明）
├── sql/            # 数据库初始化脚本（表结构与示例数据）
└── src/            # C++ 源文件（功能实现）
```
---

## 🚀 快速开始

### 1. 安装依赖

#### ▶ Ubuntu / Debian（APT）
```bash
# 更新软件源并安装依赖
sudo apt update
sudo apt install -y build-essential cmake mysql-server libmysqlcppconn-dev
```
#### ▶ CentOS / RHEL / Rocky Linux（YUM/DNF）
```bash
# 启用 EPEL 仓库并安装依赖
sudo dnf install -y epel-release
sudo dnf install -y gcc-c++ cmake mariadb-server mariadb-connector-c++-devel

# 启动并启用 MariaDB 服务
sudo systemctl enable --now mariadb
```
### 2. 配置数据库用户

### 🔧 Bash 命令（启动服务）

#### ▶ Ubuntu / Debian（APT）
```bash
sudo systemctl start mysql
```
#### ▶ CentOS / RHEL / Rocky Linux（YUM/DNF）
```bash
# CentOS/RHEL（若未自动启动）
sudo systemctl start mariadb
```


### 3. 🔑 SQL 脚本(创建用户与数据库并导入数据)

```bash
# 导入数据库初始化脚本及示例数据(在exam_sys/sql/下)
mysql -u root -p < <(cat build.sql data.sql)
```

### 4. 编译并运行程序
#### 🔨 Bash 构建脚本

```bash
cd exam_sys/build/ && cmake .. && make
```
#### ▶ 运行程序
```bash
../bin/exma.out
```

### 5. 初始账号

| 角色   | 用户名         | 密码        |
|------- |-------------  |-------------|
| 管理员 | `admin`        | `123456`    |
| 辅导员 | `teacher1`     | `123456`    |
| 辅导员 | `teacher2`     | `123456`    |
| 学生   | `student001`   | `123456`    |
| 学生   | `student002`   | `123456`    |
| 学生   | `student003`   | `123456`    |
| 学生   | `student004`   | `123456`    |



-- 创建数据库（指定字符集避免中文乱码）
CREATE DATABASE IF NOT EXISTS exam_db 
  CHARACTER SET utf8mb4 
  COLLATE utf8mb4_unicode_ci;

-- 创建专用用户（仅限本地连接）
CREATE USER 'exam_user'@'localhost' IDENTIFIED BY '123456';

-- 授予 exam_db 全部权限
GRANT ALL PRIVILEGES ON exam_db.* TO 'exam_user'@'localhost';

-- 刷新权限生效
FLUSH PRIVILEGES;

USE exam_db;

-- 用户表
CREATE TABLE IF NOT EXISTS Users (
    Usrname VARCHAR(50) PRIMARY KEY COMMENT '用户名',
    Passwd VARCHAR(50) NOT NULL COMMENT '用户密码',
    Full_name VARCHAR(50)       COMMENT '姓名',
    Sex VARCHAR(10)             COMMENT '性别',
    Age  INT                    COMMENT '年龄',
    Id_card VARCHAR(20)         COMMENT '身份证号',
    Email VARCHAR(50)           COMMENT '邮箱',
    Phone VARCHAR(20)           COMMENT '手机号',
    Faculty VARCHAR(50)         COMMENT '学院',
    Class VARCHAR(50)           COMMENT '班级',
    Stu_num VARCHAR(20)         COMMENT '学号',
    Tutor VARCHAR(50)           COMMENT '辅导员',
    Job_num VARCHAR(20)         COMMENT '工号',
    Role VARCHAR(20)            COMMENT '角色'  -- "student" | "admin" | "teacher"
);

-- 试题表
CREATE TABLE IF NOT EXISTS Questions(
    Qid INT PRIMARY KEY AUTO_INCREMENT COMMENT '试题ID',
    Type VARCHAR(20) NOT NULL COMMENT '试题类型', -- "single" | "multiple" | "judge"
    Text TEXT NOT NULL COMMENT '试题内容',
    option1 TEXT NOT NULL COMMENT '选项1',
    option2 TEXT NOT NULL COMMENT '选项2',
    option3 TEXT          COMMENT '选项3',
    option4 TEXT          COMMENT '选项4',
    Ans INT NOT null      COMMENT '答案',
    Analysis TEXT         COMMENT '解析'
);


-- 学生错题表
CREATE TABLE IF NOT EXISTS stu_wq(
    Usrname VARCHAR(50) COMMENT '用户名',
    Qid INT COMMENT '试题ID',
    PRIMARY KEY (Usrname, Qid)
);

-- 学生答题记录表
CREATE TABLE IF NOT EXISTS stu_quiz(
    Usrname VARCHAR(50) COMMENT '用户名',
    Socre INT NOT NULL COMMENT '得分',
    solved INT NOT NULL COMMENT '已解决题目数',
    timecost TIME NOT NULL COMMENT '用时',
    Start_time DATETIME COMMENT '开始时间',
    PRIMARY KEY (Usrname, Start_time)
);
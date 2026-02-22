#pragma once

#include "headers.hpp"
#include "user.hpp"
#include "quiz.hpp"


#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

#include <unistd.h>//path
#include <cstring>

class Account;
class Question;
struct Quiz;

class DatabaseManager{
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;

    char cwd[1024];

    string safeStr(const string& col){
        string s = res->getString(col);
        return res->wasNull() ? "" : s;
    };

    string escape(const string& s){
        string t = "\"";
        for (char c : s) {
            if (c == '"') t += "\"\"";
            else t += c;
        }
        t += "\"";
        return t;
    };

public:
    DatabaseManager(){
        driver = sql::mysql::get_mysql_driver_instance();       // 1. 创建驱动实例

        con = driver->connect("tcp://127.0.0.1:3306/exam_db",   // 2. 连接数据库
            "exam_user", "123456");
        
        if(con != nullptr) cout << "✅初始化成功!";
        else{
            cout << "初始化失败, 程序将关闭\n任意键退出...";
            getch();
            exit(1);
        }
        stmt = con->createStatement();                          // 3. 创建语句对象

        getcwd(cwd, sizeof(cwd));

        initDb();
    }

    ~DatabaseManager(){
        delete driver;
        delete stmt;
        delete con;
    }
    
    void initDb(){   
        // 用户表
        stmt->execute( "CREATE TABLE IF NOT EXISTS Users (" 
            "Usrname VARCHAR(50) PRIMARY KEY COMMENT '用户名',"
            "Passwd VARCHAR(50) NOT null COMMENT '用户密码',"
            "Full_name VARCHAR(50)       COMMENT '姓名',"
            "Sex VARCHAR(10)             COMMENT '性别',"
            "Age  INT                    COMMENT '年龄',"
            "Id_card VARCHAR(20)         COMMENT '身份证号',"
            "Email VARCHAR(50)           COMMENT '邮箱',"
            "Phone VARCHAR(20)           COMMENT '手机号',"
            "Faculty VARCHAR(50)         COMMENT '学院',"
            "Class VARCHAR(50)           COMMENT '班级',"
            "Stu_num VARCHAR(20)         COMMENT '学号',"
            "Tutor VARCHAR(50)           COMMENT '辅导员',"
            "Job_num VARCHAR(20)         COMMENT '工号',"
            "Role VARCHAR(20)            COMMENT '角色')"
        ); 
        
        // 试题表
        stmt->execute( "CREATE TABLE IF NOT EXISTS Questions("
            "Qid INT PRIMARY KEY AUTO_INCREMENT COMMENT '试题ID',"
            "Type VARCHAR(20) NOT null COMMENT '试题类型',"
            "Text TEXT NOT null COMMENT '试题内容',"
            "option1 TEXT NOT null COMMENT '选项1',"
            "option2 TEXT NOT null COMMENT '选项2',"
            "option3 TEXT          COMMENT '选项3',"
            "option4 TEXT          COMMENT '选项4',"
            "Ans INT NOT null      COMMENT '答案',"
            "Analysis TEXT         COMMENT '解析')"
        );

        // 学生错题表
        stmt->execute( "CREATE TABLE IF NOT EXISTS stu_wq("
            "Usrname VARCHAR(50) COMMENT '用户名',"
            "Qid INT COMMENT '试题ID',"
            "PRIMARY KEY (Usrname, Qid));"
        );

        // 学生答题记录表
        stmt->execute( "CREATE TABLE IF NOT EXISTS stu_quiz("
            "Usrname VARCHAR(50) COMMENT '用户名',"
            "Socre INT NOT NULL COMMENT '得分',"
            "solved INT NOT NULL COMMENT '已解决题目数',"
            "timecost TIME NOT NULL COMMENT '用时',"
            "Start_time DATETIME COMMENT '开始时间',"
            "PRIMARY KEY (Usrname, Start_time));"
        );
    }



    // [查询]所有 学生/教师/题目 信息
    void query_qst_all();

    void query_tec_all();
    
    void query_stu_all();
    

    // 根据导师姓名[查询]学生信息
    void query_stu_from_tec(const string& name);

    void query_soc_from_tec(const string& name);

    // 根据用户名[查询]用户信息
    unique_ptr<Account > get_act(const string& uname);

    // 根据导师姓名[查询]是否存在对应导师
    bool verify_tec(const string& name);

    // 根据题号[查询]题目
    unique_ptr<Question > get_qst(const string& Qid);

    // [更新]/[写入]/[删除] 题目/用户信息
    void modify_act(const User& usr);
    void modify_admin(const Admin& adm);

    void insert_tec(const Teacher& usr);
    void insert_stu(const Student& usr);

    void del_act(const User& usr);

    void modify_qst(const Question& usr);

    void insert_qst(const Question& usr);

    void del_qst(const Question& usr);

    // 模拟考试随机抽题
    unique_ptr<vector<Question> > get_quiz();


    // [写入]学生 历史成绩, 错题表
    void insert_quiz_history(const Quiz& quiz, const string& uname);

    void insert_wa_history(const vector<int>& wq, const string& uname);

    // 根据学生用户名[查询] 历史成绩/错题表
    void query_quiz_history(const string& uname);
    
    void query_wa_history(const string& uname);

};


# pragma once

#include "headers.hpp"
#include "database.hpp"


class DatabaseManager;


class Account{
protected:
    string Usrname;
    string Password;
    virtual void Modify(int caller,DatabaseManager& db){return;}
public:
    friend class Admin;

    Account(){return;}
    Account(const string& uname, const string& pswd): Usrname(uname), Password(pswd) {}
    virtual void Menu(DatabaseManager& db){}
    bool authenticate(const string& pswd){return Password == pswd;}
};


class Admin : public Account{

    void act_modify(DatabaseManager& db);
    void qst_modify(DatabaseManager& db);
    void qst_insert(DatabaseManager& db);
    void Modify (int caller,DatabaseManager& db);
public:
    friend class DatabaseManager;
    Admin(const string& uname, const string& pswd): Account(uname, pswd){}
        string res;
    void Menu(DatabaseManager& db);
};

class User : public Account{
protected:
    string Full_name;       // 姓名
    int Age;
    string Sex;
    string Id_card;         // 身份证号
    string Phone;
    string Email;
    string Faculty;         // 学院
    string Class;

    User(){return;}
    User(const string& uname, const string& pswd, const string& fn, const string& sex,
        const string& id, const string& pho, const string& email, const string& fct, 
        const string&  cls, const int age): 
        Account(uname, pswd), Full_name(fn), Age(age), Sex(sex),
            Id_card(id), Phone(pho), Email(email), Faculty(fct), Class(cls){}
    
    void Modify(int caller, DatabaseManager& db);
public:
    friend class DatabaseManager;
    friend class Admin;
    
    virtual void Menu(DatabaseManager& db) {}
};


class Teacher : public User{
    string Job_num;         // 工号
public:
    friend class DatabaseManager;
    friend class Admin;

    Teacher(){return;}
    Teacher(const vector<string>& s1, const int age): User(s1[0], s1[1], s1[2], s1[3], 
            s1[4], s1[5], s1[6], s1[7], s1[8], age), Job_num(s1[9]){}
    
    void Menu(DatabaseManager& db);
};

class Student : public User{
    string Stu_num;         // 学号
    string Tutor;           // 导师
    vector<int> quiz(DatabaseManager& db);
public:
    friend class DatabaseManager;
    friend class Admin;

    Student() { return;}
    Student(const vector<string>& s1, const int age): User(s1[0], s1[1], s1[2], s1[3], 
        s1[4], s1[5], s1[6], s1[7], s1[8], age),  Stu_num(s1[9]), Tutor(s1[10]){}
    
    void Menu(DatabaseManager& db);
};


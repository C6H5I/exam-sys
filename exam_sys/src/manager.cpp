

#include "../include/database.hpp"
#include "../include/user.hpp"
#include "../include/manager.hpp"

void Manager::sign_in(){
    string res, r2;
    cout << "请输入用户名: ";
    cin >> res;     cin.ignore(Msize, '\n');
    
    unique_ptr<Account> act = db.get_act(res);  
    if(act == nullptr){
        cout << "用户名不存在! \n按下任意键继续..." << endl;
        getch();
        return;
    }
    r2 = getHiddenInput("请输入密码: ");
    
    while(!( act->authenticate(r2) )){
        cout << "密码错误, 请重试\n";
        r2 = getHiddenInput("请输入密码( q[Enter]以退出 ): ");
        if(r2 == "q") return;
    }
    act->Menu(db);
}

void Manager::sign_up(){
    string res, r2;
    vector<string> input;
    short age, type = 0;
    cout << "1. 学生\n2. 导师\n3. 退出\n";
    cout << "请选择注册的用户类型: ";
    cin >> res;     cin.ignore(Msize, '\n');
    if(res[0] == '3') return;
    while(res[0] < '1' || res[0] > '3'){
        cout << "非法输入! 请重试: ";
        cin >> res;     cin.ignore(Msize, '\n');
        if(res[0] == '3') return;
    }
    if(res[0] != '1') type = 1;

    cout << "请输入用户名: ";
    cin >> res;     cin.ignore(Msize, '\n');
    while(db.get_act(res) != nullptr){
        cout << "用户名已存在, 请重试: ";
        cin >> res;     cin.ignore(Msize, '\n');
    }
    input.push_back(res);

    res = getHiddenInput("输入新密码: ");
    r2 = getHiddenInput("确认新密码: ");
    while(res != r2){
        cout << "密码不一致! 请重试\n";
        res = getHiddenInput("输入新密码: ");
        r2 = getHiddenInput("确认新密码: ");
    }
    input.push_back(res);

    cout << "请输入姓名: ";
    cin >> res;     cin.ignore(Msize, '\n');
    input.push_back(res);
    cout << "请输入性别: ";
    cin >> res;     cin.ignore(Msize, '\n');
    input.push_back(res);
    cout << "请输入身份证号: ";
    cin >> res;     cin.ignore(Msize, '\n');
    input.push_back(res);
    cout << "请输入手机号: ";
    cin >> res;     cin.ignore(Msize, '\n');
    input.push_back(res);
    cout << "请输入电子邮箱地址: ";
    cin >> res;     cin.ignore(Msize, '\n');
    input.push_back(res);
    cout << "请输入学院: ";
    cin >> res;     cin.ignore(Msize, '\n');
    input.push_back(res);
    cout << "请输入班级: ";
    cin >> res;     cin.ignore(Msize, '\n');
    input.push_back(res);

    cout << "请输入年龄: ";
    cin >> age;     cin.ignore(Msize, '\n');

    if(type == 0){//stu
        cout << "请输入学号: ";
        cin >> res;     cin.ignore(Msize, '\n');
        input.push_back(res);

        cout << "请输入导员姓名: ";
        cin >> res;     cin.ignore(Msize, '\n');
        while(!db.verify_tec(res)){
            cout << "不存在该教师, 请重试: ";
            cin >> res;     cin.ignore(Msize, '\n');
        }

        input.push_back(res);

        // 写入数据库
        db.insert_stu((Student){input, age});
    }
    else{// tec
        cout << "请输入工号: ";
        cin >> res;     cin.ignore(Msize, '\n');
        input.push_back(res);
        
        // 写入数据库
        db.insert_tec((Teacher){input, age});
    }

    cout << "✅ 创建成功\n按下任意键继续..." << flush;
    getch();
}


void Manager::run(){
    string res, r2;
    while(1){
        cls();
        cout << "=====欢迎进入测试系统=====\n\n";
        cout << "1. 登录\n" << "2. 注册\n" << "3. 系统退出\n" ;
        cout << "请选择:";
        cin >> res;     cin.ignore(Msize, '\n');
        if(!isdigit(res[0]) || res[0] > '3' || res[0] == '0'){
            cls();
            cout << "非法输入! 请重试\n按下任意键继续...";
            getch();
            continue;
        }

        cls();
        switch(res[0] - '0'){
            case 1 : 
                sign_in();
                break;

            case 2: 
                sign_up();
                break;

            case 3: 
                return;
        }
    }

}


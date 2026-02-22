
#include "../include/database.hpp"
#include "../include/user.hpp"

#include <thread>


void Admin::act_modify(DatabaseManager& db){
    string res;
    while(1){
        cout << "输入用户名(q [Enter]以退出): ";
        cin >> res;     cin.ignore(Msize, '\n');
        if(res == "q") return;
        unique_ptr<Account> usr = db.get_act(res);  
        if(usr == nullptr){
            cout << "用户名不存在! \n按下任意键继续...";
            getch();
            continue;
        }
        usr->Modify(0, db);
    }
}

void Admin::qst_modify(DatabaseManager& db){
    string res;
    while(1){
        cout << "输入题目Qid(q [Enter]以退出): ";
        cin >> res;     cin.ignore(Msize, '\n');
        if(res == "q") return;
        unique_ptr<Question> qst = db.get_qst(res);  
        if(qst == nullptr){
            cout << "Qid不存在! \n按下任意键继续...";
            getch();
            continue;
        }
        qst->Modify(db);
    }
}

void Admin::qst_insert(DatabaseManager& db){
    string res, Type, txt, anls;
    vector<string> Options;
    int Ans = 0;
    cout << "=====新增题目=====\n1. 单选\n2. 多选\n3. 判断\n4. 退出\n";
    cin >> res;     cin.ignore(Msize, '\n');
    if(res[0] == '4') return;
    while(res[0] < '1' || res[0] > '4'){
        cout << "非法输入! 请重试: "<< endl;
        cin >> res;     cin.ignore(Msize, '\n');
        if(res[0] == '4') return;
    }
    switch(res[0] - '0'){
        case 1: Type = "single";    break;
        case 2: Type = "multiple";  break;
        case 3: Type = "judge";     break;
    }

    cout << "输入题目描述: ";
    cin >> txt;     cin.ignore(Msize, '\n');

    if(Type != "judge")
        for(int i = 0;i < 4;++i){
            cout << "输入选项" << char('A' + i) << ": ";
            cin >> res;     cin.ignore(Msize, '\n');
            Options.push_back(res);
        }
    else Options = {"对", "错"};

    cout << "输入题目解析: ";
    cin >> anls;     cin.ignore(Msize, '\n');

    cout << "\n请输入答案: ";
    cin >> res;     cin.ignore(Msize, '\n');
    while(1){
        bool good = 1;

        good &= res.size() <= 4;
        for(char c : res)
            good &= (toupper(c) >= 'A' && toupper(c) - 'A' < Options.size());
        if(!good){
            cout << "非法输入! 请重试: ";
            cin >> res;     cin.ignore(Msize, '\n');
            continue;
        }
        break;
    }

    if(Type != "multiple") Ans = 1 << (toupper(res[0]) - 'A');
    else{
        Ans = 0;
        for(char c : res) Ans |= 1 << (toupper(c) - 'A');
    }
    db.insert_qst((Question){0, Type, txt, Options, anls, Ans});

    cout << "✅ 创建成功\n按下任意键继续..." << flush;
    getch();
}

void Admin::Modify (int caller,DatabaseManager& db){
        string res, r2;
        res = getHiddenInput("输入新密码: ");
        r2 = getHiddenInput("确认新密码: ");
        while(res != r2){
            cout << "密码不一致! 请重试\n";
            res = getHiddenInput("输入新密码: ");
            r2 = getHiddenInput("确认新密码: ");
        }
        Password = res;
        db.modify_admin(*this);
    }

void Admin::Menu(DatabaseManager& db){
    string res;
    while(1){
        cls();
        cout <<  "Admin, 欢迎登录\n" << "=====管理主页=====\n\n";
        cout << "1. 学生信息查询\n2. 导师信息查询\n3. 用户信息修改\n4. 题目信息查询"
        "\n5. 题目信息修改\n6. 新增题目\n7. 修改密码\n8. 登出\n" << "请选择: ";
        cin >> res;     cin.ignore(Msize, '\n');
        if(res[0] < '1' || res[0] > '8'){
            cls();
            cout << "非法输入! 请重试\n按下任意键继续...";
            getch();
            continue;
        }

        cls();
        switch(res[0] - '0'){
            case 1: // 学生信息查询
                db.query_stu_all();
                break;

            case 2: // 导师信息查询
                db.query_tec_all();
                break;

            case 3: // 用户信息管理
                act_modify(db);
                break;

            case 4:
                db.query_qst_all();
                break;

            case 5: //题目修改
                qst_modify(db);
                break;

            case 6:// 新增题目
                qst_insert(db);
                break;

            case 7:
                Modify(0, db);
                break;

            case 8:
                return;
        }
    }
}


void User::Modify(int caller, DatabaseManager& db){// 0--Admin  1--Stu  2--Tutor
    User tmp = *this;
    string res, r2;
    while(1){
        cls();
        cout << "=====个人信息修改=====";
        cout << "\n   用户名\t: " << Usrname;
        cout << "\n   姓名\t: " << Full_name;
        cout << "\n   性别\t: " << Sex;
        cout << "\n   年龄\t:" << Age;
        cout << "\n   身份证号\t: " << Id_card;
        cout << "\n0. 修改密码";
        cout << "\n1. 电话号\t: " << Phone;
        cout << "\n2. 电子邮箱\t: " << Email;
        cout << "\n3; 学院\t: " << Faculty;
        cout << "\n4. 班级\t:" << Class;
        
        cout << "\n5. 不保存并退出\n6. 保存并退出";
        if(caller == 0) cout << "\n7. 删除用户信息";
        cout << "\n请选择: ";
        cin >> res;     cin.ignore(Msize, '\n');
        if(!isdigit(res[0]) || res[0] > '7' || (caller != 0 && res[0] == '7')){
            cls();
            cout << "非法输入! 请重试\n按下任意键继续...";
            getch();
            continue;
        }
        cls();
        switch(res[0] - '0'){
            case 0:
                if(caller != 0){
                    res = getHiddenInput("输入原密码( q[Enter]以退出 ):");
                    if(res == "q") continue;
                    while(res != Password){
                        cls();
                        cout << "密码错误! 请重试\n";
                        res = getHiddenInput("输入原密码( q[Enter]以退出):");
                        if(res == "q") continue;
                    }
                }

                cls();
                res = getHiddenInput("输入新密码: ");
                r2 = getHiddenInput("确认新密码: ");
                while(res != r2){
                    cout << "密码不一致! 请重试\n";
                    res = getHiddenInput("输入新密码: ");
                    r2 = getHiddenInput("确认新密码: ");
                }
                Password = res;
                break;


            case 1:
                cout << "输入新的电话号: ";
                cin >> res;     cin.ignore(Msize, '\n');
                Phone = res;
                break;

            case 2:
                cout << "输入新的电子邮箱: ";
                cin >> res;     cin.ignore(Msize, '\n');
                Email = res;
                break;

            case 3:
                cout << "输入新的学院: ";
                cin >> res;     cin.ignore(Msize, '\n');
                Faculty = res;
                break;

            case 4:
                cout << "输入新的班级: ";
                cin >> res;     cin.ignore(Msize, '\n');
                Class = res;
                break;

            case 5:
                *this = tmp;
                return;

            case 6://同步到数据库
                db.modify_act(*this);
                return;

            case 7:
                cout << "输入delete以确认删除";
                cin >> res;     cin.ignore(Msize, '\n');
                if(res != "delete") continue;

                db.del_act(*this);
                return;
        }
    }
}


void Teacher::Menu(DatabaseManager& db){
    string res;
    while(1){
        cls();
        cout << Full_name << ", 欢迎登录\n" << "====教师主页=====\n\n";
        cout << "1. 学生信息查询\n2. 学生成绩查询\n3. 信息修改\n" << "4. 登出\n" ;
        cout << "请选择:";
        cin >> res;     cin.ignore(Msize, '\n');
        if(res[0] < '1' || res[0] > '4'){
            cls();
            cout << "非法输入! 请重试\n按下任意键继续...";
            getch();
            continue;
        }

        cls();
        switch(res[0] - '0'){
            case 1 : //查询学生信息
                db.query_stu_from_tec(Full_name);
                break;

            case 2:
                db.query_soc_from_tec(Full_name);
                break;

            case 3: 
                Modify(2, db);
                break;

            case 4: 
                return;
        }
    }
}


vector<int> Student::quiz(DatabaseManager& db){
    auto quiz = db.get_quiz();
    vector<int> res(20, 0);
    
        KbHit kb;
        bool pm = 0;
        for(int i = 0, j = 0;i < 135000;++i){
            cls();
            int t = 2700 - (i/5);
            cout << "剩余时间: " << t / 60 << " : " << t % 60 << "\n\n";

            cout << "第" << j+1 << "题: " 
                << ((j < 10) ? "单选题" : (j < 15 ? "多选题" : "判断题"));
            (*quiz)[j].Display();

            cout << "\n当前题目的选择:\n";
            for(int k = 0;k < (*quiz)[j].size();++k){
                cout << char('A' + k) << (((res[j] >> k) & 1) ? ": ✅   " : ": O   ");
            }
            cout << '\n';
            
            cout << "\n答题卡:";
            for(int k = 0;k < 20;++k){
                if(k % 5 == 0) cout << "\n";
                
                if(k == j)  cout << k+1 << ": 🎯  ";
                else cout << k+1 << (res[k] == 0 ? ": O   " : ": ✅   ");
            }
            
            cout << "\n\na/b/c/d以写入/取消答案, n/m以切换题目: " << endl;

            if(pm) cout << "\n再次按下m以提交测验: " << endl;

            if(kb.kbhit()){
                // cout << "\nohhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh\n";
                char c = tolower(kb.getch());
                if(pm){
                    if(c == 'm') {
                        res.push_back(i/5);
                        break;
                    }
                    else pm = 0;
                }
                if(c >= 'a' && c <= 'd') {
                    if(j > 9 && j < 15)
                        res[j] ^= (1 << (c - 'a'));
                    else res[j] = (1 << (c - 'a'));

                }
                else if(c == 'n') j = max(0, j - 1);
                else if(c == 'm'){
                    if(j < 19) ++j;
                    else pm = 1;
                }
            }
            this_thread::sleep_for(chrono::milliseconds(200));

            if(i == 135000) res.push_back(i/5);
        }
    
    int socre = 0;
    vector<int> wa;
    for(int i = 0;i < 20;++i){
        int soc = (*quiz)[i].Checksoc(res[i]);
        socre += soc;
        if(soc == 0) wa.push_back((*quiz)[i].get_Qid());
    }
    res.push_back(socre); // 将耗时与得分压入res

    db.insert_wa_history(wa, Usrname); // 将错题题号存入数据库

    cls();
    return res;
}

void Student::Menu(DatabaseManager& db){

    string res;
    while(1){
        cls();
        cout << Full_name << ", 欢迎登录\n" << "====学生主页=====\n\n";
        cout << "1. 模拟考试\n" << "2. 查看历史成绩\n" << "3. 我的错题本\n";
        cout << "4. 信息修改\n" << "5. 登出\n" << "请选择: ";
        cin >> res;     cin.ignore(Msize, '\n');
        if(res[0] < '1' || res[0] > '5'){
            cls();
            cout << "非法输入! 请重试\n按下任意键继续...";
            getch();
            continue;
        }

        cls();
        switch(res[0] - '0'){
            case 1 : {// 进行模拟考试
                cout << "按下任意键以开始考试..." << endl;
                getch();
                vector<int> res = quiz(db);

                int socre = res.back();res.pop_back();
                int time_cost = res.back();res.pop_back();
                int responed = 0;
                for(int r : res) responed += (r > 0);

                // 将考试信息写入数据库
                db.insert_quiz_history({socre, time_cost, responed},Usrname);
                

                cout << "=====测验结束=====";
                cout << "\n本次测验耗时 " << time_cost / 60 << " : " << time_cost % 60;
                cout << "\n共解答 "<< responed << " / 20道题目";
                cout << "\n得分: " << socre;
                cout << "\n按下任意键退出..." << endl;
                getch();
                break;
            }
            case 2: // 查询并显示历史成绩
                db.query_quiz_history(Usrname);
            break;

            case 3: // 查询并显示错题本
                db.query_wa_history(Usrname);
            break;

            case 4:
                Modify(1, db);
            break;

            case 5:
                return;
        }
    }
}




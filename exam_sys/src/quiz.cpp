
#include "../include/database.hpp"
#include "../include/quiz.hpp"

void Question::Modify(DatabaseManager& db){
    Question tmp = *this; //保存备份
    int i;

    string res, option = "toabqwd";
    while(1){
        cls();
        cout << "=====题目修改=====\n";
        Display();
        cout << "\n题目解析:\n" << Analysis << "\n\n";
        cout << "当前题型为 " << Type;
        cout << "\n答案为: ";
        for(int i = 0;i < Options.size();++i)
            if((Ans >> i) & 1) cout << char('A' + i);

        cout << "\n\nt: 修改题目描述 \no: 修改选项 \na: 修改解析\nb: 修改答案\n"
            "q: 不保存并退出 \nw: 保存并退出\nd: 删除该题目\n";
        cout << "请选择: ";


        cin >> res;     cin.ignore(Msize, '\n');
        if(option.find(tolower(res[0])) >= option.size()){
            cls();
            cout << "非法输入! 请重试\n按下任意键继续...";
            getch();
            continue;
        }

        cls();
        switch(tolower(res[0])){
            case 't':
                Display();
                cout << "输入新的题目描述: ";
                cin >> res;     cin.ignore(Msize, '\n');
                Text = res;
                break;


            case 'o':
                Display();
                cout << "输入你要修改的选项[A";
                for(int i = 1;i < Options.size();++i)
                    cout << '|' << char('A' + i);
                cout << "]: ";

                cin >> res;     cin.ignore(Msize, '\n');
                res[0] = toupper(res[0]);
                while(res[0] < 'A' || res[0] >= ('A' + Options.size())){
                    cout << "非法输入! 请重试: ";
                    cin >> res;     cin.ignore(Msize, '\n');
                    res[0] = toupper(res[0]);
                }
                i = int(res[0] - 'A');
                cout << "输入该选项的新内容: ";
                cin >> res;     cin.ignore(Msize, '\n');
                Options[i] = res;
                break;


            case 'a':
                cout << "题目解析:\n" << Analysis << '\n';
                cout << "输入新的题目解析: ";
                cin >> res;     cin.ignore(Msize, '\n');
                Analysis = res;
                break;


            case 'b':
                Display();
                cout << "当前题型为 " << Type;// "single" | "multiple" | "judge"
                cout << "\n答案为: ";
                for(int i = 0;i < Options.size();++i)
                    if((Ans >> i) & 1) cout << char('A' + i);
                cout << "\n请输入新的答案: ";
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
                break;


            case 'q': 
                *this = tmp;
                return;


            case 'w'://同步到数据库
                db.modify_qst(*this);
                return;

            case 'd':
                cout << "输入delete以确认删除";
                cin >> res;     cin.ignore(Msize, '\n');
                if(res != "delete") continue;

                db.del_qst(*this);
                return;
        }
    }
}


#include "../include/database.hpp"

#include <iomanip> // setw
#include <fstream>
    

    // [查询]所有 学生/教师/题目 信息
    void DatabaseManager::query_qst_all(){
        res = stmt->executeQuery("SELECT * FROM Questions;");

        cout << left
             << setw(5)  << "Qid"
             << setw(10) << "类型"
             << setw(30) << "题干"
             << setw(20) << "A"
             << setw(20) << "B"
             << setw(20) << "C"
             << setw(20) << "D"
             << setw(10)  << "答案"
             << setw(30) << "解析" << endl;
        cout << string(150, '-') << endl;

        // 遍历结果集并打印每行
        while (res->next()) {

            int ans = res->getInt("Ans");
            string Ans;
            for(int i = 0;i < 4;++i)
                if((ans >> i) & 1) Ans.push_back('A' + i);

            cout << left
                 << setw(5)  << res->getInt("Qid")
                 << setw(10) << safeStr("Type")
                 << setw(30) << safeStr("Text")
                 << setw(20) << safeStr("option1").substr(0, 19)
                 << setw(20) << safeStr("option2").substr(0, 19) 
                 << setw(20) << safeStr("option3").substr(0, 19)
                 << setw(20) << safeStr("option4").substr(0, 19)
                 << setw(10)  << Ans
                 << setw(30) << safeStr("Analysis").substr(0, 29)
                 << endl;
        }
        cout << "\n按下w导出至 exa_sys/data/, q退出..." << endl;
        int c = tolower(getch());
        while(c != 'q'){
            if(c == 'w') {
                string path = (string)cwd + "/../data/all_qst.csv";
                ofstream fout(path.c_str());

                fout << "\"Qid\",\"类型\",\"题干\",\"A\",\"B\","
                    "\"C\",\"D\",\"答案\",\"解析\"\n";
                
                res = stmt->executeQuery("SELECT * FROM Questions;");
                while(res->next()){

                    int ans = res->getInt("Ans");
                    string Ans;
                    for(int i = 0;i < 4;++i)
                        if((ans >> i) & 1) Ans.push_back('A' + i);
                                                                                                      
                    fout << escape(to_string(res->getInt("Qid"))) << ","
                        << escape(safeStr("Type")) << ","
                        << escape(safeStr("Text")) << ","
                        << escape(safeStr("option1")) << ","
                        << escape(safeStr("option2")) << ","
                        << escape(safeStr("option3")) << ","
                        << escape(safeStr("option4")) << ","
                        << escape(Ans) << ","
                        << escape(safeStr("Analysis")) << "\n";
                }
                fout.close();
                cout << "✅ 已导出 " << endl;
            }
            c = tolower(getch());
        }
        delete res;
    }

    void DatabaseManager::query_tec_all(){ 
        res = stmt->executeQuery("SELECT * FROM Users WHERE Role = 'teacher';");
        
        cout << left
            << setw(12) << "用户名"
            << setw(12) << "姓名"
            << setw(8)  << "性别"
            << setw(6)  << "年龄"
            << setw(16) << "身份证号"
            << setw(20) << "邮箱"
            << setw(14) << "手机号"
            << setw(12) << "学院"
            << setw(12) << "班级"
            << setw(12) << "工号"<< endl;
        cout << string(130, '-') << endl;
        while(res->next()){
            cout << left
                << setw(12) << safeStr("Usrname")
                << setw(12) << safeStr("Full_name")
                << setw(8)  << safeStr("Sex")
                << setw(6)  << res->getInt("Age")
                << setw(16) << safeStr("Id_card")
                << setw(20) << safeStr("Email")
                << setw(14) << safeStr("Phone")
                << setw(12) << safeStr("Faculty")
                << setw(12) << safeStr("Class")
                << setw(12) << safeStr("Job_num")
                << endl;
        }


        cout << "\n按下w导出至 exa_sys/data/, q退出..." << endl;
        int c = tolower(getch());
        while(c != 'q'){
            if(c == 'w') {
                string path = (string)cwd + "/../data/all_tec.csv";
                ofstream fout(path.c_str());

                fout << "\"用户名\",\"姓名\",\"性别\",\"年龄\",\"身份证号\",\"邮箱\",\"手机号\""
                    ",\"学院\",\"班级\",\"工号\"\n";
                
                res = stmt->executeQuery("SELECT * FROM Users WHERE Role = 'teacher';");
                while(res->next()){
                    fout << escape(safeStr("Usrname")) << ","
                        << escape(safeStr("Full_name")) << ","
                        << escape(safeStr("Sex")) << ","
                        << escape(to_string(res->getInt("Age"))) << ","
                        << escape(safeStr("Id_card")) << ","
                        << escape(safeStr("Email")) << ","
                        << escape(safeStr("Phone")) << ","
                        << escape(safeStr("Faculty")) << ","
                        << escape(safeStr("Class")) << ","
                        << escape(safeStr("Job_num")) << "\n";
                }
                fout.close();
                cout << "✅ 已导出 " << endl;
            }
            c = tolower(getch());
        }
        delete res;
    }
    
    void DatabaseManager::query_stu_all(){
        res = stmt->executeQuery("SELECT * FROM Users WHERE Role = 'student';");
        
        cout << left
         << setw(12) << "用户名"
         << setw(12) << "姓名"
         << setw(8)  << "性别"
         << setw(6)  << "年龄"
         << setw(16) << "身份证号"
         << setw(20) << "邮箱"
         << setw(14) << "手机号"
         << setw(12) << "学院"
         << setw(12) << "班级"
         << setw(12) << "学号"
         << setw(12) << "辅导员"<< endl;
        cout << string(124, '-') << endl;

        while (res->next()) {
        cout << left
            << setw(12) << safeStr("Usrname")
            << setw(12) << safeStr("Full_name")
            << setw(8)  << safeStr("Sex")
            << setw(6)  << safeStr("Age")
            << setw(16) << safeStr("Id_card")
            << setw(20) << safeStr("Email")
            << setw(14) << safeStr("Phone")
            << setw(12) << safeStr("Faculty")
            << setw(12) << safeStr("Class")
            << setw(12) << safeStr("Stu_num")
            << setw(12) << safeStr("Tutor") << endl;
        }

        cout << "\n按下w导出至 exa_sys/data/, q退出..." << endl;
        int c = tolower(getch());
        while(c != 'q'){
            if(c == 'w') {
                string path = (string)cwd + "/../data/all_stu.csv";
                ofstream fout(path.c_str());

                fout << "\"用户名\",\"姓名\",\"性别\",\"年龄\",\"身份证号\",\"邮箱\",\"手机号\""
                    ",\"学院\",\"班级\",\"学号\",\"辅导员\"\n";
                
                res = stmt->executeQuery("SELECT * FROM Users WHERE Role = 'student';");
                while(res->next()){
                    fout << escape(safeStr("Usrname")) << ","
                        << escape(safeStr("Full_name")) << ","
                        << escape(safeStr("Sex")) << ","
                        << escape(safeStr("Age")) << ","
                        << escape(safeStr("Id_card")) << ","
                        << escape(safeStr("Email")) << ","
                        << escape(safeStr("Phone")) << ","
                        << escape(safeStr("Faculty")) << ","
                        << escape(safeStr("Class")) << ","
                        << escape(safeStr("Stu_num")) << ","
                        << escape(safeStr("Tutor")) << "\n";
                }
                fout.close();
                cout << "✅ 已导出 " << endl;
            }
            c = tolower(getch());
        }
        delete res;
    }
    

    // 根据导师姓名[查询]学生信息
    void DatabaseManager::query_stu_from_tec(const string& name){
        res = stmt->executeQuery("SELECT * FROM Users WHERE Role = 'student' AND"
            " Tutor = '"+name+"';");
        cout << left
         << setw(12) << "用户名"
         << setw(12) << "姓名"
         << setw(8)  << "性别"
         << setw(6)  << "年龄"
         << setw(16) << "身份证号"
         << setw(20) << "邮箱"
         << setw(14) << "手机号"
         << setw(12) << "学院"
         << setw(12) << "班级"
         << setw(12) << "学号"
         << setw(12) << "辅导员"<< endl;
        cout << string(124, '-') << endl;

        while (res->next()) {
        cout << left
            << setw(12) << safeStr("Usrname")
            << setw(12) << safeStr("Full_name")
            << setw(8)  << safeStr("Sex")
            << setw(6)  << safeStr("Age")
            << setw(16) << safeStr("Id_card")
            << setw(20) << safeStr("Email")
            << setw(14) << safeStr("Phone")
            << setw(12) << safeStr("Faculty")
            << setw(12) << safeStr("Class")
            << setw(12) << safeStr("Stu_num")
            << setw(12) << safeStr("Tutor") << endl;
        }
        
        cout << "\n按下w导出至 exa_sys/data/, q退出..." << endl;
        int c = tolower(getch());
        while(c != 'q'){
            if(c == 'w') {
                string path = (string)cwd + "/../data/all_stu.csv";
                ofstream fout(path.c_str());

                fout << "\"用户名\",\"姓名\",\"性别\",\"年龄\",\"身份证号\",\"邮箱\",\"手机号\""
                    ",\"学院\",\"班级\",\"学号\",\"辅导员\"\n";
                
                res = stmt->executeQuery("SELECT * FROM Users WHERE Role = 'student';");
                while(res->next()){
                    fout << escape(safeStr("Usrname")) << ","
                        << escape(safeStr("Full_name")) << ","
                        << escape(safeStr("Sex")) << ","
                        << escape(safeStr("Age")) << ","
                        << escape(safeStr("Id_card")) << ","
                        << escape(safeStr("Email")) << ","
                        << escape(safeStr("Phone")) << ","
                        << escape(safeStr("Faculty")) << ","
                        << escape(safeStr("Class")) << ","
                        << escape(safeStr("Stu_num")) << ","
                        << escape(safeStr("Tutor")) << "\n";
                }
                fout.close();
                cout << "✅ 已导出 " << endl;
            }
            c = tolower(getch());
        }
        delete res;
    }

    void DatabaseManager::query_soc_from_tec(const string& name){
        res = stmt->executeQuery("SELECT * FROM (SELECT * FROM Users WHERE "
            "Tutor = '"+name+"') stu JOIN stu_quiz q ON stu.Usrname = q.Usrname;");

        cout << left
            << setw(12) << "学生姓名"
            << setw(8)  << "得分"
            << setw(10) << "已解决"
            << setw(10) << "用时"
            << setw(20) << "结束时间" << endl;
        cout << string(50, '-') << endl;

        while(res->next()){     
            cout << left
            << setw(12) << safeStr("Full_name")
            << setw(8)  << safeStr("Socre")
            << setw(10) << safeStr("solved")
            << setw(10) << safeStr("timecost")
            << setw(20) << safeStr("Start_time") << endl;
        }
        cout << "\n按下w导出至 exa_sys/data/, q退出..." << endl;
        int c = tolower(getch());
        while(c != 'q'){
            if(c == 'w') {
                string path = (string)cwd + "/../data/stu_soc_from_"+name+".csv";
                ofstream fout(path.c_str());

                fout << "\"学生姓名\",\"得分\",\"已解决\",\"用时\",\"结束时间\"\n";
                
                res = stmt->executeQuery("SELECT * FROM (SELECT * FROM Users WHERE "
                    "Tutor = '"+name+"') stu JOIN stu_quiz q ON stu.Usrname = q.Usrname;");
                while(res->next()){
                    fout << escape(safeStr("Full_name")) << ","
                        << escape(safeStr("Socre")) << ","
                        << escape(safeStr("solved")) << ","
                        << escape(safeStr("timecost")) << ","
                        << escape(safeStr("Start_time")) << "\n";
                }
                fout.close();
                cout << "✅ 已导出 " << endl;
            }
            c = tolower(getch());
        }
        delete res;
    }

    // 根据用户名[查询]用户信息
    unique_ptr<Account> DatabaseManager::get_act(const string& uname){
        res = stmt->executeQuery("SELECT * FROM Users WHERE Usrname = '"+uname+"'");
        if (!res || !res->next()) {
            delete res;
            return nullptr; // 用户不存在
        }

        string pswd = safeStr("Passwd");
        string fullname = safeStr("Full_name");
        string sex = safeStr("Sex");
        short age = res->wasNull() ? 0 : static_cast<short>(res->getInt("Age"));
        string idcard = safeStr("Id_card");
        string phone = safeStr("Phone");
        string email = safeStr("Email");
        string faculty = safeStr("Faculty");
        string cls = safeStr("Class");       
        string stu_num = safeStr("Stu_num");
        string Tutor = safeStr("Tutor");
        string job_num = safeStr("Job_num");
        string role = safeStr("Role");

        delete res;
        // 根据 Role 创建对应对象
        if(role == "admin"){
            return make_unique<Admin>(uname, pswd);
        }else if (role == "teacher") {
            // 构造 Teacher
            vector<string> s1 = {uname, pswd, fullname, sex, idcard, phone, email, faculty, cls, job_num};
            return make_unique<Teacher>(s1, age);
        } else if (role == "student") {
            // 构造 Student
            vector<string> s1 = {uname, pswd, fullname, sex, idcard, phone, email, faculty, cls, stu_num, Tutor};
            return make_unique<Student>(s1, age);
        }
        else return nullptr;
    }

    // 根据导师姓名[查询]是否存在对应导师
    bool DatabaseManager::verify_tec(const string& name){
        res = stmt->executeQuery(
            "SELECT * FROM Users WHERE Role = 'teacher' AND Full_name = '"+
            name+"';");
        if(!res || !res->next()){
            delete res;
            return 0;
        }
        delete res;
        return 1;
    }

    // 根据Qid[查询]题目
    unique_ptr<Question> DatabaseManager::get_qst(const string& Qid){
        res = stmt->executeQuery("SELECT * FROM Questions WHERE Qid = "+Qid+";");
        if (!res || !res->next()) {
            delete res;
            return nullptr; // 题目不存在
        }
        vector<string> options;
        for(int i = 1;i <= 4;++i){
            string res = safeStr("option"+to_string(i));
            if(res != "") options.emplace_back(res);
        }

        auto r1 = make_unique<Question>(res->getInt("Qid"), safeStr("Type"), 
        safeStr("Text"), options, safeStr("Analysis"), res->getInt("Ans"));

        delete res;
        return r1;
    }

    // [更新]/[写入]/[删除] 题目/用户信息
    void DatabaseManager::modify_act(const User& usr){
        stmt->execute("UPDATE Users SET Passwd = '"+usr.Password+"', Phone = '"
            +usr.Phone+"', Email = '"+usr.Email+"', Faculty = '"+usr.Faculty+
            "', Class = '"+usr.Class+"' WHERE Usrname='"+usr.Usrname+"';");
    }
    void DatabaseManager::modify_admin(const Admin& adm){
        stmt->execute("UPDATE Users SET Passwd = '"+adm.Password+"' "
            "WHERE Usrname='"+adm.Usrname+"';");
    }

    void DatabaseManager::insert_tec(const Teacher& usr){
        stmt->execute("INSERT INTO Users (Usrname, Passwd, Full_name, Sex, "
            "Age, Id_card, Email, Phone, Faculty, Class, Job_num, Role) "
            "VALUES('"+usr.Usrname+"', '"+usr.Password+"', '"+usr.Full_name+"', '"+
            usr.Sex+"', "+to_string(usr.Age)+", '"+usr.Id_card+"', '"+usr.Email+"', '"+
            usr.Phone+"', '"+usr.Faculty+"', '"+usr.Class+"', '"+usr.Job_num+
            "', 'teacher');");
    }
    void DatabaseManager::insert_stu(const Student& usr){
        stmt->execute("INSERT INTO Users (Usrname, Passwd, Full_name, Sex, "
            "Age, Id_card, Email, Phone, Faculty, Class, Stu_num, Tutor, Role) "
            "VALUES('"+usr.Usrname+"', '"+usr.Password+"', '"+usr.Full_name+"', '"+
            usr.Sex+"', "+to_string(usr.Age)+", '"+usr.Id_card+"', '"+usr.Email+"', '"+
            usr.Phone+"', '"+usr.Faculty+"', '"+usr.Class+"', '"+usr.Stu_num+"', '"+
            usr.Tutor+"', 'student');");
    }

    void DatabaseManager::del_act(const User& usr){
        stmt->execute("DELETE FROM Users WHERE Usrname='"+usr.Usrname+"';");
        stmt->execute("DROP TABLE IF EXISTS "+usr.Usrname+"_WQ;");
        stmt->execute("DROP TABLE IF EXISTS "+usr.Usrname+"_quiz;");
    }

    void DatabaseManager::modify_qst(const Question& usr){
        stmt->execute("UPDATE Questions SET Type='"+usr.Type+"', Text='"+usr.Text
            +"', option1='"+usr.Options[0]+"', option2='"+usr.Options[1]+"', Ans="+
            to_string(usr.Ans)+", Analysis='"+usr.Analysis+"' WHERE Qid = "+
            to_string(usr.Qid)+";");
        if(usr.Type != "judge"){
            stmt->execute("UPDATE Questions SET option3 = '"+usr.Options[2]+"', "
                "option4 = '"+usr.Options[3]+"' WHERE Qid = "+to_string(usr.Qid)+
                ";" );
        }
    }

    void DatabaseManager::insert_qst(const Question& usr){
        stmt->execute("INSERT INTO Questions(Type, Text, option1, option2, Ans, "
            "Analysis) VALUES('"+usr.Type+"', '"+usr.Text+"', '"+usr.Options[0]+
            "', '"+usr.Options[1]+"', "+to_string(usr.Ans)+", '"+usr.Analysis+
            "');");

        if(usr.Type != "judge"){
            stmt->execute("UPDATE Questions SET option3 = '"+usr.Options[2]+"', "
                "option4 = '"+usr.Options[3]+"' WHERE Text = "+usr.Text+
                ";" );
        }
    }

    void DatabaseManager::del_qst(const Question& usr){
        stmt->execute("DELETE FROM Qustions WHERE Qid="+to_string(usr.Qid)
            +";");
    }


    // 模拟考试随机抽题
    unique_ptr<vector<Question> > DatabaseManager::get_quiz(){
        res = stmt->executeQuery(
            "(   SELECT * FROM Questions "
                "WHERE Type = 'single' "
                "ORDER BY RAND() "
                "LIMIT 10)"
            "UNION ALL"
            "(   SELECT * FROM Questions "
                "WHERE Type = 'multiple' "
                "ORDER BY RAND() "
                "LIMIT 5)"
            "UNION ALL"
            "(   SELECT * FROM Questions "
                "WHERE Type = 'judge' "
                "ORDER BY RAND() "
                "LIMIT 5);"
        );
        auto quiz = make_unique<vector<Question> >();
        while(res->next()){
            vector<string> Options;
            for(int i = 1;i <= 4;++i){
                string res = safeStr("option"+to_string(i));
                if(res != "") Options.emplace_back(res);
            }

            quiz->emplace_back((Question){res->getInt("Qid"), safeStr("Type"), safeStr("Text"), 
                Options, safeStr("Analysis"), res->getInt("Ans")});
        }

        delete res;
        return quiz;
    }

    // [写入]学生 历史成绩, 错题表
    void DatabaseManager::insert_quiz_history(const Quiz& quiz, const string& uname){
        stmt->execute("INSERT INTO stu_quiz(Usrname, Socre,solved,timecost,Start_time) "
            "VALUES('"+uname+"',"+to_string(quiz.Socre)+", "+to_string(quiz.Solved)
            +", SEC_TO_TIME("+to_string(quiz.Time_cost)+"), NOW());");
    }

    void DatabaseManager::insert_wa_history(const vector<int>& wq, const string& uname){
        for(int q : wq)
            stmt->execute("INSERT IGNORE INTO stu_wq(Usrname, Qid) VALUES ('"
                +uname+"',"+to_string(q)+");");
    }

    // 根据学生用户名[查询] 历史成绩/错题表
    void DatabaseManager::query_quiz_history(const string& uname){
        res = stmt->executeQuery("SELECT * FROM stu_quiz WHERE Usrname = '"+uname+"';");

        cout << left
            << setw(8)  << "得分"
            << setw(10) << "已解决"
            << setw(10) << "用时"
            << setw(20) << "结束时间" << endl;
        cout << string(50, '-') << endl;

        while(res->next()){     
            cout << left
            << setw(8)  << safeStr("Socre")
            << setw(10) << safeStr("solved")
            << setw(10) << safeStr("timecost")
            << setw(20) << safeStr("Start_time") << endl;
        }
        cout << "\n按下w导出至 exa_sys/data/, q退出..." << endl;
        int c = tolower(getch());
        while(c != 'q'){
            if(c == 'w') {
                string path = (string)cwd + "/../data/"+uname+"_quiz_history.csv";
                ofstream fout(path.c_str());

                fout << "\"得分\",\"已解决\",\"用时\",\"结束时间\"\n";
                
                res = stmt->executeQuery("SELECT * FROM stu_quiz WHERE Usrname = '"+uname+"';");
                while(res->next()){
                    fout << escape(safeStr("Socre")) << ","
                        << escape(safeStr("solved")) << ","
                        << escape(safeStr("timecost")) << ","
                        << escape(safeStr("Start_time")) << "\n";
                }
                fout.close();
                cout << "✅ 已导出 " << endl;
            }
            c = tolower(getch());
        }
        delete res;
    }
    
    void DatabaseManager::query_wa_history(const string& uname){
        res = stmt->executeQuery("SELECT * FROM (SELECT * FROM stu_wq WHERE "
            "Usrname = '"+uname+"') n JOIN Questions q ON n.Qid = q.Qid;");
        
        cout << left
             << setw(5)  << "Qid"
             << setw(10) << "类型"
             << setw(40) << "题干"
             << setw(20) << "A"
             << setw(20) << "B"
             << setw(20) << "C"
             << setw(20) << "D"
             << setw(10)  << "答案"
             << setw(30) << "解析" << endl;
        cout << string(150, '-') << endl;

        // 遍历结果集并打印每行
        while (res->next()) {
            int ans = res->getInt("Ans");
            string Ans;
            for(int i = 0;i < 4;++i)
                if((ans >> i) & 1) Ans.push_back('A' + i);
            cout << left
                 << setw(5)  << res->getInt("Qid")
                 << setw(10) << safeStr("Type")
                 << setw(40) << safeStr("Text")
                 << setw(20) << safeStr("option1").substr(0, 19)
                 << setw(20) << safeStr("option2").substr(0, 19) 
                 << setw(20) << safeStr("option3").substr(0, 19)
                 << setw(20) << safeStr("option4").substr(0, 19)
                 << setw(10)  << Ans
                 << setw(30) << safeStr("Analysis").substr(0, 29)
                 << endl;
        }
        cout << "\n按下w导出至 exa_sys/data/, q退出..." << endl;
        int c = tolower(getch());
        while(c != 'q'){
            if(c == 'w') {
                string path = (string)cwd + "/../data/"+uname+"_wa_history.csv";
                ofstream fout(path.c_str());

                fout << "\"Qid\",\"类型\",\"题干\",\"A\",\"B\","
                    "\"C\",\"D\",\"答案\",\"解析\"\n";
                
                res = stmt->executeQuery("SELECT * FROM (SELECT * FROM stu_wq WHERE "
                    "Usrname = '"+uname+"') n JOIN Questions q ON n.Qid = q.Qid;");
                while(res->next()){

                    int ans = res->getInt("Ans");
                    string Ans;
                    for(int i = 0;i < 4;++i)
                        if((ans >> i) & 1) Ans.push_back('A' + i);
                                                                                                      
                    fout << escape(to_string(res->getInt("Qid"))) << ","
                        << escape(safeStr("Type")) << ","
                        << escape(safeStr("Text")) << ","
                        << escape(safeStr("option1")) << ","
                        << escape(safeStr("option2")) << ","
                        << escape(safeStr("option3")) << ","
                        << escape(safeStr("option4")) << ","
                        << escape(Ans) << ","
                        << escape(safeStr("Analysis")) << "\n";
                }
                fout.close();
                cout << "✅ 已导出 " << endl;
            }
            c = tolower(getch());
        }
        delete res;
    }


#pragma once

#include "headers.hpp"
#include "database.hpp"

class DatabaseManager;

class Question{
    int Qid;
    string Type;    // "single" | "multiple" | "judge"
    string Text;
    vector<string> Options;
    string Analysis;
    int Ans;
public:
    friend class DatabaseManager;
    Question(const int id,const string& tp, const string& txt, 
        const vector<string> options, const string anls, const int ans): 
        Text(txt), Options(options), Ans(ans), Qid(id), Type(tp), 
        Analysis(anls) {}

    void Display(){
        cout << "\n[P" << Qid << "] :" << Text << '\n';
        for(int i = 0;i < Options.size(); ++i){
            cout << char('A' + i) << ". " << Options[i] << '\n';
        }
    }

    int size(){return Options.size();}

    void Modify(DatabaseManager& db);

    int Checksoc(int res){
        if(res == Ans) return 5;
        if(res > 0 && (res & Ans == res)) return 2;
        return 0;
    }

    int get_Qid(){ return Qid;}

};

struct Quiz{
    int Socre;
    int Time_cost;
    int Solved;
};


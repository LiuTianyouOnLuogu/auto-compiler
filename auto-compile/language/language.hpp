#pragma once

#include <string>
#include <vector>

#define NULLSTR "null"
#define NULLNUM -1

class objfile{
    public:
        std::string name;
        std::string language;
        virtual void make();
};
/*
这是语言类的基类，开发者可以通过基类设计语言的处理方式和内容。
语言类一致大写。
*/

std::vector<std::string> s2v(std::string str){
    std::vector<std::string> ans;
    int index = 0;
    if(!str.empty()){
        while(index = str.find(' ', index) != string::npos){
            str.erase(index, 1);
        }
    }
    string tmp;
    for(int i = 0; i < str.length(); i++){
        if(str[i] == ','){
            ans.push_back(tmp);
            tmp.clear();
            continue;
        }
        tmp += str[i];
    }
    return ans;
}

std::string v2s(std::vector<std::string> v, std::string before, std::string end){
    std::string ans;
    for(std::string i : v){
        ans += (before + i + end);
    }
    return ans;
}
#include "functions.hpp"

extern "C" std::vector<std::string> s2v(std::string str){
    std::vector<std::string> ans;
    int index = 0;
    if(!str.empty()){
        while(index = str.find(' ', index) != std::string::npos){
            str.erase(index, 1);
        }
    }
    std::string tmp;
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
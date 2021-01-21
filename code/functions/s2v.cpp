#include "functions.hpp"
#include "../language/language.hpp"
#include <cstdio>
#include <memory.h>

extern "C" std::vector<std::string> s2v(std::string str){
    if(str == NULLSTR){
        return std::vector<std::string>();
    }
    std::vector<std::string> ans;
    char buffer[1024];
    int index = 0;
    memset(buffer, 0, sizeof(buffer));
    for(int i = 0; i < str.length(); i++){
        if(str[i] == '&' || i == str.length()-1){
            buffer[index] = '\0';
            ans.push_back(buffer);
            index = 0;
            memset(buffer, 0, sizeof(buffer));
        }else if(str[i] == ' '){
            continue;
        }else{
            buffer[index++] = i;
        }
    }
    return ans;
}
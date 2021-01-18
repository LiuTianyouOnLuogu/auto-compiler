#include "functions.hpp"

extern "C" std::string v2s(std::vector<std::string> v, std::string before, std::string end){
    std::string ans;
    for(std::string i : v){
        ans += (before + i + end);
    }
    return ans;
}
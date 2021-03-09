#include "language/language.hpp"
#ifdef __cplusplus
extern "C"{
#endif
#include "../Iniparser/iniparser.h"
#ifdef __cplusplus
}
#endif
#include "functions/functions.hpp"
#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char** argv){
    dictionary* ini = iniparser_load(argv[1]);
    int number = atoi(argv[2]);
    string section = iniparser_getsecname(ini, number);
    string lang = iniparser_getstring(ini, (section + ":language").c_str(), NULLSTR);
    if(section == "main") return EXIT_SUCCESS;
    if(lang == NULLSTR){
        NoLang:;
        iniparser_freedict(ini);
        exit(66666);
    }
    //在这里判断语言类型 -------------------------
    #include "language/c.cpp" // 语言文件
    if(lang == "c" || lang == "C"){
        C obj;
        obj.name = section;
        obj.language = lang;
        obj.standrand = iniparser_getstring(ini, (section + ":standrand").c_str(), NULLSTR);
        obj.optimize = iniparser_getint(ini, (section + ":optimize").c_str(), NULLNUM);
        obj.options = parser(iniparser_getstring(ini, (section + ":options").c_str(), NULLSTR), "-", " ");
        int status = obj.make();
        if(status != 0){
            iniparser_freedict(ini);
            exit(status);
        }
    }else{
        goto NoLang; //语言不支持
    }
    return EXIT_SUCCESS;
}
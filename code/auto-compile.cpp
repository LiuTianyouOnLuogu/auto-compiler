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
    string filename = "ac.ini";
    dictionary* ini = NULL;
    string link_cmd = "ld ";
    if(argc == 3 && !strcmp(argv[1], "--config")){
        filename = argv[2];
        goto start; //跳入正常的处理
    }else if(argc == 2 && !strcmp(argv[1], "--help")){
        return system("cat ../README.md");
    }else if(argc==1){
        start:;
        iniparser_load(filename.c_str());
        if(ini == NULL){
            cerr << "Error: Can NOT read config file!" << endl;
            return EXIT_FAILURE;
        }
        for(int i = 0; i < iniparser_getnsec(ini); i++){
            string section = iniparser_getsecname(ini, i);
            string lang = iniparser_getstring(ini, (section + ":language").c_str(), NULLSTR);
            if(lang == NULLSTR){
                NoLang: cerr << "Error: Can NOT read language what you use!" << endl;
                iniparser_freedict(ini);
                return EXIT_FAILURE;
            }
            //在这里判断语言类型 -------------------------
            #include "language/c.cpp" // 语言文件
            if(lang == "c" || lang == "C"){
                C obj;
                obj.name = section;
                obj.language = lang;
                obj.standrand = iniparser_getstring(ini, (section + ":standrand").c_str(), NULLSTR);
                obj.optimize = iniparser_getint(ini, (section + ":optimize").c_str(), NULLNUM);
                obj.defines = s2v(iniparser_getstring(ini, (section + ":define").c_str(), NULLSTR));
                obj.options = s2v(iniparser_getstring(ini, (section + ":options").c_str(), NULLSTR));
                if(!obj.make()){
                    iniparser_freedict(ini);
                    return EXIT_FAILURE;
                }
            }else{
                goto NoLang; // 没有语言
            }
        }
        link_cmd += (string("-o ") + iniparser_getstring(ini, "main:name", NULLSTR));
        vector<string> options = s2v(iniparser_getstring(ini, "main:options", NULLSTR));
        link_cmd += v2s(options, "", " ");
        vector<string> libraries = s2v(iniparser_getstring(ini, "main:library", NULLSTR));
        link_cmd += v2s(libraries, "-l", " ");
        cout << link_cmd << endl;
        if(!system(link_cmd.c_str())){
            iniparser_freedict(ini);
            return EXIT_FAILURE;
        }
        iniparser_freedict(ini);
        return EXIT_SUCCESS;
    }else{
        cerr << "Error: Invild command line!" << endl;
        return EXIT_FAILURE;
    }
}
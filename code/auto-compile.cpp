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
#include <signal.h>
#include <thread>
using namespace std;

#define MAIN 2147483646

int main_pid = 0;

int subthread(dictionary* ini, int number){
    string section = iniparser_getsecname(ini, number);
    if(section == "main") return MAIN;
    string lang = iniparser_getstring(ini, (section + ":language").c_str(), NULLSTR);
    clog << "Compiling: " << section << endl;
    if(lang == NULLSTR){
        NoLang: cerr << "Error: Can NOT read language what you use!" << endl;
        iniparser_freedict(ini);
        kill(main_pid, 2);
        exit(EXIT_FAILURE);
    }
    //在这里判断语言类型 -------------------------
    #include "language/c.cpp" // 语言文件
    if(lang == "c" || lang == "C"){
        string objs = "";
        C obj;
        obj.name = section;
        obj.language = lang;
        obj.standrand = iniparser_getstring(ini, (section + ":standrand").c_str(), NULLSTR);
        obj.optimize = iniparser_getint(ini, (section + ":optimize").c_str(), NULLNUM);
        obj.options = parser(iniparser_getstring(ini, (section + ":options").c_str(), NULLSTR), "-", " ");
        cerr << "[" << number << "] Compiling C file " << obj.name << "..." << endl;
        int status = obj.make(objs);
        if(status != 0){
            cerr << "[" << number << "] " << "Return status: " << status << endl;
            iniparser_freedict(ini);
            kill(main_pid, 2);
            exit(EXIT_FAILURE);
        }
    }else{
        goto NoLang; //语言不支持
    }
    clog << "[" << getpid() << "] done." << endl; 
}

int main(int argc, char** argv){
    main_pid = getpid();
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
        ini = iniparser_load(filename.c_str());
        if(ini == NULL){
            cerr << "Error: Can NOT read config file!" << endl;
            return EXIT_FAILURE;
        }
        thread threads[10240]; 
        for(int i = 0; i < iniparser_getnsec(ini); i++){
            if(string(iniparser_getsecname(ini, i)) == "main") continue;
            threads[i] = thread(subthread, ini, i);
            threads[i].detach();
        }
        for(int i = 0; i < iniparser_getnsec(ini); i++){
            if(threads[i].joinable()) threads[i].join();
        }
        string objs = "";
        clog << "Compiling: main" << endl;
        link_cmd += objs + " ";
        link_cmd += (string("-o ") + iniparser_getstring(ini, "main:name", NULLSTR)) + " ";
        link_cmd += parser(iniparser_getstring(ini, "main:library", NULLSTR), "-l", " ");
        //cout << link_cmd << endl;
        int status = system(link_cmd.c_str());
        if(status != 0){
            cerr << "Return status: " << status << endl;
            iniparser_freedict(ini);
            return EXIT_FAILURE;
        }
        iniparser_freedict(ini);
        return EXIT_SUCCESS;
    }else{
        cerr << "Error: Invaild command line!" << endl;
        return EXIT_FAILURE;
    }
}
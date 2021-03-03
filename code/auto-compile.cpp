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
    string objs;
    string filename = "ac.ini";
    dictionary* ini = NULL;
    string link_cmd = "ld ";
    char buffer[10240];
    readlink("/proc/self/exe", buffer, 10240);
    string pwd = buffer;
    pwd = pwd.substr(0, pwd.length() - 12);
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
        for(int i = 0; i < iniparser_getnsec(ini); i++){
            string name = iniparser_getsecname(ini, i);
            if(name == "main") continue;
            string cmd;
            char buf[1024];
            sprintf(buf, "%d", i);
            cmd = pwd + "submission " + filename + " " + buf;
            clog << "Command: " << cmd << endl;
            clog << "Making a process: " ;
            int status = system(cmd.c_str());
            if(status != EXIT_SUCCESS){
                return status;
            }
            std::string object = name.substr(0, name.find("."));
            objs += "/tmp/" + object + ".o ";
        }
        clog << "Linking objects..." << endl;
        link_cmd += objs + " ";
        link_cmd += (string("-o ") + iniparser_getstring(ini, "main:name", NULLSTR)) + " ";
        link_cmd += parser(iniparser_getstring(ini, "main:library", NULLSTR), "-l", " ");
        cout << link_cmd << endl;
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
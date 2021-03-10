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
#include <thread>
#include <list>
#include <signal.h>
using namespace std;

struct threadPlus{
    int number;
    thread* t;
    threadPlus(int no, thread* _t){
        number = no;
        t = _t;
    }
};

list<threadPlus> threadPool;

void CE(int sig){
    cerr << "An Unexpeted Error Happened." << endl;
    system("cat error.log");
    if(!debug) remove("error.log");
    exit(EXIT_FAILURE);
}

void subthread(const char* cmd, pid_t pid){
    int status = system(cmd);
    if(status != 0){
        kill(pid, SIGUSR1); //如果失败，发送失败信号
    }
}

int main_pid = 0; //主线程pid
bool debug = false; //debug标志

int main(int argc, char** argv){
    signal(SIGUSR1, CE);
    main_pid = getpid();
    system("echo > error.log"); //清空日志
    string objs;
    string filename = "ac.ini";
    dictionary* ini = NULL;
    string link_cmd = "ld ";
    char buffer[10240];
    int number = 0;
    readlink("/proc/self/exe", buffer, 10240);
    string pwd = buffer;
    pwd = pwd.substr(0, pwd.length() - 12);
    if(argc == 2 && !strcmp(argv[1], "--debug")){
        debug = true;
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
            char buf[1024], pid[1024];
            sprintf(buf, "%d", i);
            sprintf(pid, "%d", getpid());
            cmd = pwd + "submission " + filename + " " + buf + " 2>> error.log";
            //clog << "Command: " << cmd << endl;
            clog << "Compiling  " + name + "..." << endl;
            threadPool.push_back(threadPlus(number++, 0));
            threadPool.back().t = new thread(subthread, cmd.c_str(), main_pid);
            if(threadPool.back().t->joinable()) threadPool.back().t->detach(); //有时线程执行过快，无法脱离
            std::string object = name.substr(0, name.find("."));
            objs += "/tmp/" + object + ".o ";
        }
        while(!threadPool.empty()){ //测试：多线程处理
            if(threadPool.back().t->joinable()) threadPool.front().t->join(); //加入主线程
            threadPool.pop_front();
        }
        clog << "Linking objects..." << endl;
        link_cmd += objs + " ";
        link_cmd += (string("-o ") + iniparser_getstring(ini, "main:name", NULLSTR)) + " ";
        link_cmd += parser(iniparser_getstring(ini, "main:library", NULLSTR), "-l", " ");
        link_cmd += " 2>> error.log";
        subthread(link_cmd.c_str(), main_pid);
        if(!debug) remove("error.log");
        iniparser_freedict(ini);
        return EXIT_SUCCESS;
    }else{
        cerr << "Error: Invaild command line!" << endl;
        return EXIT_FAILURE;
    }
}
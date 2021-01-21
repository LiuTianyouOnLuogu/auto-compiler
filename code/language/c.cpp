#include "language.hpp"
#include "../functions/functions.hpp"
#include <iostream>
#include <string>

class C : public objfile{
    public:
        std::string standrand;
        int optimize;
        std::vector<std::string> defines;
        std::vector<std::string> options;
        int make(std::string& objs){
            std::string object = name.substr(0, name.find("."));
            objs += "/tmp/" + object + ".o ";
            std::string cmd = "gcc -c " + object + ".c ";
            if(standrand != NULLSTR){
                cmd += ("-std=" + standrand + " ");
            }
            if(optimize != NULLNUM){
                cmd += (std::string("-O") + (char)(optimize + '0') + " ");
            }
            if(!defines.empty()){
                cmd += v2s(defines, "-D", " ");
            }
            if(!options.empty()){
                cmd+= v2s(options, "", " ");
            }
            cmd += "-o /tmp/" + object + ".o";
            std::cout << cmd << std::endl;
            return system(cmd.c_str());
        }
};
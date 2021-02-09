#include "language.hpp"
#include "../functions/functions.hpp"
#include <iostream>
#include <string>

class C : public objfile{
    public:
        std::string standrand;
        int optimize;
        std::string options;
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
            if(!options.empty()){
                cmd += options;
            }
            cmd += "-o /tmp/" + object + ".o";
            std::cout << cmd << std::endl;
            return system(cmd.c_str());
        }
};
#include "language.hpp"
#include "../functions/functions.hpp"
#include <iostream>
#include <string>

class C : public objfile{
    public:
        std::string standrand;
        int optimize;
        std::string options;
        int make(){
            std::string object = name.substr(0, name.find("."));
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
            return system(cmd.c_str());
        }
};
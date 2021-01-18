#pragma once

#include <string>
#include <vector>

#define NULLSTR (char*)"null"
#define NULLNUM -1

class objfile{
    public:
        std::string name;
        std::string language;
        virtual int make();
};
/*
这是语言类的基类，开发者可以通过基类设计语言的处理方式和内容。
语言类一致大写。
*/
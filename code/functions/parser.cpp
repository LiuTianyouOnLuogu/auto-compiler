#include "functions.hpp"
#include <cstring>
using namespace std;

string parser(char* orginal, string begin, string end){
    string final;
    char *retptr, *ptr = orginal;
    while ((retptr=strtok(ptr, "&")) != NULL) {
        final += begin + retptr + end;
        ptr = "";
    }
    return final;
}
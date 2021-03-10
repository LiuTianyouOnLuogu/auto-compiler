#include "functions.hpp"
#include <cstring>
using namespace std;

string parser(char* orginal, const char* begin, const char* end, const char* dot) {
    string final;
    char *retptr, *ptr = orginal;
    while ((retptr=strtok(ptr, dot)) != NULL) {
        final += (string)begin + retptr + (string)end;
        ptr = NULL;
    }
    return final;
}
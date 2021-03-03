#include "functions.hpp"
#include <cstring>
using namespace std;

string parser(char* orginal, const char* begin, const char* end) {
    string final;
    char *retptr, *ptr = orginal;
    while ((retptr=strtok(ptr, "&")) != NULL) {
        final += (string)begin + retptr + (string)end;
        ptr = NULL;
    }
    return final;
}
#pragma once

#include <string>
#include <vector>

extern "C" std::vector<std::string> s2v(std::string str);
extern "C" std::string v2s(std::vector<std::string> v, std::string before, std::string end);
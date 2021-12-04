#pragma once
#include "pony.hpp"
#define HOME 1
#ifndef DEBUG
#define int int64_t
#define for(...) for(auto __VA_ARGS__)
#endif
#define in :
#define ima auto main(signed _argc,char**_argv) -> decltype(decltype(_argc)(**_argv))
#ifndef REALITY
// #include "unicorn.hpp"
#endif
#define _rand srand(time(0));
#define sysargv auto argv=std::vector<std::string>(_argv,_argv+_argc);
#define let auto
#define var auto
#define TO_STR(...) #__VA_ARGS__
#define MACRO_TO_STR(...) TO_STR(__VA_ARGS__)
using namespace std;
#define print(...) print(__VA_ARGS__);
#define write(...) write(__VA_ARGS__);
#define def auto
#define pass

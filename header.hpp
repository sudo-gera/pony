#include "pony.hpp"
#ifndef DEBUG
#define int int64_t
#define for(...) for(auto __VA_ARGS__)
#endif
#define in :
// #define _main using namespace std;signed main(signed _argc,char**_argv)
#define _main using namespace std;signed main()
#define intmain _main
#define ima _main
#ifndef REALITY
#include "unicorn.hpp"
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

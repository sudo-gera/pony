#pragma once
#if __cplusplus<202000
#define maybe_constexpr
#else
#define maybe_constexpr constexpr
#endif
#include "pony.hpp"
#define HOME 1
// #ifndef DEBUG
// #define int int64_t
// #define for(...) for(auto __VA_ARGS__)
// #endif
// #define ima ;auto main(signed _argc,char**_argv) -> decltype(decltype(_argc)(**_argv))
#ifndef REALITY
// #include "unicorn.hpp"
#endif
// #define _rand srand(time(0));
#define sysargv auto argv=std::vector<std::string>(_argv,_argv+_argc);
<<<<<<< HEAD
// #define let auto
=======
#define let auto
>>>>>>> 7055bdeab3ba1d34a78074dad3b68759859392e5
// #define var auto
#define TO_STR(...) #__VA_ARGS__
#define MACRO_TO_STR(...) TO_STR(__VA_ARGS__)
using namespace std;
// using namespace boost;
// #define write(...) write(__VA_ARGS__);
// #define put(...) put(__VA_ARGS__);
#define def auto
#define pass
#define typeof(...) decltype(__VA_ARGS__)
#undef assert
#define assert(...) assert_f(__VA_ARGS__,#__VA_ARGS__)
#define assert_m(...) assert_f(__VA_ARGS__,#__VA_ARGS__)

bool assert_f(bool q,std::string f){
	bool*a=&q;
	if (not q){
		cerr<<"\x1b[91massertion failed: \x1b[0m"<<f<<endl;
		while (a){
			q=*++a;
		}
	}
	return q;
}

#define CL000 "\x1b[0m"
#define CL030 "\x1b[30m"
#define CL031 "\x1b[31m"
#define CL032 "\x1b[32m"
#define CL033 "\x1b[33m"
#define CL034 "\x1b[34m"
#define CL035 "\x1b[35m"
#define CL036 "\x1b[36m"
#define CL037 "\x1b[37m"
#define CL040 "\x1b[40m"
#define CL041 "\x1b[41m"
#define CL042 "\x1b[42m"
#define CL043 "\x1b[43m"
#define CL044 "\x1b[44m"
#define CL045 "\x1b[45m"
#define CL046 "\x1b[46m"
#define CL047 "\x1b[47m"
#define CL030 "\x1b[30m"
#define CL091 "\x1b[31m"
#define CL092 "\x1b[32m"
#define CL093 "\x1b[33m"
#define CL094 "\x1b[34m"
#define CL095 "\x1b[35m"
#define CL096 "\x1b[36m"
#define CL097 "\x1b[37m"
#define CL100 "\x1b[100m"
#define CL101 "\x1b[101m"
#define CL102 "\x1b[102m"
#define CL103 "\x1b[103m"
#define CL104 "\x1b[104m"
#define CL105 "\x1b[105m"
#define CL106 "\x1b[106m"
#define CL107 "\x1b[107m"



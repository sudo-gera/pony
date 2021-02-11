#ifdef replace_int
using ___main=old_int;
#else
using ___main=int;
#endif
#define pony_wakeup using namespace std;
#define pony_run void pony()
#include "funcsynt.hpp"
#define let auto
#define var auto
#define in :
#define while while(
#define do )
#define if if(
#define elif else if
#define for for(auto 
#define str string
#ifdef inf_included
	using long_int=inf;
#else
	using long_int=int_least64_t;
#endif
#define short_int int_least64_t

std::vector<std::string>argv;

void pony();

___main main(___main _argc,char**_argv){
	{
		___main g=0;
		while g<_argc do
		{
			argv.push_back(_argv[g]);
			g++;
		}
	}
	pony();
	return 0;
}

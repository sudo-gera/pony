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
#define len(q) q.size()
#define append push_back
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
	argv=decltype(argv)(_argv,_argv+_argc);
	pony();
	return 0;
}


#define scan(t) scan_f<t>()
template <typename t>
t scan_f(){
	t q;
	std::cin>>q;
	return q;
}

#define print(...) print_f(__VA_ARGS__);
template <typename... t>
void print_f(t... a){
	int dummy[sizeof...(t)] = { (std::cout<<a<<' ', 0)... };
	std::cout<<std::endl;
}

#define print_nn(...) print_nn_f(__VA_ARGS__);
template <typename... t>
void print_nn_f(t... a){
	int dummy[sizeof...(t)] = { (std::cout<<a<<' ', 0)... };
}


#define vect(...) vect_funct({__VA_ARGS__})
template <typename t>
std::vector<t> vect_funct(std::initializer_list<t> a){
	std::vector<t> s(a.begin(),a.end());
	return s;
}

#define vect_by_val(t) vector<decltype(t)>()
#define vect_by_type(t) vector<t>()













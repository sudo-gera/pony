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
typedef std::string str_t;
#define int int64_t
#define float (long double)
#ifdef inf_included
	using long_int=inf;
#else
	using long_int=int_least64_t;
#endif
#define short_int int_least64_t

std::vector<std::u32string>argv;
std::vector<std::string>__argv;

void pony();

___main main(___main _argc,char**_argv){
	__argv=decltype(__argv)(_argv,_argv+_argc);
	for _arg in __argv do{argv.push_back(to_u32(_arg));}
	pony();
	return 0;
}


#define vect(...) vect_funct({__VA_ARGS__})
template <typename t>
std::vector<t> vect_funct(std::initializer_list<t> a){
	std::vector<t> s(a.begin(),a.end());
	return s;
}

#define vect_by_val(t) vector<decltype(t)>()
#define vect_by_type(t) vector<t>()

std::u32string str(){
	return std::u32string();
}

#define to_make_str(type,code) std::u32string str(type orig){let s=std::stringstream();code;return to_u32(s.str());}

to_make_str(const int8_t,s<<int(orig))
to_make_str(const int16_t,s<<orig)
to_make_str(const int32_t,s<<orig)
to_make_str(const int64_t,s<<orig)
to_make_str(const char,let d=str();d.push_back(char32_t(orig));s<<to_u8(d))
to_make_str(const char16_t,let d=str();d.push_back(char32_t(orig));s<<to_u8(d))
to_make_str(const char32_t,let d=str();d.push_back(char32_t(orig));s<<to_u8(d))
to_make_str(const bool,s<<(orig?"True":"False"))
to_make_str(const char *,s<<orig)
// to_make_str(float,s<<orig)
to_make_str(const std::string,s<<orig)
to_make_str(const std::u32string,s<<to_u8(orig))

template<typename t>
to_make_str(std::vector<t>,s<<"[";let y=len(orig);for w in orig do{s<<w<<((--y)?", ":"");};s<<"]";)

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
	int y=sizeof...(t);
	int dummy[sizeof...(t)] = { (std::cout<<to_u8(str(a))<<((--y)?" ":""), 0)... };
	std::cout<<std::endl;
}

#define write(...) print_nn_f(__VA_ARGS__);
template <typename... t>
void print_nn_f(t... a){
	int dummy[sizeof...(t)] = { (std::cout<<to_u8(str(a))                , 0)... };
}



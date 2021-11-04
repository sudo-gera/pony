#ifdef replace_int
using ___main=old_int;
#else
using ___main=int;
#endif
#define pony_run void pony()
#define let auto
#define var auto
#define append push_back
#define in :
#define while while(
#define do )
#define if if(
#define elif else if
#define for for(auto 
#define float (long double)
#define type(q) decltype(q())
#define self (*this)
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


template <typename... t>
auto br(t... a){
	auto s={a...};
	auto f=*s.begin();
	auto d=std::vector<decltype(f)>(s.begin(),s.end());
	return d;
}

template <typename t1,typename t2>
auto vect(t1 b,t2 e){
//	std::cout<<filt(typeid(*b).name())<<'\n';
	auto a=std::vector<typename std::remove_reference<decltype(*b)>::type>();
	while b!=e do{
		a.append(*b);
		++b;
	}
	return a;
}


std::u32string str(){
	return std::u32string();
}

template<typename T>
std::u32string str(T input){
	return human_cast(input,std::u32string());
}

int64_t num(){
	return std::int64_t();
}

template<typename T>
int64_t num(T input){
	return human_cast(input,int64_t());
}

int64_t real(){
	return std::int64_t();
}

template<typename T>
int64_t real(T input){
	return human_cast(input,int64_t());
}

std::string cpp_str(std::u32string input){
	return to_u8(input);
}

std::string c_str(std::u32string input){
	return to_u8(input).c_str();
}

#define scan(t) scan_f(t())
#define to_make_scan(type,code) auto scan_f(type orig){code;return orig;}

to_make_scan(int64_t,std::cin>>orig)
to_make_scan(char,std::cin>>orig)
to_make_scan(std::u32string,let d=std::string();std::cin>>d;orig=to_u32(d))
to_make_scan(std::string,std::cin>>orig)
// to_make_scan(float,std::cin>>orig)



template <typename... t>
void print(t... a){
	int64_t y=sizeof...(t);
	int64_t printed[sizeof...(t)] = { (std::cout<<to_u8(str(a))<<((--y)?" ":""), 0)... };
	std::cout<<std::endl;
}

template <typename... t>
void write(t... a){
	int64_t printed[sizeof...(t)] = { (std::cout<<to_u8(str(a))                , 0)... };
}


def1(len,q){
	return int64_t(q.size());
}


def2(each_f,&a,f){
	let g=std::vector<decltype(f(*a.begin()))>();
	for w in a do{
		g.append(f(w));
	}
	return g;
}

def2(filter_f,&a,f){
	let g=std::vector<typename std::remove_reference<decltype(*a.begin())>::type>();
	for w in a do{
		if f(w) do{
			g.append(w);
		}		
	}
	return g;
}

#define filter(arr,iter,...) filter_f(arr,[&](auto iter){return __VA_ARGS__;})
#define each(arr,iter,...) each_f(arr,[&](auto iter){return __VA_ARGS__;})


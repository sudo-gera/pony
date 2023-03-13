#ifndef ic_output_stream
#define ic_output_stream std::cerr
#endif

#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

template<size_t N,typename...T>
struct get_type_s;
template<size_t N,typename Y,typename...T>
struct get_type_s<N,Y,T...>{
	using type=get_type_s<N-1,T...>;
};
template<typename Y>
struct get_type_s<0,Y>{
	using type=Y;
};
template<size_t N,typename...T>
using get_type=typename get_type_s<N,T...>::type;

template <typename t,typename y>
auto to_str(const std::chrono::duration<t,y>&q){
	std::stringstream ss;
	ss<<q.count()*1.0*y::num/y::den;
	return ss.str();
}
template <typename t>
auto to_str(const t&q)->decltype((    *(std::ostream*)(0)     <<q,str())){
	std::stringstream ss;
	ss<<q;
	return ss.str();
}

auto to_str(const bool&a){
	std::stringstream c;
	c<<(a?"True":"False");
	return c.str();
}

auto print_one(const char*a){
	std::stringstream c;
	if (a){
		c<<a;
	}else{
		c<<"(nullptr)";
	}
	return c.str();
}

auto print_one(char*a){
	std::stringstream c;
	if (a){
		c<<a;
	}else{
		c<<"(nullptr)";
	}
	return c.str();
}

auto to_str(__int128_t a){
	std::string q;
	while (a){
		q+='0'+a%10;
		a/=10;
	}
	if (a<0){
		q+='-';
	}
	if (q.size()==0){
		q+='0';
	}
	reverse(q.begin(),q.end());
	return q;
}
auto to_str(__uint128_t a){
	std::string q;
	while (a){
		q+='0'+a%10;
		a/=10;
	}
	if (q.size()==0){
		q+='0';
	}
	reverse(q.begin(),q.end());
	return q;
}
auto to_str(const int8_t&a){
	std::stringstream c;
	c<<int64_t(a);
	return c.str();
}
auto to_str(const uint8_t&a){
	std::stringstream c;
	c<<uint64_t(a);
	return c.str();
}

str print_one(const str&q){
	return q;
}

template<typename T>
auto print_one(const T&q)->str;

std::string running_file_path;
template<typename T>
int __zero=0;
template<typename...Y>
int ignore_args(const Y&...q){
	auto s=std::vector<int>({__zero<decltype(q)>...});
	return 0;
}


std::vector<std::string> get_fields(std::string q);


#ifdef BOOST_INCLUDED
template <typename Y,typename...T>
auto to_str(const Y&q,const T&...a)->std::enable_if_t<
(
	std::is_copy_constructible_v<Y> or
	(std::is_move_constructible_v<Y> and std::is_move_assignable_v<Y>)
) and 
(
	std::is_aggregate_v<Y> or std::is_scalar_v<Y>
)
,std::string>{
	ignore_args(a...);
	std::stringstream ss;
	auto tq=strtype(q);
	ss<<tq;
	auto f=get_fields(tq);
	ss<<"(";
	int c=0;
	boost::pfr::for_each_field(
	q,
	[&](const auto&w){
		if (c){
			ss<<", ";
		}
		if (c<f.size()){
			ss<<f[c]<<"=";
		}
		++c;
		ss<<print_one(w);
	});
	ss<<")";
	return ss.str();
}
#endif
// template <typename...T>
// auto to_str(const T&...a){
// 	std::stringstream ss;
// 	ignore_args(a...);
// 	std::get<0>(std::make_tuple(std::ref(a)...)).
// 	__how_to_print__;
// 	return ss.str();
// }
template <typename T1,typename T2>
auto to_str(const std::pair<T1,T2>&a){
	std::stringstream _c;
	_c<<"<"<<print_one(a.first)<<", "<<print_one(a.second)<<">";
	return _c.str();
}
template <typename T>
auto to_str(const std::vector<T>&a){
	std::stringstream _c;
	_c<<"[";
	int c=0;
	for (auto &w:a){
		if (c){
			_c<<", ";
		}else{
			++c;
		}
		_c<<print_one(w);
	}
	_c<<"]";
	return _c.str();
}
template <typename T>
auto to_str(const std::list<T>&a){
	std::stringstream _c;
	_c<<"[";
	int c=0;
	for (auto &w:a){
		if (c){
			_c<<", ";
		}else{
			++c;
		}
		_c<<print_one(w);
	}
	_c<<"]";
	return _c.str();
}
template <typename T,typename CMP>
auto to_str(const std::set<T,CMP>&a){
	std::stringstream _c;
	_c<<"{";
	int c=0;
	for (auto const&w:a){
		if (c){
			_c<<", ";
		}else{
			++c;
		}
		_c<<print_one(w);
	}
	_c<<"}";
	return _c.str();
}
template <typename T,typename HASH>
auto to_str(const std::unordered_set<T,HASH>&a){
	std::stringstream _c;
	_c<<"{";
	int c=0;
	for (auto const&w:a){
		if (c){
			_c<<", ";
		}else{
			++c;
		}
		_c<<print_one(w);
	}
	_c<<"}";
	return _c.str();
}
template <typename T1,typename T2,typename CMP>
auto to_str(const std::map<T1,T2,CMP>&a){
	std::stringstream _c;
	_c<<"{";
	int c=0;
	for (auto &w:a){
		if (c){
			_c<<", ";
		}else{
			++c;
		}
		_c<<print_one(w.first);
		_c<<": ";
		_c<<print_one(w.second);		
	}
	_c<<"}";
	return _c.str();
}
template <typename T1,typename T2,typename HASH>
auto to_str(const std::unordered_map<T1,T2,HASH>&a){
	std::stringstream _c;
	_c<<"{";
	int c=0;
	for (auto &w:a){
		if (c){
			_c<<", ";
		}else{
			++c;
		}
		_c<<print_one(w.first);
		_c<<": ";
		_c<<print_one(w.second);		
	}
	_c<<"}";
	return _c.str();
}
template <typename T>
auto to_str(const std::multiset<T>&a){
	std::stringstream _c;
	_c<<"{";
	int c=0;
	for (auto const&w:a){
		if (c){
			_c<<", ";
		}else{
			++c;
		}
		_c<<print_one(w);
	}
	_c<<"}";
	return _c.str();
}
template <typename T>
auto to_str(const std::unordered_multiset<T>&a){
	std::stringstream _c;
	_c<<"{";
	int c=0;
	for (auto const&w:a){
		if (c){
			_c<<", ";
		}else{
			++c;
		}
		_c<<print_one(w);
	}
	_c<<"}";
	return _c.str();
}
template <typename T1,typename T2>
auto to_str(const std::multimap<T1,T2>&a){
	std::stringstream _c;
	_c<<"{";
	int c=0;
	for (auto &w:a){
		if (c){
			_c<<", ";
		}else{
			++c;
		}
		_c<<print_one(w.first);
		_c<<": ";
		_c<<print_one(w.second);		
	}
	_c<<"}";
	return _c.str();
}
template <typename T1,typename T2>
auto to_str(const std::unordered_multimap<T1,T2>&a){
	std::stringstream _c;
	_c<<"{";
	int c=0;
	for (auto &w:a){
		if (c){
			_c<<", ";
		}else{
			++c;
		}
		_c<<print_one(w.first);
		_c<<": ";
		_c<<print_one(w.second);		
	}
	_c<<"}";
	return _c.str();
}
template <typename T>
auto to_str(const std::optional<T>&a){
	std::stringstream _c;
	_c<<"(";
	if (a.has_value()){
		_c<<*a;
	}
	_c<<")";
	return _c.str();
}



template <typename...T>
auto print_f(const T&...a){
	auto h=std::vector<std::string>({print_one(a)...});
	std::string res;
	int c=0;
	for (auto&g:h){
		if (c){
			res+=" ";
		}else{
			c=1;
		}
		res+=g;
	}
	std::cout<<res<<std::endl;
}

template <typename...T>
auto write(const T&...a){
	auto h=std::vector<std::string>({print_one(a)...});
	std::string res;
	int c=0;
	for (auto&g:h){
		if (c){
			res+=" ";
		}else{
			c=1;
		}
		res+=g;
	}
	std::cout<<res<<' '<<std::flush;
}

template <typename...T>
auto put(const T&...a){
	auto h=std::vector<std::string>({print_one(a)...});
	std::string res;
	int c=0;
	for (auto&g:h){
		if (c){
			res+="";
		}else{
			c=1;
		}
		res+=g;
	}
	std::cout<<res<<std::flush;
}

template <typename...T>
auto check_output_f(int64_t line,std::string file,std::string func,std::string args,const T&...a){
	auto h=std::vector<std::string>({print_one(a)...});
	std::string res;
	int c=0;
	for (auto&g:h){
		if (c){
			res+=" ";
		}else{
			c=1;
		}
		res+=g;
	}
	if (h.size()){
		for (auto&g:h){
			if (g==h[0] and &g!=&(h[0]) ){
				return;
			}
		}
	}
	std::cout<<"\x1b[91mERROR \x1b[92mline \x1b[94m"<<line<<"\x1b[92m file \x1b[94m"<<file<<"\x1b[92m func \x1b[94m"<<func<<"\x1b[92m \x1b[93m"<<args<<" : \x1b[0m"<<res<<std::endl;
	std::exit(1);
	return;
}


struct inviz{
	auto operator-(){
		return *this;
	}
	template<typename T>
	friend auto&operator-(const T&q,inviz w){
		ignore_args(w);
		return q; 
	}
};

template<typename T>
bool is_inviz_one(const T&q){
	ignore_args(q);
	return 0;
}

bool is_inviz_one(const inviz&q){
	ignore_args(q);
	return 1;
}

template<typename...T>
bool is_inviz(const T&...q){
	std::vector<bool> a({is_inviz_one(q)...});
	for (auto w:a){
		if (w){
			return 1;
		}
	}
	return 0;
}

std::string to_str(const inviz&q){
	ignore_args(q);
	return "";
}

template<typename...T>
std::vector<str> print_mul(const T&...a){
	return {print_one(a)...};
}

bool isvarname(char q){
	return isalnum(q) or q=='_';
}

auto print_parse(str q){
	std::vector<str> res;
	size_t index=0;
	while (index<q.size()){
		while (index<q.size() and !isvarname(q[index])){
			index++;
		}
		while (index<q.size() and isvarname(q[index])){
			index++;
		}
		while (index<q.size() and !isvarname(q[index])){
			index++;
		}
		res.emplace_back();
		while (index<q.size() and isvarname(q[index])){
			res[res.size()-1]+=q[index++];
		}
	}
	return res;
}


#define enable_print(type,...)\
str to_str(const type&val){\
	auto q=print_mul(__VA_ARGS__);\
	auto a=print_parse(#__VA_ARGS__);\
	str res=str(#type)+"(";\
	int c=0;\
	for (size_t w=0;w<a.size();++w){\
		res+=(c?", ":(c++,""))+a[w]+"="+q[w];\
	}\
	res+=")";\
	return res;\
}

template<typename T>
auto print_one(const T&q)->str{
	return print_one(to_str(q));
}


template <typename...T>
void ic_f(int64_t line,std::string file,std::string func,std::string args,const T&...a){
	auto h=std::vector<std::string>({print_one(a)...});
	if (is_inviz(a...)){
		h.clear();
	}
	std::string res;
	int c=0;
	for (auto&g:h){
		if (c){
			res+=" ";
		}else{
			c=1;
		}
		res+=g;
	}
	if (h.size()){
		ic_output_stream<<"\x1b[92mline \x1b[94m"<<line<<"\x1b[92m file \x1b[94m"<<file<<"\x1b[92m func \x1b[94m"<<func<<"\x1b[92m \x1b[93m"<<args<<" : \x1b[0m"<<res<<std::endl;
	}else{
		ic_output_stream<<"\x1b[92mline \x1b[94m"<<line<<"\x1b[92m file \x1b[94m"<<file<<"\x1b[92m func \x1b[94m"<<func<<"\x1b[92m \x1b[93m"<<args<<" \x1b[0m"<<res<<std::endl;
	}
}



template <typename T>
auto eic(int64_t line,std::string file,std::string func,std::string args,const T& a){
	auto h=std::vector<std::string>({print_one(a)});
	std::string res;
	int c=0;
	for (auto&g:h){
		if (c){
			res+=" ";
		}else{
			c=1;
		}
		res+=g;
	}
	ic_output_stream<<"\x1b[92mline \x1b[94m"<<line<<"\x1b[92m file \x1b[94m"<<file<<"\x1b[92m func \x1b[94m"<<func<<"\x1b[92m \x1b[93m"<<args<<" : \x1b[0m"<<res<<std::endl;
	return a;
}

// #define print(...) {running_file_path=__FILE__;print_f(__VA_ARGS__);}
#define print_m(...) {running_file_path=__FILE__;print_f(__VA_ARGS__);}
// #define ic(...) ic(__LINE__,__PRETTY_FUNCTION__,#__VA_ARGS__,__VA_ARGS__);
#define eic(...) eic(__LINE__,__FILE__,__PRETTY_FUNCTION__,#__VA_ARGS__,__VA_ARGS__)
#define ic(...) {running_file_path=__FILE__;ic_f(__LINE__,__FILE__,__PRETTY_FUNCTION__,#__VA_ARGS__,__VA_ARGS__-inviz());}
#define ic_no_func(...) {running_file_path=__FILE__;ic_f(__LINE__,__FILE__,"",#__VA_ARGS__,__VA_ARGS__-inviz());}
// #define ic(...) {std::cout<<"\x1b[92mline \x1b[94m"<<__LINE__<<"\x1b[92m file \x1b[94m"<<__FILE__<<"\x1b[92m func \x1b[94m"<<__PRETTY_FUNCTION__<<"\x1b[92m \x1b[93m"<<std::string(#__VA_ARGS__)<<" : \x1b[0m";print(__VA_ARGS__);}
#define check_output(...) check_output_f(__LINE__,__FILE__,__PRETTY_FUNCTION__,#__VA_ARGS__,__VA_ARGS__);
// #define test check_output

template<typename T=int64_t>
auto scan(T q=int64_t(0)){
	std::cin>>q;
	return q;
}



template<typename T>
auto scan_one(){
	T q;
	std::cin>>q;
	return q;
}

#define scan(...) scan_one<__VA_ARGS__>()



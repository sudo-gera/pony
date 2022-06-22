// namespace std{
// #ifdef BOOST_INCLUDED
// 	using namespace boost;
// #endif
// }

#define TO_REPEAT_SEP
#define RP_0(x) TO_REPEAT(x)
#define RP_1(x) RP_0(x##0) TO_REPEAT_SEP RP_0(x##1)
#define RP_2(x) RP_1(x##0) TO_REPEAT_SEP RP_1(x##1)
#define RP_3(x) RP_2(x##0) TO_REPEAT_SEP RP_2(x##1)
#define RP_4(x) RP_3(x##0) TO_REPEAT_SEP RP_3(x##1)
#define RP_5(x) RP_4(x##0) TO_REPEAT_SEP RP_4(x##1)
#define RP_6(x) RP_5(x##0) TO_REPEAT_SEP RP_5(x##1)
#define RP_7(x) RP_6(x##0) TO_REPEAT_SEP RP_6(x##1)
#define RP_8(x) RP_7(x##0) TO_REPEAT_SEP RP_7(x##1)
#define RP_9(x) RP_8(x##0) TO_REPEAT_SEP RP_8(x##1)
#define REPEAT(x) RP_##x(0b0)

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
auto print_one(const T&q)->std::enable_if_t<!std::is_same_v<std::add_const_t<std::remove_reference_t<decltype(q)>>,std::add_const_t<std::remove_reference_t<decltype(to_str(q))>>>,str>{
	return print_one(to_str(q));
}

template<typename T>
auto print_one(const T&q)->std::enable_if_t<std::is_same_v<std::add_const_t<std::remove_reference_t<decltype(q)>>,std::add_const_t<std::remove_reference_t<decltype(to_str(q))>>>,str>{
	return
	q.
	__recursion__
	;
}


// str print_one(const str&q);
// template<typename T>
// auto print_one(const T&q)->std::enable_if_t<!std::is_same_v<std::add_const_t<std::remove_reference_t<decltype(q)>>,std::add_const_t<std::remove_reference_t<decltype(to_str(q))>>>,str>;

// template<typename T>
// auto print_one(const T&q)->std::enable_if_t<std::is_same_v<std::add_const_t<std::remove_reference_t<decltype(q)>>,std::add_const_t<std::remove_reference_t<decltype(to_str(q))>>>,str>;

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
	_c<<"<"<<a.first<<", "<<a.second<<">";
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
		std::cerr<<"\x1b[92mline \x1b[94m"<<line<<"\x1b[92m file \x1b[94m"<<file<<"\x1b[92m func \x1b[94m"<<func<<"\x1b[92m \x1b[93m"<<args<<" : \x1b[0m"<<res<<std::endl;
	}else{
		std::cerr<<"\x1b[92mline \x1b[94m"<<line<<"\x1b[92m file \x1b[94m"<<file<<"\x1b[92m func \x1b[94m"<<func<<"\x1b[92m \x1b[93m"<<args<<" \x1b[0m"<<res<<std::endl;
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
	std::cerr<<"\x1b[92mline \x1b[94m"<<line<<"\x1b[92m file \x1b[94m"<<file<<"\x1b[92m func \x1b[94m"<<func<<"\x1b[92m \x1b[93m"<<args<<" : \x1b[0m"<<res<<std::endl;
	return a;
}

#define print(...) {running_file_path=__FILE__;print_f(__VA_ARGS__);}
#define print_m(...) {running_file_path=__FILE__;print_f(__VA_ARGS__);}
// #define ic(...) ic(__LINE__,__PRETTY_FUNCTION__,#__VA_ARGS__,__VA_ARGS__);
#define eic(...) eic(__LINE__,__FILE__,__PRETTY_FUNCTION__,#__VA_ARGS__,__VA_ARGS__)
#define ic(...) {running_file_path=__FILE__;ic_f(__LINE__,__FILE__,__PRETTY_FUNCTION__,#__VA_ARGS__,__VA_ARGS__-inviz());}
#define ic_no_func(...) {running_file_path=__FILE__;ic_f(__LINE__,__FILE__,"",#__VA_ARGS__,__VA_ARGS__-inviz());}
// #define ic(...) {std::cout<<"\x1b[92mline \x1b[94m"<<__LINE__<<"\x1b[92m file \x1b[94m"<<__FILE__<<"\x1b[92m func \x1b[94m"<<__PRETTY_FUNCTION__<<"\x1b[92m \x1b[93m"<<std::string(#__VA_ARGS__)<<" : \x1b[0m";print(__VA_ARGS__);}
#define check_output(...) check_output_f(__LINE__,__FILE__,__PRETTY_FUNCTION__,#__VA_ARGS__,__VA_ARGS__);
// #define test check_output

template<typename...T>
auto arr(T...a){
	auto u={a...};
	auto h=*u.begin();
	return std::vector<decltype(h)>(u);
}
template<typename T=int64_t>
auto scan(T q=int64_t(0)){
	std::cin>>q;
	return q;
}

template<typename T>
auto len(const T& q)->decltype(q.size()){
	return int64_t(q.size());
}

int64_t random(int64_t q=9223372036854775807,int64_t w=-9223372036854775807){
	if (w<q){
		w=q;
		q=0;
	}
	return rand()%(w-q)+q;
}

auto time(){
	struct timespec time={0,0};
	clock_gettime(CLOCK_REALTIME, &time);
	return static_cast<long double>(time.tv_sec)+static_cast<long double>(time.tv_nsec)/1'000'000'000.0;
}
auto monotonic(){
	struct timespec time={0,0};
	clock_gettime(CLOCK_MONOTONIC, &time);
	return static_cast<long double>(time.tv_sec)+static_cast<long double>(time.tv_nsec)/1'000'000'000.0;
}

struct perf_s{
	mutable uint64_t q;
	perf_s(){
		q=clock();
	}
	friend auto&operator<<(std::ostream&qqq,const perf_s&w){
		qqq<<1.0*(clock()-w.q)/CLOCKS_PER_SEC;
		w.q=clock();
		return qqq;
	}
	template <typename T>
	operator T(){
		auto z=1.0*(clock()-q)/CLOCKS_PER_SEC;
		q=clock();
		return z;
	}
};

#define perf(...) perf_f(__LINE__,__FILE__,__PRETTY_FUNCTION__,__VA_ARGS__+0)

uint64_t _perf_prev_=clock();

template <typename...T>
perf_s perf_f(int64_t line,std::string file,std::string func,int arg){
	if (arg==0){
		auto r=1.*(clock()-_perf_prev_)/CLOCKS_PER_SEC;
		char t[1024];
		sprintf(t,"%.9f",r);
		std::cerr<<"\x1b[92mline \x1b[94m"<<line<<"\x1b[92m file \x1b[94m"<<file<<"\x1b[92m func \x1b[94m"<<func<<"\x1b[0m "<<t<<std::endl;
		_perf_prev_=clock();
	}
	return perf_s();
}


auto strip(const std::string&q){
	size_t end=q.size()-1;
	while (isspace(q[end])){
		--end;
	}
	++end;
	size_t start=0;
	while (start<end and isspace(q[start])){
		++start;
	}
	return std::string(q.begin()+long(start),q.begin()+long(end));
}


std::string radix_convert(std::string o,int64_t from,int64_t to){
	o=strip(o);
	int64_t res=0;
	int8_t sign=1;
	if (o.size() and o[0]=='-'){
		sign=-1;
		o=strip(std::string(o.begin()+1,o.end()));
	}
	for (auto g:o){
		res=res*from+"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x3a\x3b\x3c\x3d\x3e\x3f\x40\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x5b\x5c\x5d\x5e\x5f\x60\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x7b\x7c\x7d\x7e\x7f"[int(g)];
	}
	std::string r;
	while (res){
		r+="0123456789abcdefghijklmnopqrstuvwxyz"[res%to];
		res/=to;
	}
	if (r.size()==0){
		r+="0";
	}
	if (sign==-1){
		r+='-';
	}
	reverse(r.begin(),r.end());
	return r;
}

auto bin(int64_t q){
	return radix_convert(std::to_string(q),10,2);
}

auto oct(int64_t q){
	return radix_convert(std::to_string(q),10,8);
}

auto hex(int64_t q){
	return radix_convert(std::to_string(q),10,16);
}

auto dec(int64_t q){
	return std::to_string(q);
}

template<typename T>
auto bin_repr(const T&q){
	auto h=reinterpret_cast<const int8_t*>(&q);
	auto res=std::string();
	for (auto w:range(sizeof(q))){
		for (auto e : range(8)){
			res+='0'+bool(h[w]&(1<<e));
		}
	}
	reverse(res.begin(),res.end());
	return res;
}


std::string popen(std::string q){
	std::string s;
	auto pipe=popen(q.c_str(), "r");
	int c; // note: int, not char, required to handle EOF
	while ((c = fgetc(pipe)) != EOF) { // standard C I/O file reading loop
		s+=static_cast<char>(c);
	}
	pclose(pipe);
	// print(s);
	return s;
}

auto replace(std::string q,std::string w,std::string e){
	std::string res;
	uint64_t a=0;
	while (a<uint64_t(len(q))){
		if (q.find(w,a)==a){
			res+=e;
			a+=w.size();
		}else{
			res+=q[a];
			++a;
		}
	}
	return res;
}

std::string python(std::string q){
	q=replace(q,"\\","\\\\");
	q=replace(q,"\"","\\\"");
	q=replace(q,"`","\\`");
	q=replace(q,"$","\\$");
	return popen("python3 -c \""+q+"\"");
}

auto split(std::string q){
	auto res=std::vector<std::string>();
	res.emplace_back();
	for (auto&w:q){
		if (isspace(w)){
			res.emplace_back();
		}else{
			res.end()[-1]+=w;
		}
	}
	auto _res=std::vector<std::string>();
	for (auto&e:res){
		if (e.size()){
			_res.push_back(e);
		}
	}
	return _res;
}

auto readfile(FILE*q){
	std::string s;
	int c; // note: int, not char, required to handle EOF
	while ((c = fgetc(q)) != EOF) { // standard C I/O file reading loop
		s+=static_cast<char>(c);
	}
	return s;
}

auto readfilename(std::string q){
	FILE*g=fopen(q.c_str(),"r");
	if (!g){
		ic("file does not excists:",q)
	}
	auto a=readfile(g);
	fclose(g);
	return a;
}

template<typename T>
auto get_type_f(const T&q){
	auto tmp=*q;
	return tmp;
}

template<typename T1,typename T2>
auto itervect(const T1&_q,const T2&e){
	auto q=_q;
	// std::vector<typename std::remove_reference<decltype(*q)>::type> res;
	std::vector<decltype(get_type_f(q))> res;
	while (q!=e){
		res.push_back(*q);
		++q;
	}
	return res;
}

template<typename T>
auto scan_one(){
	T q;
	std::cin>>q;
	return q;
}

#define scan(...) scan_one<__VA_ARGS__>()




struct pyfunc_s{
	std::string f;
	std::string q;
	auto&operator=(const std::string&_q){
		f="def pyfunc("+f+"):\n"+_q;
		return *this;
	}
	pyfunc_s(std::string _f):f(_f){}
	template <typename...T>
	auto operator()(const T&...a){
		q="from json import *\nprint(dumps(pyfunc(";
		std::vector<int>({add(a)...});
		q+=")))";
		auto code=f+"\n\n"+q+"\n\n";
		q=code;
		q="from json import *\nexec(loads("+alnumdumps(dumps(code))+"))\n";
		return loads(python(q));
	}
	pyfunc_s(size_t line,std::string file,std::string _f):f(_f){
		auto h=pyfunc_s("line,file")=
		"	a=open(file).read().splitlines()[line:]\n"
		"	a.append('')\n"
		"	a=a[:a.index([w for w in a if not w.strip().startswith('//')][0])]\n"
		"	a=[w.replace('//','  ',1) for w in a]\n"
		"	a='\\n'.join(a)+'\\n'\n"
		"	return a";
		f="def pyfunc("+f+"):\n"+std::string(h(line,file));
	}
	template<typename T>
	int add(const T&w){
		q+="loads("+dumps(dumps(w))+"),";
		return 0;
	}
};

#define pyfunc(...) pyfunc_s(__LINE__,__FILE__,#__VA_ARGS__);

#define refdecltype(...) remove_reference_t<decltype(__VA_ARGS__)>

#ifdef __clang__
template<typename...base>
struct __type_check;

template<typename b1,typename...base>
struct __type_check<b1,base...>{
	template<typename...work>
	struct eee;
	template<typename w1,typename...work>
	struct eee<w1,work...>{
		const static bool value = __type_check<b1,base...>::eee<w1>::value and __type_check<b1,base...>::eee<work...>::value;
	};
	template<typename w1>
	struct eee<w1>{
		const static bool value = __type_check<b1>::template eee<w1>::value or __type_check<base...>::template eee<w1>::value;
	};
	template<>
	struct eee<>{
		const static bool value = 1;
	};
};

template<typename b1>
struct __type_check<b1>{
	template<typename...work>
	struct eee;
	template<typename w1,typename...work>
	struct eee<w1,work...>{
		const static bool value = __type_check<b1>::eee<w1>::value and __type_check<b1>::eee<work...>::value;
	};
	template<typename w1>
	struct eee<w1>{
		const static bool value = std::is_same<b1,w1>::value;
	};
	template<>
	struct eee<>{
		const static bool value = 1;
	};
};

template<>
struct __type_check<>{
	template<typename...work>
	struct eee{
		const static bool value = 0;
	};
	template<>
	struct eee<>{
		const static bool value = 1;
	};
};

template<typename...work>
struct all_types{
	template<typename...base>
	const bool static are_from=__type_check<base...>::template eee<work...>::value;
};
#endif

pyfunc_s py_import(str cf,str file,str name){
	while (cf.size() and cf.end()[-1]!='/'){
		cf=str(cf.begin(),cf.end()-1);
	}
	if (file.find('/')==file.npos){
		file=cf+file;
	}
	if (file.size()<3 or not (file.end()[-3]=='.' and file.end()[-2]=='p' and file.end()[-1]=='y')){
		file+=".py";
	}
	// auto r=dumps(dumps(readfilename(file)+"\n\n__args__array.append("+name+")\n"));
	return pyfunc_s("*__args__args")=
	"	from json import loads,dumps\n"
	"	from sys import stderr,path\n"
	"	from os.path import dirname\n"
	"	q=("+alnumdumps(dumps(file))+")\n"
	"	q=loads(q)\n"
	"	path.append(dirname(q))\n"
	"	q=q[len(dirname(q)):-3]\n"
	"	if q[0]=='/': q=q[1:]\n"
	"	f=__import__(q)\n"
	"	f=f."+name+"\n"
	"	return f(*__args__args)\n";
}
#define import(f,...) auto f=py_import(__FILE__,#__VA_ARGS__,#f);

str fields_db="{}";

import(py_get_fields,get_fields)
std::vector<str> get_fields(str type){
	auto z=std::map<str,std::vector<str>>(loads(fields_db));
	if (!z.count(type)){
		auto h= py_get_fields(fields_db,running_file_path,type);
		fields_db=str(h);
	}
	z=std::map<str,std::vector<str>>(loads(fields_db));
	return z[type];
}

#define py_func(name) auto name = __LINE__ *= #name *= __py_func

#define __py_func(...) (__py_func_s{.name="",.code=#__VA_ARGS__,.line=__LINE__,.file=__FILE__,.line1=0});

struct __py_func_s{
	str name;
	str code;
	uint64_t line=0;
	str file;
	uint64_t line1=0;
};

auto pyfunc_create(str name,str code,size_t line,str file,size_t line1){
	auto s=pyfunc_s("code,line,file,line1")=
	"	from sys import stderr\n"
	"	from re import findall,split\n"
	"	s=open(file).read().split('\\n')\n"
	"	s='\\n'.join(s[line1:line-1])\n"
	"	a=s[:len(s)-len(s.lstrip())]\n"
	"	s=s[len(a):]\n"
	"	a=a[::-1]\n"
	"	a=a[:(a+'\\n').index('\\n')]\n"
	"	a=a[::-1]\n"
	"	s=a+s\n"
	"	s=s.rstrip()\n"
	"	s=s.splitlines()\n"
	"	s=[w for w in s if w.strip()]\n"
	"	s=[[w.index(w.lstrip()),w.lstrip()] for w in s]\n"
	"	m=min(list(zip(*s))[0])\n"
	"	s=[[w[0]-m+1,w[1]] for w in s]\n"
	"	s=['\\t'*w[0]+w[1] for w in s]\n"
	"	s='\\n'.join(s)\n"
	"	s+='\\n\\n\\treturn "+name+"(*__args__args)\\n'\n"
	"	return s\n";
	str d=s(code,line,file,line1);
	return pyfunc_s("*__args__args")=d;
}

auto operator*=(str a,__py_func_s s){
	s.name=a;
	return s;
}

auto operator*=(uint64_t a,__py_func_s s){
	return pyfunc_create(s.name,s.code,s.line,s.file,a);
}


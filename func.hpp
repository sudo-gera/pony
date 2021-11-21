auto print_one(const bool&a){
	std::stringstream c;
	c<<(a?"True":"False");
	return c.str();
}
auto print_one(const int8_t&a){
	std::stringstream c;
	c<<int64_t(a);
	return c.str();
}
auto print_one(const uint8_t&a){
	std::stringstream c;
	c<<uint64_t(a);
	return c.str();
}
template <typename T>
auto print_one(const T&a){
	std::stringstream c;
	c<<a;
	return c.str();
}
template <typename T>
auto print_one(const std::vector<T>&a){
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
auto print_one(const std::set<T>&a){
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
auto print_one(const std::map<T1,T2>&a){
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
auto print(const T&...a){
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
			res+="";
		}else{
			c=1;
		}
		res+=g;
	}
	std::cout<<res;
	// int c=0;
	// std::vector<int*>({((c?(int*)(&(std::cout<<" ")):(int*)(&(++c)))+print_one(a))...});
	// std::cout<<std::endl;
}

template <typename...T>
auto test(int64_t line,std::string func,std::string args,const T&...a){
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
	std::cout<<"\x1b[91mERROR \x1b[92mline \x1b[94m"<<line<<"\x1b[92m func \x1b[94m"<<func<<"\x1b[92m \x1b[93m"<<args<<" : \x1b[0m"<<res<<std::endl;
	return;
}

// template <typename...T>
// auto ic(int64_t line,std::string func,std::string args,const T&...a){
// 	auto h=std::vector<std::string>({print_one(a)...});
// 	std::string res;
// 	int c=0;
// 	for (auto&g:h){
// 		if (c){
// 			res+=" ";
// 		}else{
// 			c=1;
// 		}
// 		res+=g;
// 	}
// 	std::cout<<"\x1b[92mline \x1b[94m"<<line<<"\x1b[92m func \x1b[94m"<<func<<"\x1b[92m \x1b[93m"<<args<<" : \x1b[0m"<<res<<std::endl;
// }

template <typename T>
auto eic(int64_t line,std::string func,std::string args,const T& a){
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
	std::cout<<"\x1b[92mline \x1b[94m"<<line<<"\x1b[92m func \x1b[94m"<<func<<"\x1b[92m \x1b[93m"<<args<<" : \x1b[0m"<<res<<std::endl;
	return a;
}

// #define ic(...) ic(__LINE__,__PRETTY_FUNCTION__,#__VA_ARGS__,__VA_ARGS__);
#define eic(...) eic(__LINE__,__PRETTY_FUNCTION__,#__VA_ARGS__,__VA_ARGS__)
#define ic(...) std::cout<<"\x1b[92mline \x1b[94m"<<__LINE__<<"\x1b[92m func \x1b[94m"<<__PRETTY_FUNCTION__<<"\x1b[92m \x1b[93m"<<std::string(#__VA_ARGS__)<<" : \x1b[0m";print(__VA_ARGS__);
#define test(...) test(__LINE__,__PRETTY_FUNCTION__,#__VA_ARGS__,__VA_ARGS__);


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
int64_t len(const T& q){
	return q.size();
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
	return (long double)(time.tv_sec)+(long double)(time.tv_nsec)/1'000'000'000.0;
}
auto monotonic(){
	struct timespec time={0,0};
	clock_gettime(CLOCK_MONOTONIC, &time);
	return (long double)(time.tv_sec)+(long double)(time.tv_nsec)/1'000'000'000.0;
}

struct perf{
	uint64_t q;
	perf(){
		q=clock();
	}
	// template <typename T>
	// perf(const T&q){
	// 	this->q=q;
	// }
	// template <typename T>
	// operator T(){
	// 	return T(q);
	// }
	// friend auto operator-(const perf&q,const perf&w){
	// 	return perf(q.q-w.q);
	// }
	// friend auto operator-=(const perf&q,const perf&w){
	// 	return perf(q.q-w.q);
	// }
	friend auto&operator<<(std::ostream&q,const perf&w){
		q<<1.0*(clock()-w.q)/CLOCKS_PER_SEC;
		return q;
	}
};

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
	return std::string(q.begin()+start,q.begin()+end);
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
		s+=c;
	}
	pclose(pipe);
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

	return popen("python -c \""+q+"\"");
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
		s+=c;
	}
	return s;
}

auto readfilename(std::string q){
	FILE*g=fopen(q.c_str(),"r");
	auto a=readfile(g);
	fclose(g);
	return a;
}


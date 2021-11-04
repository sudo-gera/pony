// namespace CHECK
// {
// 	class No { bool b[2]; };
// 	template<typename T, typename Arg> No operator<< (const T&, const Arg& _a){std::cout<<"\x1b[91m[error value of type \x1b[94m"<<type(_a)<<"\x1b[91m is not printable]\x1b[0m";return No();};

// 	bool Check (...);
// 	No& Check (const No&);

// 	template <typename T, typename Arg = T>
// 	struct EqualExists
// 	{
// 		enum { value = (sizeof(Check(*(T*)(0) << *(Arg*)(0))) != sizeof(No)) };
// 	};
// 	template <typename T>
// 	void _cout(const T& q){
// 		std::cout<<q;
// 	}
// }
template <typename T>
int print_one(const T&a){
	std::cout<<a;
	// CHECK::_cout(a);
	return 0;
}
// template <typename T>
// int print_one(const T&a){
// 	std::cout<<"[error: "<<type(a)<<" is unprintable]";
// 	return 0;
// }
template <typename T>
int print_one(const std::vector<T>&a){
	std::cout<<"[";
	int c=0;
	for (auto &w:a){
		if (c){
			std::cout<<", ";
		}else{
			++c;
		}
		// (c?(int*)(&(std::cout<<", ")):(int*)(&(++c)));
		// std::cout<<", ";
		print_one(w);
	}
	std::cout<<"]";
	return 0;
}
template <typename T>
int print_one(const std::set<T>&a){
	std::cout<<"{";
	int c=0;
	for (auto const&w:a){
		if (c){
			std::cout<<", ";
		}else{
			++c;
		}
		// (c?(int*)(&(std::cout<<", ")):(int*)(&(++c)));
		// std::cout<<", ";
		print_one(w);
	}
	std::cout<<"}";
	return 0;
}
template <typename T1,typename T2>
int print_one(const std::map<T1,T2>&a){
	std::cout<<"{";
	int c=0;
	for (auto &w:a){
		if (c){
			std::cout<<", ";
		}else{
			++c;
		}
		// (c?(int*)(&(std::cout<<", ")):(int*)(&(++c)));
		// std::cout<<", ";
		print_one(w.first);
		std::cout<<": ";
		print_one(w.second);		
	}
	std::cout<<"}";
	return 0;
}
template <typename...T>
auto print(const T&...a){
	int c=0;
	int*j[]={((c?(int*)(&(std::cout<<" ")):(int*)(&(++c)))+print_one(a))...};
	std::cout<<std::endl;
	return int64_t(j);
}
template <typename...T>
void write(const T&...a){
	int c=0;
	int*j[]={((c?(int*)(&(std::cout<<"")):(int*)(&(++c)))+print_one(a))...};
	// std::cout<<std::endl;
}
#define _ic(...) cout<<"\x1b[92mline \x1b[94m"<<__LINE__<<"\x1b[92m func \x1b[94m"<<__PRETTY_FUNCTION__<<"\x1b[92m: \x1b[0m";print(__VA_ARGS__);
// #define write(...) cout<<"\x1b[92mline "<<__LINE__<<":\x1b[0m ";write_f(__VA_ARGS__);
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

// #define create(c,ar) [&](auto a){return c<typename remove_reference<decltype(*a.begin())>::type>(a.begin(),a.end());}(ar)
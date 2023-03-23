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
		snprintf(t,1000,"%.9f",r);
		std::cerr<<"\x1b[92mline \x1b[94m"<<line<<"\x1b[92m file \x1b[94m"<<file<<"\x1b[92m func \x1b[94m"<<func<<"\x1b[0m "<<t<<std::endl;
		_perf_prev_=clock();
	}
	return perf_s();
}

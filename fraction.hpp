template <typename T>
struct fraction_struct{
	T nu,de;
	inline norm{
		auto n=nu;
		auto d=de;
		while (n*d){
			n=n%d;
			d=d%n;
		}
		auto g=n+d;
		nu/=g;
		de/=g;
	}
	friend inline auto operator+=(){

	}
}

template <typename Y>
auto inline fraction(){
	fraction_struct<Y> f;
	return f;
}
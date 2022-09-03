using namespace std::literals;
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

template<typename...T>
auto arr(T...a){
	auto u={a...};
	auto h=*u.begin();
	return std::vector<decltype(h)>(u);
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

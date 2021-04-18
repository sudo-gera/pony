#define to_make_cast(typeout,typein) typeout human_cast(const typein input,typeout ex)
to_make_cast(std::u32string,std::u32string){return input;}
to_make_cast(std::u32string,std::string){return to_u32(input);}
to_make_cast(std::u32string,char*){std::stringstream a;a<<input;return to_u32(a.str());}
to_make_cast(std::u32string,int8_t){std::stringstream a;a<<input;return to_u32(a.str());}
to_make_cast(std::u32string,int16_t){std::stringstream a;a<<input;return to_u32(a.str());}
to_make_cast(std::u32string,int32_t){std::stringstream a;a<<input;return to_u32(a.str());}
to_make_cast(std::u32string,int64_t){std::stringstream a;a<<input;return to_u32(a.str());}
to_make_cast(std::u32string,size_t){std::stringstream a;a<<input;return to_u32(a.str());}
to_make_cast(std::u32string,char){std::stringstream a;a<<input;return to_u32(a.str());}
to_make_cast(std::u32string,char16_t){std::stringstream a;a<<input;return to_u32(a.str());}
to_make_cast(std::u32string,char32_t){std::stringstream a;a<<input;return to_u32(a.str());}
to_make_cast(std::u32string,bool){std::stringstream a;a<<(input?"True":"False");return to_u32(a.str());}
to_make_cast(std::u32string,float){std::stringstream a;a<<input;return to_u32(a.str());}
to_make_cast(std::u32string,double){std::stringstream a;a<<input;return to_u32(a.str());}
to_make_cast(std::u32string,long double){std::stringstream a;a<<input;return to_u32(a.str());}
template<typename ...T>
to_make_cast(std::u32string,std::vector<T...>){
	auto a=human_cast("[",std::u32string());
	auto s=input.begin();
	auto d=input.end();
	while (s!=d){
		auto w=*s;
		a+=human_cast(w,std::u32string());
		++s;
		if (s!=d){
			a+=human_cast(", ",std::u32string());
		}
	}
	a+=human_cast("]",std::u32string());
	return a;
}
template<typename ...T>
to_make_cast(std::u32string,std::set<T...>){
	auto a=human_cast("{",std::u32string());
	auto s=input.begin();
	auto d=input.end();
	while (s!=d){
		auto w=*s;
		a+=human_cast(w,std::u32string());
		++s;
		if (s!=d){
			a+=human_cast(", ",std::u32string());
		}
	}
	a+=human_cast("}",std::u32string());
	return a;
}
template<typename ...T>
to_make_cast(std::u32string,std::map<T...>){
	auto a=human_cast("{",std::u32string());
	auto s=input.begin();
	auto d=input.end();
	while (s!=d){
		auto w=*s;
		a+=human_cast(w.first,std::u32string());
		a+=human_cast(": ",std::u32string());
		a+=human_cast(w.second,std::u32string());
		++s;
		if (s!=d){
			a+=human_cast(", ",std::u32string());
		}
	}
	a+=human_cast("}",std::u32string());
	return a;
}
to_make_cast(long double,char){return (long double)(human_cast(input,int64_t()));}
to_make_cast(long double,char16_t){return (long double)(human_cast(input,int64_t()));}
to_make_cast(long double,char32_t){return (long double)(human_cast(input,int64_t()));}
to_make_cast(long double,std::u32string){std::stringstream a;a<<to_u8(input);long double res;a>>res;return res;}
to_make_cast(long double,std::string){return human_cast(to_u32(input),int64_t());}
to_make_cast(long double,char*){return human_cast(to_u32(std::string(input)),int64_t());}
to_make_cast(long double,int8_t){return (long double)(input);}
to_make_cast(long double,int16_t){return (long double)(input);}
to_make_cast(long double,int32_t){return (long double)(input);}
to_make_cast(long double,int64_t){return (long double)(input);}
to_make_cast(long double,size_t){return (long double)(int64_t(input));}
to_make_cast(long double,bool){return (long double)(int64_t(input));}
to_make_cast(long double,float){return (long double)(input);}
to_make_cast(long double,double){return (long double)(input);}
to_make_cast(long double,long double){return (long double)(input);}
to_make_cast(int64_t,char){return int64_t(input)-int64_t('0');}
to_make_cast(int64_t,char16_t){return int64_t(input)-int64_t('0');}
to_make_cast(int64_t,char32_t){return int64_t(input)-int64_t('0');}
to_make_cast(int64_t,std::u32string){std::stringstream a;a<<to_u8(input);long double res;a>>res;return res;}
to_make_cast(int64_t,std::string){return human_cast(to_u32(input),int64_t());}
to_make_cast(int64_t,char*){return human_cast(to_u32(std::string(input)),int64_t());}
to_make_cast(int64_t,int8_t){return int64_t(input);}
to_make_cast(int64_t,int16_t){return int64_t(input);}
to_make_cast(int64_t,int32_t){return int64_t(input);}
to_make_cast(int64_t,int64_t){return int64_t(input);}
to_make_cast(int64_t,size_t){return int64_t(input);}
to_make_cast(int64_t,bool){return int64_t(input);}
to_make_cast(int64_t,float){return int64_t(input);}
to_make_cast(int64_t,double){return int64_t(input);}
to_make_cast(int64_t,long double){return int64_t(input);}

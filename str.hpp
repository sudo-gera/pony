#include <iostream>
#include <string>
template<typename T>
bool startswith(T self,T edge){
	return (self).rfind(edge,0)==0;
}
template<typename T>
bool endswith(T self, T edge){
	return (self).find(edge,(self).size()-edge.size())==(self).size()-edge.size();
}
char32_t chr(int64_t q){
	if(q<(1<<7)){
		return ((q&127)<<0);
	}
	if(q<(1<<11)){
		return 49280+((q&1984)<<2)+((q&63)<<0);
	}
	if(q<(1<<16)){
		return 14712960+((q&61440)<<4)+((q&4032)<<2)+((q&63)<<0);
	}
	if(q<(1<<21)){
		return 4034953344+((q&1835008)<<6)+((q&258048)<<4)+((q&4032)<<2)+((q&63)<<0);
	}
	std::cerr<<"error in chr(): "<<q<<" is too big"<<std::endl;
	return 0;
}
int64_t ord(char32_t q){
	int64_t r=0;
	int w,e;
	for (w=3*8;w>-1;w-=8){
		int started=0;
		for (e=7;e>-1;--e){
			if (started==0 and (q&(1<<(w+e)))==0){
				started=1;
			} else
			if (started){
				r=(r<<1)+!!(q&(1<<(w+e)));
			}
		}
	}
	return r;
}
std::u32string to_u32(std::string q){
	std::u32string r;
	for(uint64_t w=0;w<q.size();++w){
		if ((q[w]&(0b10000000))==0){
			r.push_back(((int32_t(uint8_t(q[w]))<<0)));
		}
		if ((q[w]&(0b11100000))==0b11000000 and w<q.size()-1){
			r.push_back(((int32_t(uint8_t(q[w]))<<8)+(int32_t(uint8_t(q[w+1]))<<0)));
		}
		if ((q[w]&(0b11110000))==0b11100000 and w<q.size()-2){
			r.push_back(((int32_t(uint8_t(q[w]))<<16)+(int32_t(uint8_t(q[w+1]))<<8)+(int32_t(uint8_t(q[w+2]))<<0)));
		}
		if ((q[w]&(0b11111000))==0b11110000 and w<q.size()-3){
			r.push_back(((int32_t(uint8_t(q[w]))<<24)+(int32_t(uint8_t(q[w+1]))<<16)+(int32_t(uint8_t(q[w+2]))<<8)+(int32_t(uint8_t(q[w+3]))<<0)));
		}
	}
	for(auto &w:r){
		w=ord(w);
	}
	return r;
}

std::string to_u8(std::u32string q){
	for(auto &w:q){
		w=chr(w);
	}	
	std::string r;
	for(auto w:q){
		if (w&0b11111111000000000000000000000000){
			r.push_back((w&0b11111111000000000000000000000000)>>24);
		}
		if (w&0b111111110000000000000000){
			r.push_back((w&0b111111110000000000000000)>>16);
		}
		if (w&0b1111111100000000){
			r.push_back((w&0b1111111100000000)>>8);
		}
		r.push_back(w&0b11111111);
	}
	return r;
}

template<typename T>
auto replace(T self,T old,T ne,long maxcount=-1){
	T res;
	for (uint64_t w=0;w<self.size();){
		if (maxcount and self.rfind(old,w)==w){
			res+=ne;
			w+=old.size();
			maxcount=maxcount>0?maxcount-1:maxcount;
		}else{
			res+=(self)[w];
			++w;
		}
	}
	return res;
}
template<typename T>
std::vector<T> split(T self,T old,int maxcount=-1){
	auto res=std::vector<T>();
	res.push_back(T());
	for (uint64_t w=0;w<(self).size();){
		if (maxcount and (self).rfind(old,w)==w){
			res.push_back(T());
			w+=old.size();
			maxcount=maxcount>0?maxcount-1:maxcount;
		}else{
			res[res.size()-1]+=(self)[w];
			++w;
		}
	}
	return res;
}
template<typename T>
std::vector<T> split(T self){
	auto res=std::vector<T>();
	int need_new=1;
	for (uint64_t w=0;w<(self).size();++w){
		if (T({9, 10, 11, 12, 13, 28, 29, 30, 31, 32}).find(T({(self)[w]}))!=-1){
			need_new=1;
		}else{
			if (need_new){
				res.push_back(T());
				need_new=0;
			}
			res[res.size()-1]+=(self)[w];
		}
	}
	return res;
}
template<typename S,typename V>
auto join(S self,const V&&a){
	S res;
	int c=0;
	for (auto&d:a){
		if (c){
			res+=self;
		}
		res+=d;
		c=1;
	}
	return res;
}
template<typename T>
auto strip(const T&q){
	size_t end=q.size()-1;
	while (isspace(q[end])){
		--end;
	}
	++end;
	size_t start=0;
	while (start<end and isspace(q[start])){
		++start;
	}
	return T(q.begin()+long(start),q.begin()+long(end));
}

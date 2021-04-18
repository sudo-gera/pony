#include <string>
bool startswith(std::u32string self,std::u32string edge){
	return (self).rfind(edge,0)==0;
}
bool endswith(std::u32string self, std::u32string edge){
	return (self).find(edge,(self).size()-edge.size())==(self).size()-edge.size();
}

std::u32string to_u32(std::string q){
	std::u32string r;
	for(int64_t w=0;w<q.size();++w){
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
	return r;
}

std::string to_u8(std::u32string q){
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


std::u32string replace(std::u32string self, std::u32string old,std::u32string ne,int maxcount=-1){
	std::u32string res=to_u32("");
	for (int64_t w=0;w<(self).size();){
		if (maxcount and (self).rfind(old,w)==w){
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
std::vector<std::u32string> split(std::u32string self,std::u32string old,int maxcount=-1){
	auto res=std::vector<std::u32string>();
	res.push_back(std::u32string());
	for (int64_t w=0;w<(self).size();){
		if (maxcount and (self).rfind(old,w)==w){
			res.push_back(std::u32string());
			w+=old.size();
			maxcount=maxcount>0?maxcount-1:maxcount;
		}else{
			res[res.size()-1]+=(self)[w];
			++w;
		}
	}
	return res;
}
std::vector<std::u32string> split(std::u32string self){
	auto res=std::vector<std::u32string>();
	int need_new=1;
	for (int w=0;w<(self).size();++w){
		if (std::u32string({9, 10, 11, 12, 13, 28, 29, 30, 31, 32}).find(std::u32string({(self)[w]}))!=-1){
			need_new=1;
		}else{
			if (need_new){
				res.push_back(std::u32string());
				need_new=0;
			}
			res[res.size()-1]+=(self)[w];
		}
	}
	return res;
}
std::u32string join(std::u32string self,std::vector<std::u32string> a){
	std::u32string res;
	int c=0;
	for (auto d:a){
		if (c){
			res+=self;
		}
		res+=d;
		c=1;
	}
	return res;
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
	printf("%lli is too big\n", q);
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




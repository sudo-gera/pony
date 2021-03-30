#include <string>
bool startswith(std::string self,std::string edge){
	return (self).rfind(edge,0)==0;
}
bool endswith(std::string self, std::string edge){
	return (self).find(edge,(self).size()-edge.size())==(self).size()-edge.size();
}

std::string replace(std::string self, std::string old,std::string ne,int maxcount=-1){
	std::string res="";
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
std::vector<std::string> split(std::string self,std::string old,int maxcount=-1){
	auto res=std::vector<std::string>();
	res.push_back(std::string());
	for (int64_t w=0;w<(self).size();){
		if (maxcount and (self).rfind(old,w)==w){
			res.push_back(std::string());
			w+=old.size();
			maxcount=maxcount>0?maxcount-1:maxcount;
		}else{
			res[res.size()-1]+=(self)[w];
			++w;
		}
	}
	return res;
}
std::vector<std::string> split(std::string self){
	auto res=std::vector<std::string>();
	int need_new=1;
	for (int w=0;w<(self).size();++w){
		if (std::string({9, 10, 11, 12, 13, 28, 29, 30, 31, 32}).find(std::string({(self)[w]}))!=-1){
			need_new=1;
		}else{
			if (need_new){
				res.push_back(std::string());
				need_new=0;
			}
			res[res.size()-1]+=(self)[w];
		}
	}
	return res;
}
std::string join(std::string self,std::vector<std::string> a){
	std::string res;
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

int64_t chr(int64_t q){
	if(q<(1<<7)){
		printf("1\n");
		return ((q&127)<<0);
	}
	if(q<(1<<11)){
		printf("2\n");
		return 49280+((q&1984)<<2)+((q&63)<<0);
	}
	if(q<(1<<16)){
		printf("3\n");
		return 14712960+((q&61440)<<4)+((q&4032)<<2)+((q&63)<<0);
	}
	if(q<(1<<21)){
		printf("4\n");
		return 4034953344+((q&1835008)<<6)+((q&258048)<<4)+((q&4032)<<2)+((q&63)<<0);
	}
	printf("%lli is too big\n", q);
	return 0;
}

int64_t ord(int64_t q){
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








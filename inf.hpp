#define inf_included
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
class inf{
private:
	struct Ninf{
	public:
		std::vector<uint32_t> digits;
		inline void norm(){
			while (digits.size() && digits[digits.size()-1]==0){
				digits.pop_back();
			}
		}
		explicit operator std::string(){
			std::string e;
			Ninf t=*this;
			Ninf m,n;
			Ninf zero(0);
			Ninf ten(10);
			while (t.diff(zero)){
				n=t/ten;
				m=(t.add(n*ten,-1));
				if (m.digits.size()){
					e.push_back(m.digits[0]+'0');
				}else{
					e.push_back('0');
				}
				t=n;
			}
			reverse(e.begin(), e.end());
			return e;
		}
		explicit operator uint_least64_t(){
			uint_least64_t f=0;
			for (uint_least64_t i=0;i<digits.size() and i<sizeof(uint_least64_t)/sizeof(int32_t);i++){
				f+=(uint_least64_t)(digits[i])<<(sizeof(int32_t)*8*i);
			}
			return f;
		}
		inline Ninf(uint_least64_t o){
			digits.clear();
			while (o){
				digits.push_back(o);
				o>>=8*sizeof(int32_t);
			}
		}
		inline Ninf(std::string o){
			digits.clear();
			Ninf dp(1);
			Ninf ten(10);
			reverse(o.begin(), o.end());
			for (uint_least64_t i=0;i<o.size();i++){
				Ninf t(o[i]-'0');
				*this=this->add(t*dp,1);
				dp=dp*ten;
			}
		}
		inline Ninf(){};
		inline Ninf add(Ninf o,int32_t s){
			Ninf a;
			uint_least64_t n=0;
			for (uint_least64_t t=0; t<digits.size() || t<o.digits.size() || n; t++){
				n+=1LL<<(sizeof(int32_t)*8);
				if (t<digits.size()){
					n+=digits[t];
				}
				if (t<o.digits.size()){
					if (s>0){
						n+=o.digits[t];
					}else{
						n-=o.digits[t];
					}
				}
				a.digits.push_back(n);
				n>>=8*sizeof(int32_t);
				n-=1;
			}
			a.norm();
			return a;
		}
		inline int32_t diff(Ninf o){
			o.norm();
			this->norm();
			if (digits.size()<o.digits.size()){
				return -1;
			}
			if (digits.size()>o.digits.size()){
				return 1;
			}
			for (uint_least64_t t=digits.size()-1;t>=0;t--){
				if(digits[t]<o.digits[t]){
					return -1;
				}
				if(digits[t]>o.digits[t]){
					return 1;
				}
			}
			return 0;
		}
		inline Ninf operator*(Ninf o){
			Ninf a;
			for (uint_least64_t u=0;u<digits.size();u++){
				for (uint_least64_t i=0;i<o.digits.size();i++){
					Ninf s;
					uint_least64_t d=(uint_least64_t)(digits[u])*(uint_least64_t)(o.digits[i]);
					s.digits=std::vector<uint32_t> (u+i);
					s.digits.push_back(d);
					s.digits.push_back(d>>8*sizeof(int32_t));
					s.norm();
					a=a.add(s,1);
				}
			}
			a.norm();
			return a;
		}
		inline Ninf operator/(Ninf o){
			Ninf c=1;
			Ninf a=0;
			while (digits.size()>o.digits.size()){
				o=o<<(sizeof(int32_t)*8);
				c=c<<(sizeof(int32_t)*8);
			}
			while (this->diff(o)!=-1){
				c=c<<1;
				o=o<<1;
			}
			while (c.diff(0)){
				if (this->diff(o)>-1){
					*this=this->add(o,-1);
					a=a.add(c,1);
				}
				c=c>>1;
				o=o>>1;
			}
			return a;
			Ninf b(0);
			Ninf one(1);
			Ninf five(1LL<<(8*sizeof(int32_t)-1));
			Ninf e=this->add(one,1);
			while ((e.add(b,-1)).diff(one)==1){
				Ninf c=(e.add(b,1))*five;
				c.digits=std::vector<uint32_t>(c.digits.begin()+1, c.digits.end());
				int32_t d=(c*o).diff(*this);
				if (d==-1){
					b=c;
				}
				if (d==1){
					e=c;
				}
				if (d==0){
					b=c;
					e=c;
				}
			}
			b.norm();
			return b;
		}
		inline Ninf operator<<(Ninf o){
			Ninf a=*this;
			Ninf r;
			uint32_t s;
			if(o.diff(sizeof(int32_t)*8)==-1){
				r=0;
			}else if(o.diff(sizeof(int32_t)*8*2)==-1){
				r=1;
			}else {
				r=o/(sizeof(int32_t)*8);
			}
			s=uint_least64_t(o.add(r*sizeof(int32_t)*8,-1));
			if(r.diff(digits.size())==1){
				r=digits.size();
			}
			auto dig=std::vector<uint32_t>();
			while (r.diff(0)>0){
				r.add(1,-1);
				dig.resize(dig.size()+1);
			}
			dig.insert(dig.end(),a.digits.begin(), a.digits.end());
			a.digits=dig;
			int_least64_t t=0;
			int32_t y=0;
			for(auto d=a.digits.begin();d!=a.digits.end();d++){
				t=(int_least64_t)(*d);
				t<<=s;
				*d=t;
				*d+=y;
				y=t>>(sizeof(int32_t)*8);
			}
			return a;
		}
		inline Ninf operator>>(Ninf o){
			Ninf a=*this;
			Ninf r;
			uint32_t s;
			if(o.diff(sizeof(int32_t)*8)==-1){
				r=0;
			}else if(o.diff(sizeof(int32_t)*8*2)==-1){
				r=1;
			}else {
				r=o/(sizeof(int32_t)*8);
			}
			s=uint_least64_t(o.add(r*sizeof(int32_t)*8,-1));
			if(r.diff(digits.size())==1){
				r=digits.size();
			}
			a.digits=std::vector<uint32_t>(a.digits.begin()+uint_least64_t(r),a.digits.end());
			int_least64_t t=0;
			int32_t y=0;
			for(auto d=a.digits.rbegin();d!=a.digits.rend();d++){
				t=(int_least64_t)(*d)<<(sizeof(int32_t)*8);
				t>>=s;
				*d=t>>(sizeof(int32_t)*8);
				*d+=y;
				y=t;
			}
			return a;
		}
	};
	Ninf mod;
	int32_t sign;
	inline void norm(){
		mod.norm();
		Ninf zero(0);
		if (mod.diff(zero)==0){
			sign=0;
		}else if(sign==0){
			sign=1;
		}
	}
	inline int32_t diff(inf o){
		if (sign < o.sign){
			return -1;
		}
		if (sign > o.sign){
			return 1;
		}
		if (sign==0 && 0==o.sign){
			return 0;
		}
		if (sign==1){
			return mod.diff(o.mod);
		}
		if (sign==-1){
			return -mod.diff(o.mod);
		}
		return 0;
	}
public:
	explicit operator std::string(){
		std::string e;
		if (sign==0){
			e="0";
		}
		if (sign==1){
			e=std::string(mod);
		}
		if (sign==-1){
			e="-"+std::string(mod);
		}
		return e;
	}
	explicit operator int_least64_t(){
		return sign*uint_least64_t(mod);
	}
	inline inf(std::string o){
		sign=1;
		Ninf zero(0);
		if (o[0]=='-'){
			sign=-1;
			o=std::string(o.begin()+1, o.end());
		}
		mod=Ninf(o);
		if (mod.diff(zero)==0){
			sign=0;
		}
	}
	inline inf(){
		sign=0;
	};
	inline inf(int_least64_t o){
		sign=(!!o)*(o<0?-1:1);
		if (o<0){
			o=-o;
		}
		Ninf t(o);
		mod=t;
	}
	friend inline inf inf(std::string o){
		inf a(o);
		return a;
	}
	friend inline inf inf(int_least64_t o){
		inf a(o);
		return a;
	}
	friend inline std::ostream& operator<<(std::ostream& os,inf i){
		os<<std::string(i);
		return os;
	}
	friend inline std::istream& operator>>(std::istream& is,inf&i){
		std::string o;
		is>>o;
		inf t(o);
		i=o;
		i.norm();
		return is;
	}
	friend inline inf abs(inf o){
		inf a=o;
		a.sign*=-1;
		return a;
	}
	inline inf operator+(){
		inf a;
		a.sign=sign;
		a.mod=mod;
		return a;
	}
	inline inf operator+(inf o){
		inf a;
		if (sign==o.sign){
			a.mod=mod.add(o.mod,1);
			a.sign=sign;
		}
		else{
			int32_t d=mod.diff(o.mod);
			if (d==1){
				a.mod=mod.add(o.mod,-1);
				a.sign=sign;
			}else if (d==-1){
				a.mod=o.mod.add(mod,-1);
				a.sign=o.sign;
			}else{
				a=inf(0);
			}
		}
		return a;
	}
	inline inf operator-(){
		inf a;
		a.mod=mod;
		a.sign=-sign;
		return a;
	}
	inline inf operator-(inf o){
		return *this+(-o);
	}
	inline bool operator<(inf o){
		return this->diff(o)==-1;
	}
	inline bool operator>(inf o){
		return this->diff(o)==1;
	}
	inline bool operator==(inf o){
		return this->diff(o)==0;
	}
	inline bool operator<=(inf o){
		return this->diff(o)!=1;
	}
	inline bool operator>=(inf o){
		return this->diff(o)!=-1;
	}
	inline bool operator!=(inf o){
		return this->diff(o)!=0;
	}
	inline inf operator*(inf o){
		inf a;
		a.mod=mod*o.mod;
		a.sign=sign*o.sign;
		a.norm();
		return a;
	}
	inline inf operator/(inf o){
		inf a;
		a.sign=sign/o.sign;
		a.mod=mod/o.mod;
		a.norm();
		return a;
	}
	inline inf operator%(inf o){
		return *this-*this/o*o;
	}
	inline inf operator+=(inf o){
		inf a;
		a=*this+o;
		mod=a.mod;
		sign=a.sign;
		return a;
	}
	inline inf operator-=(inf o){
		inf a;
		a=*this-o;
		mod=a.mod;
		sign=a.sign;
		return a;
	}
	inline inf operator*=(inf o){
		inf a;
		a=*this*o;
		mod=a.mod;
		sign=a.sign;
		return a;
	}
	inline inf operator/=(inf o){
		inf a;
		a=*this/o;
		mod=a.mod;
		sign=a.sign;
		return a;
	}
	inline inf operator%=(inf o){
		inf a;
		a=*this%o;
		mod=a.mod;
		sign=a.sign;
		return a;
	}
	inline inf operator++(){
		*this+=1;
		return *this;
	}
	inline inf operator--(){
		*this-=1;
		return *this;
	}
	inline inf operator++(int32_t){
		inf a=*this;
		*this+=1;
		return a;
	}
	inline inf operator--(int32_t){
		inf a=*this;
		*this-=1;
		return a;
	}
	inline inf operator~(){
		inf a=*this;
		for (auto& o:mod.digits){
			o=~o;
		}
		return a;
	}
	inline inf operator!(){
		return inf(!sign);
	}
	inline inf operator<<(inf o){
		inf a=*this;
		if (o>0){
			a.mod=a.mod<<o.mod;
		}
		if (o<0){
			a.mod=a.mod>>o.mod;
		}
		return a;
	}
	inline inf operator>>(inf o){
		inf a=*this;
		if (o<0){
			a.mod=a.mod<<o.mod;
		}
		if (o>0){
			a.mod=a.mod>>o.mod;
		}
		return a;
	}
};
#ifdef replace_int
	using old_int = int;
	#define int inf
#endif

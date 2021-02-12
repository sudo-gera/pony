#define inf_included
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
//using namespace std;
//#define log(q) std::cout<<#q;for (auto gg:(q).digits){std::cout<<' '<<gg;}cout<<'\n';
struct inf{
	struct Zinf{
		struct Ninf{
			std::vector<uint32_t> digits;
			inline void norm(){
				while (digits.size() && digits[digits.size()-1]==0){
					digits.pop_back();
	struct Ninf{
		std::vector<uint32_t> digits;
		inline void norm(){
			while (digits.size() && digits[digits.size()-1]==0){
				digits.pop_back();
			}
		}
		explicit operator uint_least64_t(){
			uint_least64_t f=0;
			for (uint_least64_t i=0;i<digits.size() and i<sizeof(uint_least64_t)/sizeof(int32_t);i++){
				f+=(uint_least64_t)(digits[i])<<(sizeof(int32_t)*8*i);
			}
			return f;
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
			reverse(e.begin(), e.end());
			return e;
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
				for (int_least64_t t=digits.size()-1;t>=0;t--){
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
				while (digits.size()>=o.digits.size()){
					o=o<<(sizeof(int32_t)*8);
					c=c<<(sizeof(int32_t)*8);
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
			}
			inline Ninf operator<<(Ninf o){
				Ninf a=*this;
				Ninf r;
				uint32_t s;
				if(o.diff(sizeof(int32_t)*8)==-1){
					r=0;
				}else if(o.diff(sizeof(int32_t)*8*2)==-1){
					r=1;
				}else{
					r=o/(sizeof(int32_t)*8);
				}
				s=uint_least64_t(o.add(r*sizeof(int32_t)*8,-1));
				if(r.diff(digits.size())==1){
					r=digits.size();
				}
				auto dig=std::vector<uint32_t>();
				Ninf zero(0);
				dig.resize(dig.size()+uint_least64_t(r));
				dig.insert(dig.end(),a.digits.begin(), a.digits.end());
				a.digits=dig;
				a.digits.resize(a.digits.size()+1);
				uint_least64_t t=0;
				uint32_t y=0;
				for(auto d=a.digits.begin();d!=a.digits.end();d++){
					t=(uint_least64_t)(*d);
					t<<=s;
					*d=t;
					*d+=y;
					y=t>>(sizeof(int32_t)*8);
				}

				a.norm();
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
				}else{
					r=o/(sizeof(int32_t)*8);
				}
				s=uint_least64_t(o.add(r*sizeof(int32_t)*8,-1));
				if(r.diff(digits.size())==1){
					r=digits.size();
				}
				a.digits=std::vector<uint32_t>(a.digits.begin()+uint_least64_t(r),a.digits.end());
				uint_least64_t t=0;
				uint32_t y=0;
				for(auto d=a.digits.rbegin();d!=a.digits.rend();d++){
					t=(uint_least64_t)(*d)<<(sizeof(int32_t)*8);
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
			} else if(sign==0){
				mod=zero;
			}
		}
		inline int32_t diff(Zinf o){
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
		inline Zinf(std::string o){
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
		inline Zinf(){
			sign=0;
		};
		inline Zinf(int_least64_t o){
			sign=(!!o)*(o<0?-1:1);
			int32_t m=0;
			if (o==INT_MIN){
				m=1;
				o+=1;
			}
			if (o<0){
				o=-o;
			}
			Ninf t(o);
			mod=t;
			if (m){
				*this=add(*this,m,-1);
			}
		}
		friend inline Zinf add(Zinf s,Zinf o,int32_t d){
			o.sign*=d;
			Zinf a;
			if (s.sign==o.sign){
				a.mod=s.mod.add(o.mod,1);
				a.sign=s.sign;
			}
			else{
				int32_t d=s.mod.diff(o.mod);
				if (d==1){
					a.mod=s.mod.add(o.mod,-1);
					a.sign=s.sign;
				}else if (d==-1){
					a.mod=o.mod.add(s.mod,-1);
					a.sign=o.sign;
				}else{
					a=Zinf(0);
				}
			}
			return a;
		}
		friend inline Zinf operator-(Zinf s){
			s.sign*=-1;
			return s;
		}
		friend inline Zinf operator*(Zinf s,Zinf o){
			Zinf a;
			a.mod=s.mod*o.mod;
			a.sign=s.sign*o.sign;
			a.norm();
			return a;
		}
		friend inline Zinf operator/(Zinf s,Zinf o){
			Zinf a;
			a.sign=s.sign/o.sign;
			a.mod=s.mod/o.mod;
			a.norm();
			return a;
		}
		friend inline Zinf operator%(Zinf s,Zinf o){
			return add(s,s/o*o,-1);
		}
		friend inline Zinf shift(Zinf s,Zinf o){
			Zinf a=s;
			if (o.diff(0)>0){
				a.mod=a.mod>>o.mod;
			}
			if (o.diff(0)<0){
				a.mod=a.mod<<o.mod;
		inline Ninf operator/(Ninf o){
			Ninf t=*this;
			Ninf c=1;
			Ninf a=0;
			while (t.digits.size()>=o.digits.size()){
				o=o<<(sizeof(int32_t)*8);
				c=c<<(sizeof(int32_t)*8);
			}
			while (c.diff(0)){
				if (t.diff(o)>-1){
					t=t.add(o,-1);
					a=a.add(c,1);
				}
				c=c>>1;
				o=o>>1;
			}
			a.norm();
			return a;
		}
		friend inline Zinf operator&(Zinf s,Zinf o){
			Zinf a=s;
			while (a.mod.digits.size()>o.mod.digits.size()){
				o.mod.digits.push_back(0);
			}
			while (a.mod.digits.size()<o.mod.digits.size()){
				a.mod.digits.push_back(0);
			}
			for (uint_least64_t f=0;f<o.mod.digits.size();f++){
				a.mod.digits[f]&=o.mod.digits[f];
			}
			a.norm();
			return a;
		}
		friend inline Zinf operator^(Zinf s,Zinf o){
			Zinf a=s;
			while (a.mod.digits.size()>o.mod.digits.size()){
				o.mod.digits.push_back(0);
			}
			while (a.mod.digits.size()<o.mod.digits.size()){
				a.mod.digits.push_back(0);
			}
			for (uint_least64_t f=0;f<o.mod.digits.size();f++){
				a.mod.digits[f]^=o.mod.digits[f];
			}
			a.norm();
			return a;
		}
		friend inline Zinf operator|(Zinf s,Zinf o){
			Zinf a=s;
			while (a.mod.digits.size()>o.mod.digits.size()){
				o.mod.digits.push_back(0);
			}
			while (a.mod.digits.size()<o.mod.digits.size()){
				a.mod.digits.push_back(0);
			}
			for (uint_least64_t f=0;f<o.mod.digits.size();f++){
				a.mod.digits[f]|=o.mod.digits[f];
			}
			a.norm();
			return a;
		}
		friend inline Zinf operator&=(Zinf& s,Zinf o){
			s=s&o;
			auto a=s;
			return a;
		}
		friend inline Zinf operator^=(Zinf& s,Zinf o){
			s=s^o;
			auto a=s;
			return a;
		}
		friend inline Zinf operator|=(Zinf& s,Zinf o){
			s=s|o;
			auto a=s;
			return a;
		}
		friend inline Zinf operator>>=(Zinf& s,Zinf o){
			s=shift(s,o);
			auto a=s;
			return a;
		}
		friend inline Zinf operator<<=(Zinf& s,Zinf o){
			s=shift(s,-o);
			auto a=s;
			return a;
		}
	};
	int_least64_t sval;
	bool longer;
	Zinf lval;
	inline void norm(){
		if (LLONG_MIN<=lval and lval<=LLONG_MAX){
			sval=int_least64_t(lval);
			lval=0;
			longer=0;
		}
	}
	inline inf(): sval(0), longer(0), lval(0){}
	inline inf(int_least64_t a): sval(a), longer(0), lval(0){}
	inline inf(int_least64_t a,bool s,Zinf d): sval(a), longer(s), lval(d){}
	inline inf(Zinf d): sval(0), longer(0), lval(d){}
	inline inf(std::string o):sval(0), longer(0), lval(o){
		this->norm();
	}
	explicit inline operator Zinf(){
		return longer?lval:Zinf(sval);
	}
	explicit operator bool(){
		return longer?bool(lval.sign):bool(sval);
	}
	explicit operator std::string(){
		return longer?std::string(lval):std::to_string(sval);
	inline inf(){
		sign=0;
	};
	inline inf(int_least64_t o){
		sign=(!!o)*(o<0?-1:1);
/*		int32_t m=0;
		if (o==INT_MIN){
			m=1;
			o+=1;
		}
*/
		if (o<0){
			o=-o;
		}
		Ninf t(o);
		mod=t;
//		*this-=m;
	}
	friend inline inf inf(std::string o){
		inf a(o);
		return a;
>>>>>>> noboost
	}
	explicit operator int_least64_t(){
		return longer?int_least64_t(lval):sval;	
	}
	friend inline std::ostream& operator<<(std::ostream& os,inf i){
		os<<std::string(i);
		return os;
	}
	friend inline std::istream& operator>>(std::istream& is,inf&i){
		std::string o;
		is>>o;
		i=o;
		return is;
	}
	friend inline inf operator+(inf s){
		return s;
	}
	friend inline inf operator-(inf s){
		if (s.longer==0 and s.sval!=LLONG_MIN){
			s.sval= -s.sval;
		}else{
			s={0,1,-Zinf(s)};
		}
		s.norm();
		return s;
	}
	#define oper2(d,f)\
	friend inline inf d##= (inf& s,inf o);\
	friend inline inf d (inf s,inf o){return s f##= o;}\
	friend inline inf d##= (inf& s,inf o)

	#define oper1(d,f)\
	friend inline inf d (inf s)

	oper2(operator+,+){
		if (
			(s.longer==0 and o.longer==0) and
			(o.sval<0 or LLONG_MAX-o.sval>=s.sval) and
			(o.sval>0 or LLONG_MIN-o.sval<=s.sval))
		{
			s=s{s.sval+o.sval,0,0};
		}else{
			s={0,1,Zinf(s)+Zinf(o)};
		}
		s.norm();
		return s;
	}
	oper2(operator-,-){
		if (
			(s.longer==0 and o.longer==0) and
			(s.sval<0 or LLONG_MAX-s.sval>=-o.sval) and
			(s.sval>0 or LLONG_MIN-s.sval<=-o.sval))
		{
			s={s.sval-o.sval,0,0};
		}else{
			s={0,1,Zinf(s)-Zinf(o)};
		}
		s.norm();
		return s;
	}
	oper2(operator*,*){
		if (
			(s.longer==0 and o.longer==0) and
			(s.sval<0 or o.sval<0 or LLONG_MAX/s.sval>=o.sval) and
			(s.sval>0 or o.sval<0 or LLONG_MAX/(-s.sval)>=o.sval) and
			(s.sval<0 or o.sval>0 or LLONG_MAX/s.sval>=-o.sval) and
			(s.sval>0 or o.sval>0 || LLONG_MAX/s.sval<=o.sval))
		{
			s={s.sval*o.sval,0,0};
		}else{
			s={0,1,Zinf(s)*Zinf(o)};
		}
		s.norm();
		return s;
	}
	oper2(operator/,/){
		if (
			s.longer==0&&o.longer==0)
		{
			s={s.sval/o.sval,0,0};
		}else{
			s={0,1,Zinf(s)/Zinf(o)};
		}
		s.norm();
		return s;
	}
	oper2(operator%,%){
		if (
			s.longer==0&&o.longer==0)
		{
			s={s.sval%o.sval,0,0};
		}else{
			s={0,1,Zinf(s)%Zinf(o)};
		}
		s.norm();
		return s;
	}
	oper1(operator~,~){
		if (s.longer==0){
			s={~s.sval,0,0};
		}else{
			s={0,1,inf::Zinf(-1).add(s.lval,-1)};
		}
		s.norm();
		return s;
	}
	oper1(operator!,!){
		if (s.longer==0){
			s={!s.sval,0,0};
		}else{
			s={!s.lval.sign,0,0};
		}
		s.norm();
		return s;
	}
	oper2(operator<<,<<){
		s={0,1,shift(inf(s),-inf(o))};
		s.norm();
		return s;
	}
	oper2(operator>>,>>){
		if (s.longer==0 and o.longer==0){
			s={s.sval>>o.sval,0,0};
		}else{
			s={0,1,shift(inf(s),inf(o))};
		}
		s.norm();
		return s;
	}
	oper2(operator&,&){
		if (s.longer==0 and o.longer==0){
			s={s.sval&o.sval,0,0};
		}else{
			s={0,1,inf(s)&inf(o)};
		}
		s.norm();
		return s;
	}
	oper2(operator|,|){
		if (s.longer==0 and o.longer==0){
			s={s.sval&o.sval,0,0};
		}else{
			s={0,1,inf(s)&inf(o)};
		}
		s.norm();
		return s;
	}
	oper2(operator^,^){
		if (s.longer==0 and o.longer==0){
			s={s.sval&o.sval,0,0};
		}else{
			s={0,1,inf(s)&inf(o)};
		}
		s.norm();
		return s;
	}

	friend inline bool operator<(inf s,inf o){
		return
			s.longer==0&&o.longer==0?
				s.sval<o.sval
			:
				Zinf(s).diff(Zinf(o))==-1
		;
	}
	friend inline bool operator==(inf s,inf o){
		return
			s.longer==0&&o.longer==0?
				s.sval==o.sval
			:
				Zinf(s).diff(Zinf(o))==0
		;
	}
	friend inline bool operator>(inf s,inf o){
		return
			s.longer==0&&o.longer==0?
				s.sval>o.sval
			:
				Zinf(s).diff(Zinf(o))==1
		;
	}
	friend inline bool operator<=(inf s,inf o){
		return
			s.longer==0&&o.longer==0?
				s.sval<=o.sval
			:
				Zinf(s).diff(Zinf(o))<=0
		;
	}
	friend inline bool operator!=(inf s,inf o){
		return
			s.longer==0&&o.longer==0?
				s.sval!=o.sval
			:
				Zinf(s).diff(Zinf(o))!=0
		;
	}
	friend inline bool operator>=(inf s,inf o){
		return
			s.longer==0&&o.longer==0?
				s.sval>=o.sval
			:
				Zinf(s).diff(Zinf(o))>=0
		;
	}
	friend inline inf operator++(inf& s){
		return s+=1;
	}
	friend inline inf operator--(inf& s){
		return s-=1;
	}
	friend inline inf operator++(inf& s,int32_t){
		inf a=s;
		s+=1;
		return a;
	}
	friend inline Zinf operator--(inf& s,int32_t){
		Zinf a=s;
		s-=1;
		return a;
	}
	friend inline inf abs(inf s){
		if (s.longer and s.sval!=LLONG_MIN){
			s.sval=s.sval<0?-s.sval:s.sval;
		}else{
			s.lval=Zinf(s);
			s.lval=s.lval<0?-s.lval:s.lval;
		}
		s.norm();
		return s;
	}
};
#ifdef replace_int
	using old_int = int;
	#define int inf
#endif

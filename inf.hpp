#include <iostream>
#include <string>
#include <type_traits>

struct power;
class Rational;

class BigInteger{
	int8_t sign=0;
	size_t size=0;
	uint32_t *vect=nullptr;
public:
	BigInteger(){
	}
private:
	void resize(size_t q){
		if (size<q){
			auto tmp=new uint32_t[q]();
			for (size_t w=0;w<size;++w){
				tmp[w]=vect[w];
			}
			if (vect){
				delete[] vect;
			}
			vect=tmp;
			size=q;
		}
	}
public:
	BigInteger(const BigInteger& orig){
		resize(orig.size);
		size=orig.size;
		sign=orig.sign;
		for (size_t w=0;w<size;++w){
			vect[w]=orig.vect[w];
		}
	}
	BigInteger(__uint128_t orig){
		resize(4);
		sign=orig>0?1:0;
		vect[0]=reinterpret_cast<uint32_t*>(&orig)[0];
		vect[1]=reinterpret_cast<uint32_t*>(&orig)[1];
		vect[2]=reinterpret_cast<uint32_t*>(&orig)[2];
		vect[3]=reinterpret_cast<uint32_t*>(&orig)[3];
	}
	BigInteger(__int128_t orig){
		if (orig<0){
			*this=BigInteger(__uint128_t(-orig));
			sign=-1;
		}else{
			*this=BigInteger(__uint128_t(orig));
		}
	}
	template<typename T>
	BigInteger(T q){
		std::enable_if_t<(__int128_t(T()),true),T> g;
		*this=BigInteger(__int128_t(q));
	}
	BigInteger&operator=(const BigInteger&orig){
		if (vect==orig.vect){
			return *this;
		}
		resize(orig.size);
		sign=orig.sign;
		size_t w=0;
		for (;w<orig.size;++w){
			vect[w]=orig.vect[w];
		}
		for (;w<size;++w){
			vect[w]=0;
		}
		return *this;
	}
	BigInteger(const char*orig,int base=10){
		*this=BigInteger(static_cast<std::string>(orig),base);
	}
	std::string toString(uint64_t base=10)const{
		BigInteger abs_of_this=*this;
		abs_of_this.sign=bool(abs_of_this.sign);
		std::string res;
		while (abs_of_this.sign){
			uint64_t buff=0;
			uint64_t tmp=0;
			for (size_t w=abs_of_this.size;w>0;--w){
				tmp=abs_of_this.vect[w-1];
				tmp+=buff<<32;
				buff=tmp%base;
				tmp/=base;
				abs_of_this.vect[w-1]=tmp;
			}
			abs_of_this.sign=0;
			for (size_t _w=abs_of_this.size;_w>0;--_w){size_t w=_w-1;
				if (abs_of_this.vect[w]){
					abs_of_this.sign=1;
					break;
				}
			}
			res.push_back(buff);
		}
		auto code_to_symbol="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		//code_to_symbol[0] is '0', code_to_symbol[10] is 'A'
		for (size_t w=0;w<res.size();++w){
			res[w]=code_to_symbol[static_cast<int>(res[w])];
		}
		if (sign<0){
			res.push_back('-');
		}
		if (!res.size()){
			res.push_back('0');
		}
		for (size_t w=0;w*2<res.size();++w){
			char tmp=res[w];
			res[w]=res[res.size()-1-w];
			res[res.size()-1-w]=tmp;
		}
		return res;
	}
	std::string to_string(uint64_t base=10)const{
		return toString(base);
	}
	operator std::string()const{
		return this->toString();
	}
	int cmp(BigInteger const&e,bool onlymod=0)const{
		if (!onlymod and sign!=e.sign){
			return ((sign)-(e.sign));
		}
		if (size+e.size==0){
			return 0;
		}
		for (size_t c=(size>e.size?size:e.size);c--;){
			size_t qdigit=size>c?vect[c]:0;
			size_t edigit=e.size>c?e.vect[c]:0;
			if (qdigit!=edigit){
				return ((qdigit>edigit)*2-1)*(onlymod?1:sign);
			}
		}
		return 0;
	}
	~BigInteger(){
		if (vect){
			delete[] vect;
		}
	}
private:
	void bn_M_add_to(BigInteger const &e){
		size_t qs=size;
		if (qs and vect[qs-1]==0){
			qs-=1;
		}
		size_t es=e.size;
		if (es and e.vect[es-1]==0){
			es-=1;
		}
		qs=(qs>es?qs:es)+1;
		resize(qs);
		uint64_t buff=0;
		for (size_t w=0;w<qs;++w){
			buff+=vect[w];
			if (w<e.size){
				buff+=e.vect[w];
			}
			vect[w]=buff&0b11111111111111111111111111111111;
			buff>>=32;
		}
	}
	//helps in e has only 2 digits
	void bn_M_add_to_fast(BigInteger const &e,uint64_t start){
		size_t qs=size;
		if (qs and vect[qs-1]==0){
			qs-=1;
		}
		size_t es=e.size;
		if (es and e.vect[es-1]==0){
			es-=1;
		}
		qs=(qs>es?qs:es)+1;
		resize(qs);
		uint64_t buff=0;
		for (size_t w=start;w<qs;++w){
			buff+=vect[w];
			if (w<e.size){
				buff+=e.vect[w];
			}
			vect[w]=buff&0b11111111111111111111111111111111;
			buff>>=32;
			if (w>start and buff==0){
				break;
			}
		}
	}
	void bn_M_sub_to(BigInteger const &e){
		size_t qs=size;
		if (qs and vect[qs-1]==0){
			qs-=1;
		}
		size_t es=e.size;
		if (es and e.vect[es-1]==0){
			es-=1;
		}
		qs=(qs>es?qs:es)+1;
		resize(qs);
		int64_t buff=0;
		for (size_t w=0;w<qs;++w){
			buff+=vect[w];
			if (w<e.size){
				buff-=e.vect[w];
			}
			vect[w]=buff&0b11111111111111111111111111111111;
			buff>>=32;
		}
		size_t g=size;
		while (g>0 and vect[g-1]==0){
			g-=1;
		}
		if (g==0){
			sign=0;
		}	
	}
	//helps in e has only 2 digits
	void bn_M_sub_to_fast(BigInteger const &e,uint64_t start){
		size_t qs=size;
		if (qs and vect[qs-1]==0){
			qs-=1;
		}
		size_t es=e.size;
		if (es and e.vect[es-1]==0){
			es-=1;
		}
		qs=(qs>es?qs:es)+1;
		resize(qs);
		int64_t buff=0;
		for (size_t w=start;w<qs;++w){
			buff+=vect[w];
			if (w<e.size){
				buff-=e.vect[w];
			}
			vect[w]=buff&0b11111111111111111111111111111111;
			buff>>=32;
			if (w>start and buff==0){
				break;
			}
		}
		size_t g=size;
		while (g>0 and vect[g-1]==0){
			g-=1;
		}
		if (g==0){
			sign=0;
		}	
	}
public:
	BigInteger&operator+=(const BigInteger&e){
		if (!e.sign){
			return *this;
		}
		if (e.sign*sign>=0){
			bn_M_add_to(e);
			sign=e.sign;
		}else if (this->cmp(e,1)>=0){
			bn_M_sub_to(e);
		}else{
			BigInteger tmp=*this;
			*this=e;
			bn_M_sub_to(tmp);
		}
		size_t ts=size;
		while (ts>0 and vect[ts-1]==0){
			ts-=1;
		}
		if (ts==0){
			sign=0;
		}
		return *this;
	}
	BigInteger&operator-=(const BigInteger&e){
		sign*=-1;
		*this+=e;
		sign*=-1;
		return *this;
	}
	auto&operator*=(const BigInteger&e){
		BigInteger res;
		BigInteger tmp;
		size_t qs=size;
		size_t es=e.size;
		while (qs and vect[qs-1]==0){
			--qs;
		}
		while (es and e.vect[es-1]==0){
			--es;
		}
		res.resize(qs+es);
		tmp.resize(qs+es);
		tmp.sign=1;
		for (size_t w=0;w<qs;++w){
			if (vect[w]){
				for (size_t r=0;r<es;++r){
					uint64_t mulres=(uint64_t)(vect[w])*(uint64_t)(e.vect[r]);
					tmp.vect[w+r]=mulres<<32>>32;
					tmp.vect[w+r+1]=mulres>>32;
					res.bn_M_add_to_fast(tmp,w+r); 
					tmp.vect[w+r]=0;
					tmp.vect[w+r+1]=0;
				}
			}
		}
		res.sign=sign*e.sign;
		*this=res;
		return *this;
	}
private:
	void bn_half(){
		if (size){
			vect[0]>>=1;
		}
		for (size_t w=1;w<size;++w){
			vect[w-1]|=(vect[w]&1)<<31;
			vect[w]>>=1;
		}
		size_t not_zero=0;
		for (size_t w=0;w<size;++w){
			if (vect[w]){
				not_zero=1;
				break;
			}
		}
		if (!not_zero){
			sign=0;
		}
	}
	void bn_M_div_to(const BigInteger&e,bool getdiv=1){
		if(!e.sign){std::cerr<<"zero"<<std::flush;return;}
		auto rsign=sign*e.sign;
		sign=bool(sign); //q=abs(q)
		size_t qs=size;
		size_t es=e.size;
		while (qs and vect[qs-1]==0){
			--qs;
		}
		while (es and e.vect[es-1]==0){
			--es;
		}
		BigInteger res;
		if (qs>=es){
			BigInteger*shifted_e=new BigInteger[32];
			shifted_e[0].resize(qs+2);
			shifted_e[0].sign=1;
			for(size_t w=0;w<es;++w){
				shifted_e[0].vect[qs-es+2+w]=e.vect[w];
			}
			shifted_e[31]=shifted_e[0];
			shifted_e[31].bn_half();
			for (size_t w=31;w>1;--w){
				shifted_e[w-1]=shifted_e[w];
				shifted_e[w-1].bn_half();
			}
			uint64_t*offsets=new uint64_t[32]();
			res.resize(qs+1-es);
			int64_t shift=(res.size+1)*32;
			res.sign=1;
			while (shift>=0){
				if (this->cmp(shifted_e[shift&0b11111])>=0){
					res.vect[shift>>5]|=(1LL<<(shift&0b11111));
					bn_M_sub_to(shifted_e[shift&0b11111]);
				}
				shifted_e[shift&0b11111].size-=1;
				shifted_e[shift&0b11111].vect+=1;
				offsets[shift&0b11111]+=1;
				shift-=1;
			}
			size_t rs=res.size;
			while (rs and res.vect[rs-1]==0){
				--rs;
			}
			if (!rs){
				res.sign=0;
			}
			for (size_t w=0;w<32;++w){
				shifted_e[w].vect-=offsets[w];
			}
			delete[] offsets;
			delete[] shifted_e;
		}
		if (getdiv){
			*this=res;
		}
		sign=rsign;
		qs=size;
		while (qs>0 and vect[qs-1]==0){
			qs-=1;
		}
		if (qs==0){
			sign=0;
		}	
	}
public:
	auto&operator/=(const BigInteger&e){
		bn_M_div_to(e,1);
		return *this;
	}
	auto&operator%=(const BigInteger&e){
		bn_M_div_to(e,0);
		return *this;
	}
	auto&operator++(){
		if (this->sign<0){
			bn_M_sub_to_fast(1,0);
		}else{
			bn_M_add_to_fast(1,0);
		}
		return *this;
	}
	auto operator++(int){
		auto tmp=*this;
		++*this;
		return tmp;
	}
	auto&operator--(){
		if (this->sign<0){
			bn_M_add_to_fast(1,0);
		}else{
			bn_M_sub_to_fast(1,0);
		}
		return *this;
	}
	auto operator--(int){
		auto tmp=*this;
		--*this;
		return tmp;
	}
	auto operator-()const{
		BigInteger g=*this;
		g.sign*=-1;
		return g;
	}
	explicit operator bool(){
		return this->sign;
	}
	BigInteger(std::string orig,int64_t base=10){
		size_t start = 0 ;
		size_t stop = 0 ;
		auto isspace="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x01\x01\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x01\x01\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
		while (start+stop<orig.size() and isspace[int(orig[start+stop])]) {
			start++ ;
		}
		if (start+stop<orig.size() and orig[start+stop] == '-') {
			stop++ ;
		}
		auto symbol_to_code="------------------------------------------------\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09-------\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23------\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23-----";
		//string has \x00\x01... at positions '0','1',... and \x0a\x0b... at positions 'a','b',... and 'A','B',... symbol_to_code['0'] is 0, symbol_to_code['a'] is 10
		while (start+stop<orig.size() and uint64_t(symbol_to_code[int(orig[start+stop])]) < uint64_t(base)) {
			stop++ ;
		}
		orig=std::string(orig.begin()+start,orig.begin()+start+stop);
		resize(orig.size()/"\x00\x00\x20\x14\x10\x0d\x0c\x0b\x0a\x0a\x09\x09\x08\x08\x08\x08\x08\x07\x07\x07\x07\x07\x07\x07\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06"
			[base]+1); //optimal digit count, int(ln(2^32)/ln(base))
		sign=0;
		bool starts_with_minus_sign=0;
		if (orig.size() and orig[0]=='-'){
			starts_with_minus_sign=1;
		}
		for (size_t w=starts_with_minus_sign;w<orig.size();++w){
			*this*=base;
			*this+=symbol_to_code[static_cast<int>(orig[w])];  
		}
		if (starts_with_minus_sign){
			sign*=-1;
		}
	}
	void pow(uint64_t e) {
		BigInteger&q=*this;
		size_t s = 0 ;
		for (size_t w = 0 ; w < 64 ; ++w) {
			if ((1ULL << w)&e) {
				s = w+1 ;
			}
		}
		if(s) {
			BigInteger a[64];
			a[0]=q;
			for (size_t w = 1 ; w < s ; ++w) {
				a[w]=a[w-1] ;
				a[w]*=a[w];
			}
			q=1;
			for (size_t w = 0 ; w < s ; ++w) {
				if ((1 << w)&e) {
					q*=a[w];
				}
			}
		} else {
			q=1;
		}
	}
private:
	void bn_root2_to() {
		BigInteger&q=*this;
		BigInteger r,p,u;
		p.resize(q.size+1);
		p.vect[q.size]=1;
		p.sign=1;
		while(p.sign) {
			u=r;
			u+=p;
			if (q.cmp(u)>=0){
				q-=u;
				r+=p;
				r+=p;
			}
			r.bn_half();
			p.bn_half();
			p.bn_half();
		}
		q=r;
	}
public:
	void root(uint64_t e) {
		BigInteger&q=*this;
		if (e == 2) {
			bn_root2_to();
			return;
		}
		if (e == 1) {
			return;
		}
		BigInteger _b;
		BigInteger _e;
		_e . resize(q . size/e+1);
		_e . sign = 1 ;
		_e . vect[_e . size-1] = 1LL << 31 ;
		BigInteger _c;
		BigInteger _d;
		BigInteger _f;
		BigInteger _g=2;
		while (1) {
			_f=_e;
			_f-=_b;
			if (_f.cmp(_g) < 0) {
				break ;
			}
			_c=_b;
			_c+=_e;
			_c.bn_half();
			_d=_c;
			_d.pow(e);
			int j = _d.cmp(q) ;
			if (j < 0) {
				_b=_c;
			} else
			if (j > 0) {
				_e=_c;
			} else
			if (j == 0) {
				_e=_c;
				_b=_c;
			}
		}
		q=_b;
	}
	explicit operator __uint128_t()const{
		__uint128_t res=0;
		reinterpret_cast<uint32_t*>(&res)[0]=vect[0];
		reinterpret_cast<uint32_t*>(&res)[1]=vect[1];
		reinterpret_cast<uint32_t*>(&res)[2]=vect[2];
		reinterpret_cast<uint32_t*>(&res)[3]=vect[3];
		return res;
	}
	explicit operator __int128_t()const{
		return (__int128_t)(__uint128_t)(*this)*sign;
	}
	template <typename T>
	explicit operator T()const{
		return (T)(__int128_t)(*this);
	}
	power operator*();
	void pow(const Rational&q);
	void root(const Rational&q);
};


std::ostream&operator<<(std::ostream&ostr,const BigInteger&bn){
	ostr<<bn.toString();
	return ostr;
}
auto&operator>>(std::istream&istr,BigInteger&bn){
	std::string tmp;
	istr>>tmp;
	bn=tmp;
	return istr;
}
bool operator<(BigInteger const&q,BigInteger const&e){
	return q.cmp(e)<0;
}
bool operator>(BigInteger const&q,BigInteger const&e){
	return q.cmp(e)>0;
}
bool operator==(BigInteger const&q,BigInteger const&e){
	return q.cmp(e)==0;
}
bool operator!=(BigInteger const&q,BigInteger const&e){
	return q.cmp(e)!=0;
}
bool operator<=(BigInteger const&q,BigInteger const&e){
	return q.cmp(e)<=0;
}
bool operator>=(BigInteger const&q,BigInteger const&e){
	return q.cmp(e)>=0;
}
BigInteger operator+(const BigInteger&q,const BigInteger&w){
	auto tmp=q;
	tmp+=w;
	return tmp;
}
BigInteger operator-(const BigInteger&q,const BigInteger&w){
	auto tmp=q;
	tmp-=w;
	return tmp;
}
BigInteger operator*(const BigInteger&q,const BigInteger&w){
	auto tmp=q;
	tmp*=w;
	return tmp;
}
BigInteger operator/(const BigInteger&q,const BigInteger&w){
	auto tmp=q;
	tmp/=w;
	return tmp;
}
BigInteger operator%(const BigInteger&q,const BigInteger&w){
	auto tmp=q;
	tmp%=w;
	return tmp;
}


BigInteger operator""_bi(const char*orig){
	return BigInteger(orig);
}


BigInteger gcd(BigInteger q,BigInteger e){
	while (q and e){
		q%=e;
		if (q and e){
			e%=q;
		}
	}
	if (q){
		return q;
	}
	return e;
}


class Rational{
public:
	BigInteger numerator=0;
	BigInteger denominator=1;
private:
	void norm(){
		auto g=gcd(numerator,denominator);
		numerator/=g;
		denominator/=g;
		if (denominator<BigInteger(0)){
			numerator*=-1;
			denominator*=-1;
		}
	}
public:
	template<typename T>
	Rational(const T& q=0){
		numerator=q;
	}
	Rational(const BigInteger& q,const BigInteger& e){
		numerator=q;
		denominator=e;
		norm();
	}
	Rational(const std::string&orig,int base=10){
		auto slash_index=orig.find('/');
		if (slash_index==orig.npos){
			numerator=BigInteger(orig,base);
		}else{
			numerator=BigInteger(std::string(orig.begin(),orig.begin()+slash_index),base);
			denominator=BigInteger(std::string(orig.begin()+slash_index+1,orig.end()),base);
			norm();
		}
	}
	Rational(const char*a){
		*this=Rational(std::string(a));
	}
	auto&operator+=(const Rational&e){
		numerator*=e.denominator;
		numerator+=e.numerator*denominator;
		denominator*=e.denominator;
		norm();
		return *this;
	}
	auto&operator-=(const Rational&e){
		numerator*=e.denominator;
		numerator-=e.numerator*denominator;
		denominator*=e.denominator;
		norm();
		return *this;
	}
	auto&operator/=(const Rational&e){
		numerator*=e.denominator;
		denominator*=e.numerator;
		norm();
		return *this;
	}
	auto&operator*=(const Rational&e){
		numerator*=e.numerator;
		denominator*=e.denominator;
		norm();
		return *this;
	}
	auto operator-()const{
		return Rational(-numerator)/=denominator;
	}
	auto toString(uint64_t base=10)const{
		auto res=numerator.toString(base);
		if (denominator!=BigInteger(1)){
			res+="/"+denominator.toString(base);
		}
		return res;
	}
	operator std::string()const{
		return this->toString();
	}
	auto asDecimal(const size_t&p){
		auto tmp=numerator;
		auto tsign=tmp.cmp(0)<0?-1:1;
		tmp*=tsign;
		for (size_t w=0;w<p;++w){
			tmp*=10;
		}
		tmp/=denominator;
		auto res=tmp.toString();
		while (res.size()<p+1){
			res="0"+res;
		}
		res=std::string(res.begin(),res.end()-p)+"."+std::string(res.end()-p,res.end());
		if (tsign==-1){
			res="-"+res;
		}
		return res;
	}
	explicit operator double()const{
		return stold(numerator.toString())/stold(denominator.toString());
	}
	void pow(Rational e){
		if (e.numerator<0){
			e=-e;
			std::swap(numerator,denominator);
		}
		numerator.pow(uint64_t(e.numerator));
		denominator.pow(uint64_t(e.numerator));
		numerator.root(uint64_t(e.denominator));
		denominator.root(uint64_t(e.denominator));
		norm();
	}
	void root(const Rational&e){
		pow({e.denominator,e.numerator});
	}
	auto to_string()const{
		return toString();
	}
	power operator*();
};



auto operator+(const Rational&q,const Rational&e){
	auto tmp=q;
	tmp+=e;
	return tmp;
}
auto operator-(const Rational&q,const Rational&e){
	auto tmp=q;
	tmp-=e;
	return tmp;
}
auto operator*(const Rational&q,const Rational&e){
	auto tmp=q;
	tmp*=e;
	return tmp;
}
auto operator/(const Rational&q,const Rational&e){
	auto tmp=q;
	tmp/=e;
	return tmp;
}
bool operator<(const Rational&q,const Rational&e){
	return q.numerator*e.denominator<q.denominator*e.numerator;
}
bool operator>(const Rational&q,const Rational&e){
	return q.numerator*e.denominator>q.denominator*e.numerator;
}
bool operator==(const Rational&q,const Rational&e){
	return q.numerator*e.denominator==q.denominator*e.numerator;
}
bool operator<=(const Rational&q,const Rational&e){
	return q.numerator*e.denominator<=q.denominator*e.numerator;
}
bool operator!=(const Rational&q,const Rational&e){
	return q.numerator*e.denominator!=q.denominator*e.numerator;
}
bool operator>=(const Rational&q,const Rational&e){
	return q.numerator*e.denominator>=q.denominator*e.numerator;
}
std::ostream&operator<<(std::ostream&q,const Rational&w){
	q<<w.toString();
	return q;
}

using inf=BigInteger;
using Fraction=Rational;

struct power{
	Rational q;
};

Rational operator*(const Rational&q,const power&e){
	Rational w=q;
	w.pow(e.q);
	return w;
}
Rational operator*(const BigInteger&q,const power&e){
	Rational w=q;
	w.pow(e.q);
	return w;
}
Rational operator/(const Rational&q,const power&e){
	Rational w=q;
	w.root(e.q);
	return w;
}
Rational operator/(const BigInteger&q,const power&e){
	Rational w=q;
	w.root(e.q);
	return w;
}
std::string operator<<(const BigInteger&q,const power&e){
	return q.toString(uint64_t(e.q.numerator));
}
std::string operator<<(const Rational&q,const power&e){
	return q.toString(uint64_t(e.q.numerator));
}

power BigInteger::operator*(){
	return {*this};
}

power Rational::operator*(){
	return {*this};
}

void BigInteger::pow(const Rational&e){
	pow(e.numerator);
	root(e.denominator);
}

void BigInteger::root(const Rational&e){
	pow(e.denominator);
	root(e.numerator);
}

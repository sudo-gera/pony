#include <iostream>
#include <vector>
#include <map>
namespace json_ns{
	auto skip(const std::string&q,const std::string&w,size_t h=0,size_t c=1){
		while (h<q.size()){
			bool b=0;
			for (const auto&e:w){
				if (q[h]==e){
					b=1;
					break;
				}
			}
			if (!b){
				return h;
			}
			++h;
			if (h==c){
				return h;
			}
		}
		return h;
	}
	auto skip_whitespace(const std::string&q,size_t h=0){
		return skip(q,std::string({9, 10, 13, 32}),h,0);
	}
	auto skip_const(const std::string&q,size_t h=0){
		return skip(q,"truefalsenull",h,0);
	}
	auto skip_number(const std::string&q,size_t h=0){
		return skip(q,"-1234567890.eE",h,0);
	}
	auto skip_string(const std::string&q,size_t h=0){
		auto _h=skip(q,"\"",h);
		if (_h==h){
			return h;
		}
		h=_h;
		_h++;
		while (skip(q,"\"",h)==h and _h!=h){
			_h=h;
			if (skip(q,"\\",h)!=h){
				h+=2;
				h=h>=q.size()?q.size():h;
			}else{
				h+=1;
				h=h>=q.size()?q.size():h;
			}
		}
		h=skip(q,"\"",h,0);
		return h;
	}
	size_t skip_array(const std::string&q,size_t h);
	size_t skip_object(const std::string&q,size_t h);
	auto skip_value(const std::string&q,size_t h=0){
		h=skip_whitespace(q,h);
		h=skip_string(q,h);
		h=skip_number(q,h);
		h=skip_object(q,h);
		h=skip_array(q,h);
		h=skip_const(q,h);
		h=skip_whitespace(q,h);
		return h;
	}
	size_t skip_array(const std::string&q,size_t h=0){
		auto _h=skip(q,"[",h);
		if (_h==h){
			return h;
		}
		h=_h;
		_h++;
		while (skip(q,"]",h,1)==h and h!=_h){
			_h=h;
			h=skip_value(q,h);
			h=skip(q,",",h);
		}
		h=skip(q,"]",h,1);
		return h;
	}
	size_t skip_object(const std::string&q,size_t h=0){
		auto _h=skip(q,"{",h);
		if (_h==h){
			return h;
		}
		h=_h;
		_h++;
		while (skip(q,"}",h)==h and h!=_h){
			_h=h;
			h=skip_value(q,h);
			h=skip(q,":",h);
			h=skip_value(q,h);
			h=skip(q,",",h);
		}
		h=skip(q,"}",h);
		return h;
	}
	enum{
		json_const,json_number,json_string,json_array,json_object
	};
	struct json;
	json loads(const std::string&q);
	struct json{
		size_t type=0;
		size_t const_val=0;
		std::string number_val;
		#ifdef GMP_INCLUDED
		mpz_class int_val=0;
		#else
		long long int int_val=0;
		#endif
		long double float_val=0;
		size_t int_mode=0;
		std::string string_val;
		std::vector<json> array_val;
		std::map<std::string,json> object_val;
		friend json loads(const std::string&q);
	private:
		void _(const std::string&_q){
			size_t _qb=0;
			size_t _qe=_q.size();
			while (_qe and isspace(_q[_qe-1])){
				_qe--;
			}
			while (_qb<_qe and isspace(_q[_qb])){
				_qb++;
			}
			std::string q=std::string(_q.begin()+long(_qb),_q.begin()+long(_qe));
			if (skip(q,"ntf")){
				type=json_const;
				if (q[0]=='n'){
					const_val=2;
				}
				if (q[0]=='t'){
					const_val=1;
				}
				if (q[0]=='f'){
					const_val=0;
				}
			}else
			if (skip(q,"1234567890-")){
				type=json_number;
				// number_val=q;
				if (skip(q,"1234567890-",0,0)==q.size()){
					#ifdef GMP_INCLUDED
					int_val=q;
					#else
					int_val=stoll(q);
					#endif
					int_mode=1;
				}else{
					float_val=stold(q);
					int_mode=0;
				}
			}else
			if (skip(q,"\"")){
				type=json_string;
				auto h=skip(q,"\"");
				auto _h=h+1;
				while (skip(q,"\"",h)==h and _h!=h){
					_h=h;
					if (skip(q,"\\",h)!=h){
						h+=1;
						if (skip(q,"\"",h)!=h){
							string_val+="\"";
							h+=1;
						}else if (skip(q,"\\",h)!=h){
							string_val+="\\";
							h+=1;
						}else if (skip(q,"/",h)!=h){
							string_val+="/";
							h+=1;
						}else if (skip(q,"b",h)!=h){
							string_val+="\x08";
							h+=1;
						}else if (skip(q,"f",h)!=h){
							string_val+="\x0c";
							h+=1;
						}else if (skip(q,"n",h)!=h){
							string_val+="\n";
							h+=1;
						}else if (skip(q,"r",h)!=h){
							string_val+="\r";
							h+=1;
						}else if (skip(q,"t",h)!=h){
							string_val+="\t";
							h+=1;
						}else if (skip(q,"u",h)!=h and q.size()-h>4){
							int g;
							string_val+='\0';
							for (size_t f=0;f<4;++f){
								g=q[h+1+f];
								if ('0'<=g and g<='9'){
									g-='0';
								}
								if ('a'<=g and g<='f'){
									g-=int('a')-10;
								}
								if ('A'<=g and g<='F'){
									g-=int('A')-10;
								}
								string_val.back()*=16;
								string_val.back()+=g;
							}
							h+=5;
						}
					}else{
						string_val+=q[h];
						h+=1;
						h=h>=q.size()?q.size():h;
					}
				}
			}else
			if (skip(q,"[")){
				type=json_array;
				auto h=skip(q,"[");
				auto _h=h+1;
				while (h<q.size()-1 and h!=_h){
					_h=h;
					h=skip_value(q,h);
					array_val.push_back(loads(std::string(q.begin()+long(_h),q.begin()+long(h))));
					h=skip(q,",",h);
					h=skip_whitespace(q,h);
				}
			}else
			if (skip(q,"{")){
				type=json_object;
				auto h=skip(q,"{");
				auto _h=h+1;
				while (h<q.size()-1 and h!=_h){
					_h=h;
					h=skip_value(q,h);
					auto k=loads(std::string(q.begin()+long(_h),q.begin()+long(h)));
					h=skip(q,":",h);
					_h=h;
					h=skip_value(q,h);
					auto v=loads(std::string(q.begin()+long(_h),q.begin()+long(h)));
					h=skip(q,",",h);
					h=skip_whitespace(q,h);
					object_val[k]=v;
				}
			}
		}
	public:
		auto dumps(bool alnum=0)const{
			if (type==json_const){
				std::string h[3]={"false","true","null"};
				return h[const_val];
			}
			if (type==json_number){
				// return number_val;
				if (int_mode){
					#ifdef GMP_INCLUDED
					return int_val.get_str();
					#else
					return std::to_string(int_val);
					#endif
				}else{
					return std::to_string(float_val);
				}
			}
			if (type==json_string){
				auto res=std::string();
				res+='"';
				for (auto&w:string_val){
					if ((alnum==0 and (w<8 or w==11 or (13<w and w<32) or w==127)) or alnum==1){
						res+="\\u00";
						res+='0'+w/16;
						if ('0'+10<=res.back()){
							res.back()-='0'+10;
							res.back()+='a';
						}
						res+='0'+w%16;
						if ('0'+10<=res.back()){
							res.back()-='0'+10;
							res.back()+='a';
						}
					}else if(w>=32 and w!=34 and w!=92 and w!=127){
						res+=w;
					}else if (w==8){
						res+="\\b";
					}else if (w==9){
						res+="\\t";
					}else if (w==10){
						res+="\\n";
					}else if (w==12){
						res+="\\f";
					}else if (w==13){
						res+="\\r";
					}else if (w==34){
						res+="\\\"";
					}else if (w==92){
						res+="\\\\";
					}else{
						res+="error";
					}
				}
				res+='"';
				return res;
			}
			if (type==json_array){
				auto res=std::string();
				int c=0;
				res+="[";
				for (auto&w:array_val){
					if (c){
						res+=", ";
					}else{
						c=1;
					}
					res+=w.dumps();
				}
				res+="]";
				return res;
			}
			if (type==json_object){
				auto res=std::string();
				int c=0;
				res+="{";
				for (auto&w:object_val){
					if (c){
						res+=", ";
					}else{
						c=1;
					}
					res+=json(w.first).dumps();
					res+=": ";
					res+=w.second.dumps();
				}
				res+="}";
				return res;
			}
			return std::string("error ")+std::to_string(type);
		}
		operator std::string(){
			if (type==json_string){
				return string_val;
			}else{
				return this->dumps();
			}
		}
		template <typename T>
		operator T(){
			if (type==json_string){
				return stold(string_val);
			}
			if (int_mode){
				return T(int_val);
			}else{
				return T(float_val);
			}
		}
		template <typename T>
		operator std::vector<T>(){
			return std::vector<T>(array_val.begin(),array_val.end());
		}
		template <typename I,typename T>
		operator std::map<I,T>(){
			std::map<I,T> res;
			for (auto&w:object_val){
				res[json(w.first)]=T(w.second);
			}
			return res;
		}
		json&operator[](uint64_t q){
			return array_val[q];
		}
		json&operator[](std::string q){
			return object_val[q];
		}
		void __init__(const long long int&q){
			type=json_number;
			int_mode=1;
			#ifdef GMP_INCLUDED
			int_val=std::to_string(q);
			#else
			int_val=q;
			#endif
		}
		#ifdef GMP_INCLUDED
		void __init__(const mpz_class&q){
			type=json_number;
			int_mode=1;
			int_val=q;
		}
		#endif
		void __init__(const long int&q){
			type=json_number;
			int_mode=1;
			int_val=q;
		}
		void __init__(const int&q){
			type=json_number;
			int_mode=1;
			int_val=q;
		}
		void __init__(unsigned const long long int&q){
			type=json_number;
			int_mode=1;
			#ifdef GMP_INCLUDED
			int_val=std::to_string(q);
			#else
			int_val=decltype(int_val)(q);
			#endif
		}
		void __init__(unsigned const long int&q){
			type=json_number;
			int_mode=1;
			int_val=decltype(int_val)(q);
		}
		void __init__(unsigned const int&q){
			type=json_number;
			int_mode=1;
			int_val=decltype(int_val)(q);
		}
		void __init__(const bool&q){
			type=json_const;
			const_val=q;
		}
		void __init__(){
			type=json_const;
			const_val=2;
		}
		void __init__(const long double&q){
			type=json_number;
			int_mode=0;
			float_val=q;
		}
		void __init__(const std::string&q){
			type=json_string;
			string_val=q;
		}
		void __init__(const char*q){
			type=json_string;
			string_val=q;
		}
		template<typename T>
		void __init__(const std::vector<T>&q){
			type=json_array;
			for (auto&w:q){
				array_val.push_back(w);
			}
		}
		template<typename I,typename T>
		void __init__(const std::map<I,T>&q){
			type=json_object;
			for (auto&w:q){
				object_val[std::to_string(w.first)]=w.second;
			}
		}
		template <typename...T>
		json(const T&...q){
			this->__init__(q...);
		}
		void clear(){
			type=json_const;
			const_val=2;
			int_val=0;
			float_val=0;
			int_mode=0;
			string_val.clear();
			array_val.clear();
			object_val.clear();
		}
		template <typename T>
		json&operator=(const T&q){
			this->clear();
			this->__init__(q);
			return *this;
		}
		friend auto&operator<<(std::ostream&q,const json&w){
			q<<w.dumps();
			return q;
		}
		std::string json_type(){
			return std::vector({"json_const","json_number","json_string","json_array","json_object"})[type];
		}

	};
	json loads(const std::string&q){
		// std::stringstream d;
		auto h=json();
		h._(q);
		return h;
	}
	template <typename T>
	auto dumps(const T&a){
		return json(a).dumps();
	}
	template <typename T>
	auto alnumdumps(const T&a){
		return json(a).dumps(1);
	}
}

using json_ns::json;
using json_ns::loads;
using json_ns::dumps;
using json_ns::alnumdumps;


// int main(){
// 	print(json_ns::loads(" { \" 1 \" : 2 , \" 4 \" : [ 1 , true , 2 , false , 9 , \" \\\" \"] } "));
// 	// auto h=(json_ns::loads(" { \" 1 \" : 2 , \" 4 \" : [ 1 , true , 2 , false , 9 , \" \\\" \"] } "));
// }


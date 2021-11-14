auto jsondumps(const std::string&q){
	std::string s="\"";
	for (auto w:q){
		s+=std::vector({"\\u0000","\\u0001","\\u0002","\\u0003","\\u0004","\\u0005","\\u0006","\\u0007","\\b","\\t","\\n","\\u000b","\\f","\\r","\\u000e","\\u000f","\\u0010","\\u0011","\\u0012","\\u0013","\\u0014","\\u0015","\\u0016","\\u0017","\\u0018","\\u0019","\\u001a","\\u001b","\\u001c","\\u001d","\\u001e","\\u001f"," ","!","\"","#","$","%","&","\'","(",")","*","+",",","-",".","/","0","1","2","3","4","5","6","7","8","9",":",";","<","=",">","?","@","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","[","\\\\","]","^","_","`","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","{","|","}","~","\\u007f"})[w];
	}
	s+="\"";
	return s;
}

auto jsondumps(const char* _q){
	std::string s="\"",q=_q;
	for (auto w:q){
		s+=std::vector({"\\u0000","\\u0001","\\u0002","\\u0003","\\u0004","\\u0005","\\u0006","\\u0007","\\b","\\t","\\n","\\u000b","\\f","\\r","\\u000e","\\u000f","\\u0010","\\u0011","\\u0012","\\u0013","\\u0014","\\u0015","\\u0016","\\u0017","\\u0018","\\u0019","\\u001a","\\u001b","\\u001c","\\u001d","\\u001e","\\u001f"," ","!","\"","#","$","%","&","\'","(",")","*","+",",","-",".","/","0","1","2","3","4","5","6","7","8","9",":",";","<","=",">","?","@","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","[","\\\\","]","^","_","`","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","{","|","}","~","\\u007f"})[w];
	}
	s+="\"";
	return s;
}

auto jsondumps(const bool&a){
	std::stringstream c;
	c<<(a?"True":"False");
	return c.str();
}

auto jsondumps(const int64_t&a){
	std::stringstream c;
	c<<a;
	return c.str();
}

auto jsondumps(const int&a){
	std::stringstream c;
	c<<a;
	return c.str();
}

auto jsondumps(const long double&a){
	std::stringstream c;
	c<<a;
	auto s=c.str();
	if (s.find('.')==s.size()){
		s+=".0";
	}
	return s;
}

auto jsondumps(const double&a){
	std::stringstream c;
	c<<a;
	auto s=c.str();
	if (s.find(".")==s.npos){
		s+=".0";
	}
	return s;
}


template <typename T>
auto jsondumps(const std::vector<T>&a){
	std::stringstream _c;
	_c<<"[";
	int c=0;
	for (auto &w:a){
		if (c){
			_c<<", ";
		}else{
			++c;
		}
		_c<<jsondumps(w);
	}
	_c<<"]";
	return _c.str();
}

template <typename T1,typename T2>
auto jsondumps(const std::map<T1,T2>&a){
	std::stringstream _c;
	_c<<"{";
	int c=0;
	for (auto &w:a){
		if (c){
			_c<<", ";
		}else{
			++c;
		}
		_c<<jsondumps(print_one(w.first));
		_c<<": ";
		_c<<jsondumps(w.second);		
	}
	_c<<"}";
	return _c.str();
}

struct json{
	std::string data;
	std::string suff;
	json(std::string q):data(q){};
	auto get_json(){
		auto h=python(
"\
from json import *\n\
suff='"+suff+"'\n\
json='"+data+"'\n\
json=loads(json)\n\
json=json"+suff+"\n\
from sys import stderr\n\
print(json)\
");
		h=strip(h);
		return h;
	}
	operator int64_t(){
		auto h=get_json();
		return stol(h);
	}
	operator std::string(){
		auto h=get_json();
		return h;
	}
	friend auto&operator<<(std::ostream&q,const json&f){
		auto h=python(
"\
from json import *\n\
suff='"+f.suff+"'\n\
json='"+f.data+"'\n\
json=loads(json)\n\
json=json"+f.suff+"\n\
from sys import stderr\n\
print(json)\
");
		h=strip(h);
		q<<h;
		return q;		
	}
	template <typename T>
	json operator[](T q){
		json f(*this);
		f.suff+="["+jsondumps(q)+"]";
		return f;
	}
 	auto size()const{
		auto h=python(
"\
from json import *\n\
suff='"+suff+"'\n\
json='"+data+"'\n\
json=loads(json)\n\
json=json"+suff+"\n\
from sys import stderr\n\
print(len(json))\
");
		h=strip(h);
		return stol(h);
 	}
 	auto keys(){
		auto h=python(
"\
from json import *\n\
suff='"+suff+"'\n\
json='"+data+"'\n\
json=loads(json)\n\
json=json"+suff+"\n\
from sys import stderr\n\
print(len(json))\
");
		h=strip(h);
		auto l=stol(h);
		auto res=std::vector<std::string>();
		for (auto w:range(l)){
			auto h=python(
"\
from json import *\n\
suff='"+suff+"'\n\
json='"+data+"'\n\
json=loads(json)\n\
json=json"+suff+"\n\
from sys import stderr\n\
print(sorted(list(json.keys()))["+std::to_string(w)+"])\
");
			h=strip(h);
			res.push_back(h);
		}
		return res;
 	}
};
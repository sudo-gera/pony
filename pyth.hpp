using namespace std::literals;

std::string popen(std::string q){
	std::string s;
	auto pipe=popen(q.c_str(), "r");
	int c; // note: int, not char, required to handle EOF
	while ((c = fgetc(pipe)) != EOF) { // standard C I/O file reading loop
		s+=static_cast<char>(c);
	}
	pclose(pipe);
	return s;
}

std::string python(std::string q){
	q=replace(q,"\\"s,"\\\\"s);
	q=replace(q,"\""s,"\\\""s);
	q=replace(q,"`"s,"\\`"s);
	q=replace(q,"$"s,"\\$"s);
	return popen("python3 -c \""+q+"\"");
}


auto readfile(FILE*q){
	std::string s;
	int c; // note: int, not char, required to handle EOF
	while ((c = fgetc(q)) != EOF) { // standard C I/O file reading loop
		s+=static_cast<char>(c);
	}
	return s;
}

auto readfilename(std::string q){
	FILE*g=fopen(q.c_str(),"r");
	if (!g){
		ic("file does not excists:",q)
	}
	auto a=readfile(g);
	fclose(g);
	return a;
}

struct pyfunc_s{
	std::string f;
	std::string q;
	auto&operator=(const std::string&_q){
		f="def pyfunc("+f+"):\n"+_q;
		return *this;
	}
	pyfunc_s(std::string _f):f(_f){}
	template <typename...T>
	auto operator()(const T&...a){
		q="from json import *\nprint(dumps(pyfunc(";
		std::vector<int>({add(a)...});
		q+=")))";
		auto code=f+"\n\n"+q+"\n\n";
		q=code;
		q="from json import *\nexec(loads("+alnumdumps(dumps(code))+"))\n";
		return loads(python(q));
	}
	template<typename T>
	int add(const T&w){
		q+="loads("+dumps(dumps(w))+"),";
		return 0;
	}
};


pyfunc_s py_import(str cf,str file,str name){
	while (cf.size() and cf.end()[-1]!='/'){
		cf=str(cf.begin(),cf.end()-1);
	}
	if (file.find('/')==file.npos){
		file=cf+file;
	}
	if (file.size()<3 or not (file.end()[-3]=='.' and file.end()[-2]=='p' and file.end()[-1]=='y')){
		file+=".py";
	}
	// auto r=dumps(dumps(readfilename(file)+"\n\n__args__array.append("+name+")\n"));
	return pyfunc_s("*__args__args")=
	"	from json import loads,dumps\n"
	"	from sys import stderr,path\n"
	"	from os.path import dirname\n"
	"	q=("+alnumdumps(dumps(file))+")\n"
	"	q=loads(q)\n"
	"	path.append(dirname(q))\n"
	"	q=q[len(dirname(q)):-3]\n"
	"	if q[0]=='/': q=q[1:]\n"
	"	f=__import__(q)\n"
	"	f=f."+name+"\n"
	"	return f(*__args__args)\n";
}
#define import(f,...) auto f=py_import(__FILE__,#__VA_ARGS__,#f);

str fields_db="{}";

import(py_get_fields,get_fields)
std::vector<str> get_fields(str type){
	auto z=std::map<str,std::vector<str>>(loads(fields_db));
	if (!z.count(type)){
		auto h= py_get_fields(fields_db,running_file_path,type);
		fields_db=str(h);
	}
	z=std::map<str,std::vector<str>>(loads(fields_db));
	return z[type];
}

#define py_func(name) auto name = __LINE__ *= #name *= __py_func

#define __py_func(...) (__py_func_s{.name="",.code=#__VA_ARGS__,.line=__LINE__,.file=__FILE__,.line1=0});

struct __py_func_s{
	str name;
	str code;
	uint64_t line=0;
	str file;
	uint64_t line1=0;
};

auto pyfunc_create(str name,str code,size_t line,str file,size_t line1){
	auto s=pyfunc_s("code,line,file,line1")=
	"	from sys import stderr\n"
	"	from re import findall,split\n"
	"	s=open(file).read().split('\\n')\n"
	"	s='\\n'.join(s[line1:line-1])\n"
	"	a=s[:len(s)-len(s.lstrip())]\n"
	"	s=s[len(a):]\n"
	"	a=a[::-1]\n"
	"	a=a[:(a+'\\n').index('\\n')]\n"
	"	a=a[::-1]\n"
	"	s=a+s\n"
	"	s=s.rstrip()\n"
	"	s=s.splitlines()\n"
	"	s=[w for w in s if w.strip()]\n"
	"	s=[[w.index(w.lstrip()),w.lstrip()] for w in s]\n"
	"	m=min(list(zip(*s))[0])\n"
	"	s=[[w[0]-m+1,w[1]] for w in s]\n"
	"	s=['\\t'*w[0]+w[1] for w in s]\n"
	"	s='\\n'.join(s)\n"
	"	s+='\\n\\n\\treturn "+name+"(*__args__args)\\n'\n"
	"	return s\n";
	str d=s(code,line,file,line1);
	return pyfunc_s("*__args__args")=d;
}

auto operator*=(str a,__py_func_s s){
	s.name=a;
	return s;
}

auto operator*=(uint64_t a,__py_func_s s){
	return pyfunc_create(s.name,s.code,s.line,s.file,a);
}


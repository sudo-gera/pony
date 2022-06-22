#include <string>
// template <typename T>
// std::string strtype(const T&q){
// 	std::string s;
// 	s+="c++filt -t ";
// 	s+=typeid(q).name();
// 	FILE* pipe = popen(s.c_str(), "r");
// 	s="";
// 	int c= fgetc(pipe);
// 	while (c != EOF) {
// 		s.push_back(static_cast<char>(c));
// 		c = fgetc(pipe);
// 	}
// 	pclose(pipe);
// 	while ( s.size() and isspace(s.back()) ){
// 		s.pop_back();
// 	}
// 	return s;
// }

// template <typename T>
// std::string strtype(){
// 	return strtype(T());
// }

// usage:
	// std::cout << strtype(-1) << std::endl;

template <typename T>
std::string strtype() {
	std::string a=__PRETTY_FUNCTION__;
	return std::string(a.begin()+27,a.end()-1);
}

template <typename T>
std::string strtype(const T&q) {
	return strtype<T>();
}

template <typename T>
std::string wstrtype() {
	return strtype<T>();
	sprintf(0,"%i");
}

template <typename T>
std::string wstrtype(const T&q) {
	return wstrtype<T>();
}


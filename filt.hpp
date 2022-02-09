#include <string>
template <typename T>
std::string type(const T&q){
	std::string s;
	s+="c++filt -t ";
	s+=typeid(q).name();
	FILE* pipe = popen(s.c_str(), "r");
	s="";
	int c= fgetc(pipe);
	while (c != EOF) {
		s.push_back(static_cast<char>(c));
		c = fgetc(pipe);
	}
	pclose(pipe);
	while ( s.size() and isspace(s.back()) ){
		s.pop_back();
	}
	return s;
}

template <typename T>
std::string type(){
	return type(T());
}

// usage:
	// std::cout << type(-1) << std::endl;

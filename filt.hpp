#include <string>
template <typename T>
std::string type(const T&q=T()){
	std::string s;
	FILE* pipe = popen((std::string("c++filt -t ")+typeid(q).name()).c_str(), "r");
	while (!feof(pipe)) {
		s+='\n';
		fscanf(pipe,"%c",&(s[s.size()-1]));
	}
	pclose(pipe);
	while (s.size() and s[s.size()-1]=='\n'){
		s=std::string(s.begin(),s.end()-1);
	}
	return s;
}


#include "/Users/gera/pony/pony.hpp"
using namespace std;
def1(tobin,f){
	let q=int32_t(f);
	let res=str();
	let c=int(0);
	for w in range(int(sizeof(q)*8-1),int(-1),int(-1)) do{
		if c++%8==0 and c!=1 do{
			res+=str(" ");
		}
		res+=str(!!(q&(1<<w)));
	}
	return res;
}




pony_run{
	print(49L);
	print(int8_t(49));
	print(int16_t(49));
	print(int32_t(49));
	print(int64_t(49));
	print(char(49));
	print(char16_t(49));
	print(char32_t(49));
	print(bool(49));

}
#include "/Users/gera/pony/pony.hpp"
using namespace std;
def1(tobin,q){
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
	let q=int(4036005256);
	print(tobin(q));
	print(tobin(ord(q)));
/*	let a=str("абвг");
	let d=int();
	for w in a do{
		write(tobin(w),' ');
		if d do{
			print();
		}
		d=1-d;
	}
	print();
*/}
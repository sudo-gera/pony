#include "pony.hpp"
pony_wakeup

pony_run{
	let s=vector<int>({1,2,3,4,5,6,7,8,9});;
	let f=frag(s,2,-2);
	for w in f do{
		cout<<w;
	}
	for w in s do{
		cout<<w;
	}
}
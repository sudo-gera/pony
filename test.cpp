#include "pony.hpp"
pony_wakeup

def1(eiler_func,f){
	let res=f;
	let p=2;
	if f%p==0 do{
		res=res*(p-1)/p;
		while f%p==0 do{
			f/=p;
		}
	}
	p=3;
	while p*p<=f do{
		if f%p==0 do{
			res=res*(p-1)/p;
			while f%p==0 do{
				f/=p;
			}
		}
		p+=2;
	}
	if f>1 do{
		p=f;
		if f%p==0 do{
			res=res*(p-1)/p;
			while f%p==0 do{
				f/=p;
			}
		}
	}
	return res;
}


pony_run{
	print(eiler_func(scan(int)))
}
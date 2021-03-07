#include "pony.hpp"
pony_wakeup

def2(a,m,n){
	if m==0 do{
		return n+1;
	}
	if n==0 do{
		return a(m-1,1);
	}
	return a(m-1,a(m,n-1));

}

pony_run{
	print(a(scan(int),scan(int)))
}
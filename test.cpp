<<<<<<< HEAD
<<<<<<< HEAD
#include "inf.hpp"
//#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main(){
	auto d=inf(3)<<inf(4);
	cout<<int64_t(d);
}
=======
>>>>>>> 66e3ba6e09122b8dcf3e8d54114571db7e68aca8
#include "pony.hpp"
pony_wakeup
#pragma GCC optimize("Ofast")

pony_run{
	let s=inf::Zinf("1234567890987654321"),d=inf::Zinf("1234567890987654321");
	cout<<inf::Zinf(s+d);
=======
#include "inf.hpp"
using namespace std;
inf gcd(inf a,inf s){
	return a!=0?gcd(s%a,a):s;
>>>>>>> noboost
}

int main(){
	inf g,h;
	cin>>g>>h;
	cout<<gcd(g,h);
}
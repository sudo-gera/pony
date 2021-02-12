#include "inf.hpp"
using namespace std;
inf gcd(inf a,inf s){
	return a!=0?gcd(s%a,a):s;
}

int main(){
	inf g,h;
	cin>>g>>h;
	cout<<gcd(g,h);
}
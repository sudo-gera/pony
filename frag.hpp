#define stl(a) a.begin(),a.end()
template <typename T>
auto frag(T a,int_least64_t s=0,int_least64_t d=0){
	auto f=a.size();
	if (s>f){
		s=f;
	}
	if (s<0){
		s+=f;
	}
	if (s<0){
		s=0;
	}
	if (d<-f){
		d=-f;
	}
	if (d>0){
		d-=f;
	}
	if (d>0){
		d=0;
	}
	return decltype(a)(a.begin()+s,a.end()-s);
}
void* begin_end_stored=new bool;
template <typename T>
void* begin_end_store(T q){
//	delete begin_end_stored;
	begin_end_stored=new T;
	(*((T*)(begin_end_stored)))=q;
	return begin_end_stored;
}
#define stl(a) (*((decltype(a)*)(begin_end_store(a)))).begin(),(*((decltype(a)*)(begin_end_stored))).end()
template<typename T>
struct iterable_c{
	T b,e;
	T begin(){
		return b;
	}
	T end(){
		return e;
	}
};
template<typename T>
iterable_c<T> iterable(T b,T e){
	return iterable_c<T>({b,e});
}
template <typename T>
T frag(T a,int64_t s=0,int64_t d=(1LL<<63)){
	int64_t f=a.size();
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
	d+=f;
	int64_t g=0;
	auto h=decltype(a)();
	for (auto j:a){
		if (s<=g and g<d){
			h.push_back(j);
		}
		++g;
	}
	return h;
}
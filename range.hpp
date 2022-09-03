#include <vector>
// // template <typename int64_t>
// struct range_struct{
// 	struct range_iterator{
// 		int64_t val, step;
// 		range_iterator(int64_t v,int64_t s){
// 			val=v;
// 			step=s;
// 		}
// 		bool operator!=(range_iterator o){
// 			if (step>0 and val>=o.val){
// 				return false;
// 			}
// 			if (step<0 and val<=o.val){
// 				return false;
// 			}
// 			if (step==0 and val==o.val){
// 				return false;
// 			}
// 			return true;
// 		}
// 		void operator++(){
// 			val+=step;
// 		}
// 		int64_t operator*(){
// 			return val;
// 		}
// 	};
// 	int64_t start, stop, step;
// 	range_iterator begin(){
// 		range_iterator r(start,step);
// 		return r;
// 	}
// 	range_iterator end(){
// 		range_iterator r(stop,step);
// 		return r;
// 	}
// };
// // template <typename int64_t>
// 	range_struct range(int64_t a,int64_t o,int64_t e){
// 		range_struct r;
// 		r.start=a;
// 		r.stop=o;
// 		r.step=e;
// 		return r;
// 	}
// // template <typename int64_t>
// 	range_struct range(int64_t a,int64_t o){
// 		range_struct r;
// 		r.start=a;
// 		r.stop=o;
// 		r.step=1;
// 		return r;
// 	}
// // template <typename int64_t>
// 	range_struct range(int64_t o){
// 		range_struct r;
// 		r.start=0;
// 		r.stop=o;
// 		r.step=1;
// 		return r;
// 	}

auto range(int64_t w){
	int64_t q=0,e=1;
	std::vector<int64_t> r;
	for (auto t=q;(e<0 or t<w) and (e>0 or t>w);t+=e){
		r.push_back(t);
	}
	return r;
}
auto range(int64_t q,int64_t w,int64_t e=1){
	std::vector<int64_t> r;
	for (auto t=q;(e<0 or t<w) and (e>0 or t>w);t+=e){
		r.push_back(t);
	}
	return r;
}

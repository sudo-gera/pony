template <typename T>
struct range_struct{
	struct range_iterator{
		T val, step;
		inline range_iterator(T v,T s){
			val=v;
			step=s;
		}
		inline bool operator!=(range_iterator o){
			if (step>0 and val>=o.val){
				return false;
			}
			if (step<0 and val<=o.val){
				return false;
			}
			if (step==0 and val==o.val){
				return false;
			}
			return true;
		}
		inline void operator++(){
			val+=step;
		}
		inline T operator*(){
			return val;
		}
	};
	T start, stop, step;
	inline range_iterator begin(){
		range_iterator r(start,step);
		return r;
	}
	inline range_iterator end(){
		range_iterator r(stop,step);
		return r;
	}
};
template <typename Y>
	inline range_struct<Y> range(Y a,Y o,Y e){
		range_struct<Y> r;
		r.start=a;
		r.stop=o;
		r.step=e;
		return r;
	}
template <typename Y>
	inline range_struct<Y> range(Y a,Y o){
		range_struct<Y> r;
		r.start=a;
		r.stop=o;
		r.step=1;
		return r;
	}
template <typename Y>
	inline range_struct<Y> range(Y o){
		range_struct<Y> r;
		r.start=0;
		r.stop=o;
		r.step=1;
		return r;
	}

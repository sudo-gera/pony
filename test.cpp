pony_run{
	let a=vect(1,2,3,4,5);
	a=filter(a,w,w%2);
	a=each(a,w,w*w);
//	let h=vector<int>(a.begin(), a.end());
	print(a);
}
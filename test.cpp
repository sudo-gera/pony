def1(tobin,f){
	let q=int32_t(f);
	let res=str();
	let c=int(0);
	for w in range(int(sizeof(q)*8-1),int(-1),int(-1)) do{
		if c++%8==0 and c!=1 do{
			res+=str(" ");
		}
		res+=str(!!(q&(1<<w)));
	}
	return res;
}




pony_run{
	print(1)
	print(1L)
	print(1LL)

}
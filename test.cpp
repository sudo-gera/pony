def1(tobin,q){
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
	let q=int(4036005256);
}
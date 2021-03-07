#include "pony.hpp"
pony_wakeup

def2(al,m,n){
	if m==0 do{
		return n+1;
	}
	if n==0 do{
		return al(m-1,1);
	}
	return al(m-1,al(m,n-1));
}


struct aco{
	int m,n;
	int use,uc;
	int r;
	int saved;
	aco(int _m,int _n,int _use=-1,int _uc=0){
		m=_m;
		n=_n;
		use=_use;
		uc=_uc;
		r=-1;
		saved=-1;
	}
	friend ostream& operator<<(ostream& a,aco t){
		a<<"\x1b[31m"<<t.m<<" "<<t.n<<"\x1b[32m "<<t.use<<" "<<t.uc<<"\x1b[33m "<<t.r<<t.saved<<"\x1b[0m\t`";
		return a;
	}
};

def2(a,m,n){
	let st=vect(aco(m,n));
	let po=0;
	while po<len(st) do{
/*		for w in st do{
			cout<<w<<"; ";
		}
		cout<<'\n';
*/		if st[po].m==0 do{
			st[po].r=st[po].n+1;
		}elif st[po].n==0 do{
			if st[po].uc==0 do{
				let cs=len(st);
				st.append(aco(st[po].m-1,1));
				st.append(aco(st[po].m,st[po].n,cs,1));
				st[po].saved=cs+1;
			}else{
				while st[st[po].use].saved!=-1 do{
					st[po].use=st[st[po].use].saved;
				}
				if st[st[po].use].r==-1 do{
					let cs=len(st);
					st.append(aco(st[po].m,st[po].n,st[po].use,st[po].uc));
					st[po].saved=cs;
				}else{
					st[po].r=st[st[po].use].r;
				}
			}
		}else{
			if st[po].uc==0 do{
				let cs=len(st);
				st.append(aco(st[po].m,st[po].n-1));
				st.append(aco(st[po].m,st[po].n,cs,1));
				st[po].saved=cs+1;
			}elif st[po].uc==1 do{
				let cs=len(st);
				while st[st[po].use].saved!=-1 do{
					st[po].use=st[st[po].use].saved;
				}
				if st[st[po].use].r==-1 do{
					let cs=len(st);
					st.append(aco(st[po].m,st[po].n,st[po].use,st[po].uc));
					st[po].saved=cs;
				}else{
					let cs=len(st);
					st.append(aco(st[po].m-1,st[st[po].use].r));
					st.append(aco(st[po].m,st[po].n,cs,2));
					st[po].saved=cs+1;
				}
			}else{
				while st[st[po].use].saved!=-1 do{
					st[po].use=st[st[po].use].saved;
				}
				if st[st[po].use].r==-1 do{
					let cs=len(st);
					st.append(aco(st[po].m,st[po].n,st[po].use,st[po].uc));
					st[po].saved=cs;
				}else{
					st[po].r=st[st[po].use].r;
				}
			}
		}
		if st[po].m==m and st[po].n==n and st[po].r!=-1 do{
			return st[po].r;
		}
		po++;
	}
	return -1;
}

pony_run{
#if 1
	for n in range(100)do{
		for m in range(4)do{
			print_nn(a(m,n),' ');
		}
		print();
	}
#else
	print(a(scan(int),scan(int)))
#endif
}
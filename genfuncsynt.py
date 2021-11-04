open('funcsynt.hpp','w')
a=open('funcsynt.hpp','a')
a.write('#define def0(fun) auto fun()\n')
a.write('#define structor0(fun) fun()\n')
a.write('#define lambda0() [&]()\n')
for w in range(1,33):
	a.write('#define def'+str(w)+'(fun,'+','.join(['a'+str(e) for e in range(w)])+') template<'+','.join(['typename t'+str(e) for e in range(w)])+'> auto inline fun('+','.join(['t'+str(e)+' a'+str(e) for e in range(w)])+')\n')
	a.write('#define structor'+str(w)+'(fun,'+','.join(['a'+str(e) for e in range(w)])+') template<'+','.join(['typename t'+str(e) for e in range(w)])+'> inline fun('+','.join(['t'+str(e)+' a'+str(e) for e in range(w)])+')\n')
	a.write('#define lambda'+str(w)+'('+','.join(['a'+str(e) for e in range(w)])+',...) [&]('+','.join(['auto a'+str(e) for e in range(w)])+'){return __VA_ARGS__;}\n')

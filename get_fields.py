from json import *
import re
from sys import stderr
def py_get_fields(db,file,name):
	# print(db,file,name,file=stderr)
	db=loads(db)
	try:
		if name not in db:
			a=open(file).read()
			_name=name
			name=name.split('<')[0]
			t=re.search(r'\b'+name+r'\b\s*\{',a).start()
			if t:
				a=a[t+len(name):]
				a=a[a.index('{')+len('{'):]
				ob=1
				s=''
				while ob and a:
					if a[0] in '([{':
						ob+=1
						a=a[1:]
					elif a[0] in ')]}':
						ob-=1
						a=a[1:]
					elif ob>1:
						a=a[1:]
					else:
						s+=a[0]
						a=a[1:]
				a=s
				# a=a.replace(',',';')
				a=a.split(';')
				a=[w for w in a if w]
				a=[w[w.index('\\')+1:] if w.strip().startswith('\\') else w for w in a]
				a=[w.split('=')[0] for w in a]
				a=[w for w in a if w.strip()]
				a=[w[-[(e).isalnum() or e=='_' for e in w[::-1]+' '].index(0):] for w in a]
				a=[w for w in a if w]
				# print(name,a,file=stderr)
				db[_name]=a
			else:
				db[name]=[]
	except Exception:
		pass
	return dumps(db)

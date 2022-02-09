from json import *
def py_get_fields(db,file,name):
	from sys import stderr
	db=loads(db)
	if name not in db:
		a=open(file).read()
		a=a[a.index(name)+len(name):]
		a=a[a.index('{')+len('{'):]
		a=a[:a.index('}')]
		ob=''
		s=''
		while a:
			if a[0] in '([{':
				ob+={'(':')','[':']','{':'}'}[a[0]]
				a=a[1:]
			elif a[0] in ')]}':
				ob=ob[:-1]
				a=a[1:]
			elif ob:
				a=a[1:]
			else:
				s+=a[0]
				a=a[1:]
		a=s
		a=a.replace(',',';')
		a=a.split(';')
		a=[w for w in a if w]
		a=[w.split('=')[0] for w in a]
		a=[w for w in a if w.strip()]
		a=[w.split()[-1] for w in a]
		a=[w for w in a if w]
		db[name]=a
	return [dumps(db),db[name]]

from json import *
def py_get_fields(db,file,name):
	from sys import stderr
	db=loads(db)
	if name not in db:
		a=open(file).read()
		if name in a:
			a=a[a.index(name)+len(name):]
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
			a=a.replace(',',';')
			a=a.split(';')
			a=[w for w in a if w]
			a=[w.split('=')[0] for w in a]
			a=[w for w in a if w.strip()]
			a=[w[-[(e).isalnum() or e=='_' for e in w[::-1]+' '].index(0):] for w in a]
			a=[w for w in a if w]
			db[name]=a
		else:
			db[name]=[]
	return dumps(db)

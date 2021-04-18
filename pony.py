''':'
python3 $0 $@
exit
':'''
open_=open
from os import *
from os.path import *
from subprocess import*
from pathlib import Path
from sys import argv
compile_mode='run'
if argv[1] in ['-exe','-cpp']:
	compile_mode=argv[1][1:]
	argv=argv[:1]+argv[2:]
open=open_
home=str(Path.home())+'/'
path = str(abspath(dirname(argv[0])))
if path[-1]!='/':
	path+='/'
path=open_(home+'.pony/path').read().strip()
if len(argv)==1:
	print('no input files',file=stderr)
	exit()
q=open(argv[1]).read()
if compile_mode!='cpp':
	q='#include "'+path+'pony.hpp"\nusing namespace std;\n'+q
	open(argv[1]+'.cpp','w').write(q)
	if not run(['g++','-std=c++17','-Wfatal-errors',argv[1]+'.cpp','-o',argv[1]+'.exe']).returncode:
		if compile_mode=='run':
			run([argv[1]+'.exe'])
		else:
			print('executable binary saved to '+argv[1]+'.exe')
else:
	pony=open(path+'pony.hpp').read()
	from re import *
	pony=findall(r'#include "(.*)"',pony)
	pony=['/'*80+'\n//'+w+'\n\n'+open(path+w).read() for w in pony]
	pony='\n\n'.join(pony)
	pony+='/'*80+'\n//the code'
	q=pony+'\n\nusing namespace std;\n'+q
	open(argv[1]+'.cpp','w').write(q)
	print('cpp file saved to '+argv[1]+'.cpp')
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
q='#include "'+path+'pony.hpp"\nusing namespace std;\n'+q
open(argv[1]+'.cpp','w').write(q)
if not run(['g++','-std=c++17','-Wfatal-errors',argv[1]+'.cpp','-o',argv[1]+'.exe']).returncode:
	run([argv[1]+'.exe'])

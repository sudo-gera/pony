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
home=str(Path.home())+'/'
path = str(abspath(dirname(argv[0])))
if path[-1]!='/':
	path+='/'
try:
	mkdir(home+'.pony')
except:
	pass
chdir(home+'.pony')
open_('path','w').write(path)
try:
	run(['ln','-s',path+'pony.py',home+'pony.py'],stderr='PIPE')
except:
	pass
print('executable file is ~/pony.py')
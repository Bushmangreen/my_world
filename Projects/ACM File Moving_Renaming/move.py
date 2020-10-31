# moveing into appropriate folder
import openpyxl,os,shutil
def_dir = '/Users/omarkulov/Desktop/test/'
os.chdir(def_dir+'M1/') 

met='MET'
cet='CET'
iet='IET'
eet='EET'

for filename in os.listdir():
	if filename[-3:]==met:
		src = def_dir+'M1/'+filename+'/'
		dest = def_dir+met+'/'
		shutil.move(src, dest) 
	elif filename[-3:]==cet:
		src = def_dir+'M1/'+filename+'/'
		dest = def_dir+cet+'/'
		shutil.move(src, dest) 
	elif filename[-3:]==eet:
		src = def_dir+'M1/'+filename+'/'
		dest = def_dir+eet+'/'
		shutil.move(src, dest) 
	elif filename[-3:]==iet:
		src = def_dir+'M1/'+filename+'/'
		dest = def_dir+iet+'/'
		shutil.move(src, dest) 	


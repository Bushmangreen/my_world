import openpyxl,os,shutil
os.chdir('/Users/omarkulov/Desktop/test/') 

wb = openpyxl.load_workbook('M1.xlsm')
sheet = wb['Students-info']

data={};

for row in range(9,18):
	Major=sheet['A'+str(row)].value
	Name= sheet['B'+str(row)].value
	Surname = sheet['C'+str(row)].value
	temp={Name:Major}
	data.update(temp)

# renaming all files
 
  
os.chdir('/Users/omarkulov/Desktop/test/M1/') 
for k,v in data.items():
	for filename in os.listdir():
		if k in filename:
			
			os.rename(filename,filename[0:-29]+v)


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



	
			











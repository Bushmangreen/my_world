import openpyxl
wb = openpyxl.load_workbook('grade.xlsx')
sheet = wb['ABET']
#print(sheet['D1'].value)
for row in range(2,sheet.max_row+1):
	grades = sheet['D'+str(row)].value
	if grades==85:
		myRow=row

sheet1=wb['Student']
Major = sheet1['A'+str(myRow)].value
ID = sheet1['D'+str(myRow)].value

print(Major,ID)






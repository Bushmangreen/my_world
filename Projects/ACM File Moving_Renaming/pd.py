import openpyxl,os,shutil
import pandas as pd
df=pd.read_excel(r'/Users/omarkulov/Desktop/test/M1.xlsm',sheet_name='Students-info')
data=pd.DataFrame(df)
print(data['Unnamed: 0'][9])




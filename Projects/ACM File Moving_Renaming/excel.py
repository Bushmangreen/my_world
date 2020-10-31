import xlrd

def open_file(path):
    wb = xlrd.open_workbook(path)
    sheet = wb.sheet_by_index(0)


    for row_num in range(sheet.nrows):
        row_value = sheet.row_values(row_num)
        if row_value[0] == 'MET':
            print(row_value)

if __name__ == "__main__":
    path = "Gradebook.xlsx"
    open_file(path)
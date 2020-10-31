import datetime
def func(string):
	new_list = string.split('\n')
	new_list.pop()
	

	#parsing the emails and ages 
	for row in range(1, len(new_list)):
		#parsing the emails
		parse_list = new_list[row].split(',')
		parse_list[4] = parse_list[4][parse_list[4].index('@')+1:]
		#parsing the ages 
		if 	int(parse_list[5]) <= 20:
			parse_list[5] = "1->20"
		elif  int(parse_list[5]) <= 40:
			parse_list[5] = "21->40"
		elif  int(parse_list[5]) <= 65:
			parse_list[5] = "41->65"
		else:
			parse_list[5] = "66->99"

		#parsing For the Order at column, 
		#[morning => 06:00am -> 11:59am]
		#[afternoon => 12:00pm -> 5:59pm]
		#[evening => 6:00pm -> 11:59pm]

		date_time_str = parse_list[-1]	
		date_time_obj = datetime.datetime.strptime(date_time_str, '%Y-%m-%d %H:%M:%S')
		if date_time_obj.hour < 24 and date_time_obj.hour >= 18:
			parse_list[-1] = "evening"
		elif date_time_obj.hour < 18 and date_time_obj.hour >= 12:
			parse_list[-1] = "afternoon"
		else:
			parse_list[-1] = "morning"


		new_list[row] = ','.join(parse_list)

		# lets collect all the columns first

		# then we will make list as value to dict
	
	parsed_rows = []
	columns_list = []
	index = 0
	for row in range(0, len(new_list)):
		parsed_rows.append(new_list[row].split(","))

	for column in range(0, len(parsed_rows[0])):	
		temp_list = []
		for row in range(1, len(new_list)):
			temp_list.append(parsed_rows[row][column])
			index += 1
		columns_list.append(temp_list)
	
	new_dict = {}
	index = 0
	
	column_name = ["Gender","Email","Age","City","Device","Order At"] 
	column_index = [0,4,5,6,7,9]
	for name in column_name: 
		new_dict.setdefault(name, {})

		for lis in columns_list[column_index[index]]: 
		    new_dict[name].setdefault(lis, list()).append(1) 

		for a, b in new_dict[name].items():
			new_dict[name][a] = sum(b) 
		index += 1
	    
	

  
	#new_dict = {"Gender": {},"Email": {},"Age": {},"City": {},"Device": {},"Order At": {}}

	#new_dict = {"Gender":columns_list[0]}
	# parsed_rows[column_name.index()]
	# [0['Male', 'Male', 'Female', 'Female', 'Male'], 
	#   ['Carl', 'Marvin', 'Shanelle', 'Lavonne', 'Derick'], 
	#   ['Wilderman', 'Lind', 'Marquardt', 'Romaguera', 'McLaughlin'], 
	#   ['carl', 'marvin', 'shanelle', 'lavonne', 'derick'], 
	#  4['yahoo.com', 'hotmail.com', 'hotmail.com', 'yahoo.com', 'hotmail.com'],
	#  5['21->40', '66->99', '21->40', '66->99', '41->65'], 
	#  6['Seattle', 'Detroit', 'Las Vegas', 'Seattle', 'Chicago'],
	#  7['Safari iPhone', 'Chrome Android', 'Chrome', 'Chrome', 'Chrome Android'],
	#   ['2', '2', '1', '2', '1'], 
	#  9['afternoon', 'afternoon', 'afternoon', 'morning', 'afternoon']]
# {'Gender': {'Male': 3, 'Female': 2}, 
#  'Email': {'yahoo.com': 2, 'hotmail.com': 3},
#  'Age': {'21->40': 2, '66->99': 2, '41->65': 1},
#  'City': {'Seattle': 2, 'Detroit': 1, 'Las Vegas': 1, 'Chicago': 1}, 
#  'Device': {'Safari iPhone': 1, 'Chrome Android': 2, 'Chrome': 2}, 
#  'Order At': {'afternoon': 4, 'morning': 1}}


#  {"Gender":{"Male":3,"Female":2},'
#  ' Email":{"yahoo.com":2,"hotmail.com":3},
#  "Age":{"21->40":2,"66->99":2,"41->65":1},
#  "City":{"Seattle":2,"Detroit":1,"Las Vegas":1,"Chicago":1},
#  "Device":{"Safari iPhone":1,"Chrome Android":2,"Chrome":2},
#  "Order At":{"afternoon":4,"morning":1}}

	return json.dumps(new_dict)
	







func("Gender,FirstName,LastName,UserName,Email,Age,City,Device,Coffee Quantity,Order At\nMale,Carl,Wilderman,carl,wilderman_carl@yahoo.com,29,Seattle,Safari iPhone,2,2020-03-06 16:37:56\nMale,Marvin,Lind,marvin,marvin_lind@hotmail.com,77,Detroit,Chrome Android,2,2020-03-02 13:55:51\nFemale,Shanelle,Marquardt,shanelle,marquardt.shanelle@hotmail.com,21,Las Vegas,Chrome,1,2020-03-05 17:53:05\nFemale,Lavonne,Romaguera,lavonne,romaguera.lavonne@yahoo.com,81,Seattle,Chrome,2,2020-03-04 10:33:53\nMale,Derick,McLaughlin,derick,mclaughlin.derick@hotmail.com,47,Chicago,Chrome Android,1,2020-03-05 15:19:48\n")
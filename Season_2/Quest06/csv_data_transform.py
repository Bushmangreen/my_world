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

	return new_list







func("Gender,FirstName,LastName,UserName,Email,Age,City,Device,Coffee Quantity,Order At\nMale,Carl,Wilderman,carl,wilderman_carl@yahoo.com,29,Seattle,Safari iPhone,2,2020-03-06 16:37:56\nMale,Marvin,Lind,marvin,marvin_lind@hotmail.com,77,Detroit,Chrome Android,2,2020-03-02 13:55:51\nFemale,Shanelle,Marquardt,shanelle,marquardt.shanelle@hotmail.com,21,Las Vegas,Chrome,1,2020-03-05 17:53:05\nFemale,Lavonne,Romaguera,lavonne,romaguera.lavonne@yahoo.com,81,Seattle,Chrome,2,2020-03-04 10:33:53\nMale,Derick,McLaughlin,derick,mclaughlin.derick@hotmail.com,47,Chicago,Chrome Android,1,2020-03-05 15:19:48\n")
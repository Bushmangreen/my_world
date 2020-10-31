import json
class Solution:
    """
    :type  param_1: {String[]}
    :rtype: string
    """
    def init_dict(self, list_of_keys):
        dictionary = {}        
        for x in list_of_keys:
            dictionary[x] = {}
        return dictionary
            
    def data_transform(self, param_1):
        result = []
        index2 = 1
        while index2 < len(param_1):
            string = param_1[index2]
            index = 0
            current_list = []
            current_string = ""
            while index < len(string):
                if string[index] == ',':
                    current_list.append(current_string)
                    current_string = ""
                else:
                    current_string += string[index]
                if index == len(string) - 1:
                    current_list.append(current_string)
                index += 1
            result.append(current_list)
            index2 += 1
        return result

    def counter_dict(self, input_data, col_index):
        my_list = [i[col_index] for i in input_data]
        freq = {} 
        for item in my_list: 
            if (item in freq): 
                freq[item] += 1
            else: 
                freq[item] = 1
        return freq


    def my_data_process(self, param_1):
        #print(param_1[0])
        data = self.data_transform(param_1)
        output_keys = ["Gender", "E-mail", "Age", "City", "Device", "Order At"]
        dictionary = self.init_dict(output_keys)



        indeces = [0, 4, 5, 6, 7, 9]
        i = 0
        for x in output_keys:
            dictionary[x] = self.counter_dict(data, indeces[i])
            i += 1

        #print([i[0] for i in data])
        json_data = json.dumps(dictionary)
        #print(dictionary)
        print(json_data)
        return json_data


my_object = Solution()
my_object.my_data_process(["Gender,FirstName,LastName,UserName,Email,Age,City,Device,Coffee Quantity,Order At", "Male,Carl,Wilderman,carl,yahoo.com,21->40,Seattle,Safari iPhone,2,afternoon", "Male,Marvin,Lind,marvin,hotmail.com,66->99,Detroit,Chrome Android,2,afternoon", "Female,Shanelle,Marquardt,shanelle,hotmail.com,21->40,Las Vegas,Chrome,1,afternoon", "Female,Lavonne,Romaguera,lavonne,yahoo.com,66->99,Seattle,Chrome,2,morning", "Male,Derick,McLaughlin,derick,hotmail.com,41->65,Chicago,Chrome Android,1,afternoon"])
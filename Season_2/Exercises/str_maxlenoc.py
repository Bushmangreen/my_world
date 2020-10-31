
def shortest_string(my_list, length):
    
    my_min = 100
    my_index = 0
    
    for index in range(length):
        if (len(my_list[index]) <= my_min):
            my_index = index;
            my_min = len(my_list[index])
           # print(my_index)

    return my_index

def check_presence(substring, my_list):
    for word in my_list:
        if substring not in word:
            status = False
            break;
        else:
            status = True

    return status


def str_maxlenoc(my_list, length):

    l = 0
    r = 0
    my_max = 0
    my_string = []
    #find shortest substring
    shortest = shortest_string(my_list, length)

    #print(my_list[shortest])
    for l in range(len(my_list[shortest])):

        for r in range(l, len(my_list[shortest])):
            substring = my_list[shortest][l:r+1]
            
            status = check_presence(substring, my_list)  
            #print(substring,status)
            if status:
                my_string.append(substring)


    return max(my_string, key=len)




print(str_maxlenoc( ["ab", "bac", "abacabccabcb"] ,3))



class Solution:
  """
  :type  param_1: {String[]}
  :type  param_2: {Integer}
  :rtype: string
  """

  def shortest_string(self, my_list, length):

    my_min = 100
    my_index = 0

    for index in range(length):
      if (len(my_list[index]) <= my_min):
        my_index = index;
        my_min = len(my_list[index])
        # print(my_index)

    return my_index

  def check_presence(self, substring, my_list):
    for word in my_list:
      if substring not in word:
        status = False
        break;
      else:
        status = True

    return status


  def str_maxlenoc(self, my_list, length):

    l = 0
    r = 0
    my_max = 0
    my_string = []
    #find shortest substring
    shortest = self.shortest_string(my_list, length)

    #print(my_list[shortest])
    for l in range(len(my_list[shortest])):

      for r in range(l, len(my_list[shortest])):
        substring = my_list[shortest][l:r+1]

        status = self.check_presence(substring, my_list)  
        #print(substring,status)
        if status:
          my_string.append(substring)
    if (len(my_string) == 0):
      return 
    else:
      return max(my_string, key=len)



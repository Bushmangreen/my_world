def longest_increasing_subsequence(array):
    l = 0
    r = 0
    index = 0
    my_max = 0
    #find max
    min_value = min(array)
    min_index = array[array.index(min_value)]
    my_list = []

    for runner in range(min_index, len(array)):
        my_list = []
        my_list.append(min_value)
        for index in range(runner, len(array)):
            if my_list[-1] < array[index] :
                my_list.append(array[index])
                my_max = max(my_max, len(my_list))
            if (my_list[-1] == array[-1] and  len(my_list) == 1):
                return 0
            index += 1
    if (len(my_list) == 1):
        return 0
    else: 
        return my_max

print(longest_increasing_subsequence([10,9,2,5,3,7,101,18]))
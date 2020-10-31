
def my_median(sub_list):
    
    sub_list.sort()
    length = len(sub_list)
    print(sub_list)
    if (length % 2 == 0):
        middle = int(length/2)
        median = (sub_list[middle] + sub_list[middle-1])/2
    else:
        middle = int(length/2)
        median = sub_list[middle]
    return median

def sliding_window_median(array, window):
    my_list = []
    for index in range(len(array) - window + 1):
        sub_list = array[index : (index + window)]
        my_list.append(my_median(sub_list))

    return my_list


print(sliding_window_median([1,3,-1,-3,5,3,6,7],3))
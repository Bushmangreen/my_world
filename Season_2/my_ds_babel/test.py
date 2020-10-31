class Solution:
    """
    :type  param_1: {String}
    :rtype: integer
    """
    def length_of_last_word(self, string):
        print(len(string))
        new_string = string.split(' ')
        my_list = [a for a in new_string if a.isalpha()]
        
        return len(my_list[-1])

test = Solution()

print(test.length_of_last_word("    "))
# [24, 13, 1, 100, 0, 94, 3, 0, 3]
#[83, 20, 17, 43, 52, 78, 68, 45]
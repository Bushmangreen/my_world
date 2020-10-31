def k_th_smallest_prime_fraction(array, k):
	my_list = []
	permutation = (len(array) * (len(array) - 1)) / 2
	for i in range(len(array)-1):
		for j in range(i+1,len(array)):
			my_list.append(array[i]/array[j])
	sorted(my_list)
	for i in range(len(array)-1):
		for j in range(i+1,len(array)):
			if (my_list[k-1] == array[i]/array[j]):
				return [array[i], array[j]]
	


	


print(sorted(k_th_smallest_prime_fraction([1, 2, 3, 5],3)))

#[1, 2, 3, 5]
 # 1/2
 # 1/3
 # 1/5
 # 2/3
 # 2/5
 # 3/5
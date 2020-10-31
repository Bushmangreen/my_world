def long_pressed_name(org_name, typed_name):

	l = 0
	r = 0
	l_counter = 0
	r_counter = 0

	while(r < len(typed_name)):
		if org_name[l] == typed_name[r]:
			r += 1
			r_counter += 1
		else: 
			while(org_name[l] == typed_name[r - 1]):
				l += 1
				l_counter += 1
			if (l_counter > r_counter):
				return False
			else:
				r_counter = 0
				l_counter = 0


	return True


print(long_pressed_name("xnhtq","xhhttqq"))

# sssaeed
#       l
# sssssaaedd
#         r


# alex

# aaleex

# saeed

# ssaaedd

# leelee

# lleeelee
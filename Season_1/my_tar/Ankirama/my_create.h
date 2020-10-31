#ifndef MY_CREATE_H_
# define MY_CREATE_H_

# include "my_file.h"

t_my_file       *my_create_header(char *str);
void		my_createfile(int fg, t_my_file *my_file, char *opt);
void		my_createdir(t_my_file *my_file, char *opt);

#endif /* !MY_CREATE_H_ */
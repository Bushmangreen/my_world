#ifndef MY_APPEND_H_
# define MY_APPEND_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void	my_append_data(char *str, char *data);
void	my_append_chksum(char *str, t_my_file *file, int tot);
void	my_append_link(char *my_link, char *str, struct stat *buf);
void	my_append_uid(char *str, struct stat *buf, char type);
char	my_type_file(struct stat *buf);

#endif /* !MY_APPEND_H_ */
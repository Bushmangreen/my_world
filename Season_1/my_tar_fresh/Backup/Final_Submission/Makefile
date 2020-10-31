CC = gcc
CC_OPT = -g3 -fsanitize=address
OUTPUT = my_tar

all: ${OUTPUT}

${OUTPUT}: main.o get_opt.o print_opt.o create_archive.o list_archive.o extract_archive.o extract_helpers.o
	${CC} ${CC_OPT} main.o get_opt.o print_opt.o create_archive.o list_archive.o extract_archive.o extract_helpers.o -o ${OUTPUT}

main.o: main.c
	${CC} ${CC_OPT} -c main.c 

get_opt.o: get_opt.c
	${CC} ${CC_OPT} -c get_opt.c

print_opt.o: print_opt.c
	${CC} ${CC_OPT} -c print_opt.c

list_archive.o: list_archive.c
	${CC} ${CC_OPT} -c list_archive.c

create_archive.o: create_archive.c
	${CC} ${CC_OPT} -c create_archive.c

extract_archive.o: extract_archive.c
	${CC} ${CC_OPT} -c extract_archive.c
extract_helpers.o: extract_helpers.c
	${CC} ${CC_OPT} -c extract_helpers.c

clean:
	rm *.o ${OUTPUT}

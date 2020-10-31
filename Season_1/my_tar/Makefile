
CC = gcc
CC_OPT = -g3 -fsanitize=address
OUTPUT = my_tar

all: ${OUTPUT}

${OUTPUT}: main.o get_opt.o print_opt.o
	${CC} ${CC_OPT} main.o get_opt.o print_opt.o -o ${OUTPUT}

main.o: main.c
	${CC} ${CC_OPT} -c main.c 

get_opt.o: get_opt.c
	${CC} ${CC_OPT} -c get_opt.c

print_opt.o: print_opt.c
	${CC} ${CC_OPT} -c print_opt.c

clean:
	rm *.o ${OUTPUT}


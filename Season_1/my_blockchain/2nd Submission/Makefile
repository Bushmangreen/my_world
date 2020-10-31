#-*- MakeFile -*-

all: my_blockchain
	
my_blockchain:
	gcc -g -fsanitize=address *.c -o my_blockchain
run:
	clear && ./my_blockchain -l ; rm my_blockchain
w:
	gcc -g -fsanitize=address -Wall -Wextra -Werror *.c headers.h -o my_blockchain
d:
	lldb *.c headers.h -o my_blockchain


clean:
	rm *.o *.h.gch core.* a.out my_blockchain

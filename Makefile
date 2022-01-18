all :	menace.exe

menace.exe	: opened_matchbox_stack.o ball_arraylist.o  game.o matchboxes.o main.o opened_matchbox_stack.h ball_arraylist.h  game.h matchboxes.h
	gcc -g -Wall -Wextra opened_matchbox_stack.o ball_arraylist.o game.o matchboxes.o main.o -o menace.exe

ball_arraylist.o:	ball_arraylist.c ball_arraylist.h
	gcc -g -Wall -Wextra -c ball_arraylist.c

opened_matchbox_stack.o	:	opened_matchbox_stack.c opened_matchbox_stack.h
	gcc -g -Wall -Wextra -c opened_matchbox_stack.c

game.o	:	game.c game.h
	gcc -g -Wall -Wextra -c game.c

matchboxes.o	:	matchboxes.c matchboxes.h
	gcc -g -Wall -Wextra -c matchboxes.c

main.o	:	 main.c
	gcc -g -Wall -Wextra -c main.c


clean:
	rm *.o all


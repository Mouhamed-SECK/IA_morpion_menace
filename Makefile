all :	menace.exe

menace.exe	:	game.o matchboxes.o main.o game.h matchboxes.h
	gcc -g -Wall -Wextra game.o matchboxes.o main.o -o menace.exe

game.o	:	game.c game.h
	gcc -g -Wall -Wextra -c game.c

matchboxes.o	:	matchboxes.c matchboxes.h
	gcc -g -Wall -Wextra -c matchboxes.c

main.o	:	 main.c
	gcc -g -Wall -Wextra -c main.c
all:
	gcc -I src/libs/SDL2/include -L src/libs/SDL2/lib ooc.c -o ooc.exe -lmingw32 -lSDL2main -lSDL2
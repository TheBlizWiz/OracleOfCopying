all:
	gcc -I src/libs/SDL2/include -I src/defs -I src/math  -I src/objects -I src/render -I src/game -I src/engine -L src/libs/SDL2/lib src/engine/e_app.c ooc.c -o ooc.exe -lmingw32 -lSDL2main -lSDL2
prog: source.o main.o
	gcc source.o main.o -o main -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
main.o: main.c
	gcc -c main.c -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
func.o: source.c
	gcc -c source.c -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

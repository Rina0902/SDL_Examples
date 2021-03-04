prog: source.o main.o
	gcc source.o main.o -o prog -g -lSDL -lSDL_image 
main.o: main.c
	gcc -c main.c -g -lSDL -lSDL_image 
func.o: source.c
	gcc -c source.c -g -lSDL -lSDL_image

CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic `pkg-config --cflags MLV`
LDLIBS = `pkg-config --libs MLV`
OBJ = main.o snake_graphique.o snake.o

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

main.o: main.c snake.h snake_graphique.h

snake_graphique.o: snake_graphique.c snake_graphique.h snake.h

snake.o: snake.c snake.h

%.o: %.c
	$(CC) -c $< $(CFLAGS) $(LDLIBS)

clean:
	rm -f *.o

mrproper: clean
	rm -rf main
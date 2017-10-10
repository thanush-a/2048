CC=gcc
CFLAGS=-Wall
LDFLAGS=-lm
EXEC=2048
TEXEC=2048test
SRC= $(wildcard src/*.c lib/*.c)
TEST := $(SRC) $(wildcard test/*.c)
TEST := $(filter-out src/main.c, $(TEST))
OBJ= $(SRC:.c=.o)

run: mrproper all
	@./$(EXEC)

test: mrproper $(TEXEC)
	@./$(TEXEC) | less -R

all: $(EXEC)

$(TEXEC): $(TEST)
	@$(CC) -o $@ $^ $(LDFLAGS)

2048: $(SRC)
	@$(CC) -o $@ $^ $(LDFLAGS)
	
main.o: jeu.h

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
	@rm -rf $(TEXEC)

DEBUG=no
CC=gcc

ifeq ($(DEBUG),yes)
	CFLAGS=-W -Werror -Wall -ansi -pedantic -g
	LDFLAGS=
else
	CFLAGS=-W -Werror -Wall -ansi -pedantic
	LDFLAGS=
endif

EXEC=tp5
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: $(EXEC)
ifeq ($(DEBUG),yes)
	@echo "Génération finie [DEBUG]"
else
	@echo "Génération finie [RELEASE]"
endif

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm *.o

mrproper: clean
	rm $(EXEC)

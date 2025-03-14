CC = gcc-11
CFLAGS = -Wall -Wextra -g -w

SRC_FILES = driver.c lexer.c parser.c
OBJ_FILES = $(SRC_FILES:.c=.o)
EXEC = stage1exe

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(EXEC)
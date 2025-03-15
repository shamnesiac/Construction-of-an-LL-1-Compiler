# GROUP 22 :
#        ID : 2021B3A70995P | Name : Dhruv Ravi Krishnan
#        ID : 2021B3A70981P | Name : Anirudh Anand
#        ID : 2021B3A71738P | Name : Akshit Phophaliya
#        ID : 2022A7PS1182P | Name : Arnav Dham
#        ID : 2022A7TS0154P | Name : Shaurya Jain
#        ID : 2022A7PS0187P | Name : Darsh Rathi

CC = gcc
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
# the compiler
CC = gcc

# compiler flags
# -g	add debugging info to the executable
# -Wall	turn on (most) compiler warnings
CFLAGS = -g -Wall

TARGET = main
OUTFILE = main.o

DATA_STRUCTS = ../data-struct/src
SRC = src

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGE) $(DATA_STRUCTS)/*.c $(SRC)/*.c $(TARGET).c -o $(OUTFILE)

run:
	./$(OUTFILE)

clean:
	$(RM) $(OUTFILE)

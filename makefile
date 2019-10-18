# the compiler
CC = gcc

# compiler flags
# -g	add debugging info to the executable
# -Wall	turn on (most) compiler warnings
CFLAGS = -g -Wall

TARGET = *
OUTFILE = a2.out

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $(TARGET).c -o $(OUTFILE)

run:
	./$(OUTFILE)

clean:
	$(RM) $(OUTFILE)
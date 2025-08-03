CC = gcc
CFLAGS = -Wall -g -Iinclude
TARGET = main
SRC = main.c
LIBS = -lcurl -lsqlite3

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f *.o $(TARGET)

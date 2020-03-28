TARGET = creatures
CC = gcc
CFLAGS = -O3 -std=gnu99 -DNDEBUG
LDFLAGS = -lm -ldl -lX11 -lGL -lpthread
SRC = $(wildcard src/*.c)
SRC += $(wildcard lib/Chipmunk2D/src/*.c)
INCLUDE = -Ilib -Ilib/Chipmunk2D/include

all:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(INCLUDE)

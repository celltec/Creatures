TARGET = creatures.js
ROOT = ..
CC = emcc
DEFINES = -DNDEBUG -DSOKOL_GLES2
EMFLAGS = WASM=1
CFLAGS = -O3 -std=gnu99
LDFLAGS = -lm -ldl -lX11 -lGL -lpthread
SRC = $(wildcard $(ROOT)/src/*.c)
SRC += $(wildcard $(ROOT)/lib/Chipmunk2D/src/*.c)
INCLUDE = -I$(ROOT)/lib -I$(ROOT)/lib/Chipmunk2D/include

all:
	$(CC) $(SRC) -o $(TARGET) -s $(EMFLAGS) $(CFLAGS) $(LDFLAGS) $(INCLUDE) $(DEFINES)

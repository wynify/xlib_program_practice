TARGET = window

SRC = main.c events.c shapes.c save_shapes.c select_color.c

CC = gcc

CFLAGS = -Wall -g `pkg-config --cflags x11`

LDFLAGS = `pkg-config --libs x11`

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean

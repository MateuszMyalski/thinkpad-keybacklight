# Variables
CC = gcc
CFLAGS = -Wall -Werror -g -Iinclude
TARGET = thinkpad-keybacklight
SRC = src/main.c src/events.c src/thinkpad_leds.c src/schedule.c

# Default rule
all: $(TARGET)

# Linking step 

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC)

# Clean up build files
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean

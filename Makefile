# Variables
CC = gcc
CFLAGS = -Wall -Werror -g -Iinclude
TARGET = thinkpad-keybacklight
SRC = src/main.c src/events.c src/thinkpad_leds.c src/schedule.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC)

clean:
	rm -f $(TARGET)

install: $(TARGET)
	cp thinkpad-keybacklight.service /etc/systemd/system/
	cp $(TARGET) /usr/bin
	systemctl enable thinkpad-keybacklight.service
	systemctl start thinkpad-keybacklight.service
	
uninstall:
	systemctl stop thinkpad-keybacklight.service
	systemctl disable thinkpad-keybacklight.service
	rm /usr/bin/$(TARGET)
	rm /etc/systemd/system/thinkpad-keybacklight.service

# Phony targets
.PHONY: all clean install uninstall

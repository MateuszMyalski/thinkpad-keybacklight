# Variables
CC = gcc
CFLAGS = -Wall -Werror -Iinclude -std=gnu99
TARGET = thinkpad-keybacklight
SRCS = src/main.c src/events.c src/thinkpad_leds.c src/schedule.c src/thinkpad_bat.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

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

clang-tidy:
	@for file in $(SRCS); do \
		clang-tidy $$file -- $(CFLAGS); \
	done

clang-format:
	@for file in $(SRCS); do \
		clang-format -i $$file --style=file; \
	done

	@for file in include/*; do \
		clang-format -i $$file --style=file; \
	done

# Phony targets
.PHONY: all clean install uninstall

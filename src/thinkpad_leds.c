/*
 * Thinkpad Keyboard Backlight Controller
 * Copyright (C) 2024 Mateusz Myalski
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "thinkpad_leds.h"

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RW_BUFFER_SIZE 10

#define TPACPI_KBD_BACKLIGHT_PATH "/sys/class/leds/tpacpi::kbd_backlight"

typedef struct {
    int fd;
    int max_brightness;
    int current_brightness;
} thinkpad_leds_t;

thinkpad_leds_t keyboard_leds;

static thinkpad_leds_status_t _keyboard_get_max_brightness(int *max_brightness) {
    assert(max_brightness != NULL);

    int fd = open(TPACPI_KBD_BACKLIGHT_PATH "/max_brightness", O_RDONLY);
    if (fd <= 0) {
        return THINKPAD_LEDS_FILE_OPEN_ERROR;
    }

    char read_buffer[RW_BUFFER_SIZE];

    ssize_t n_read = read(fd, read_buffer, sizeof(read_buffer));
    if (n_read <= 0) {
        close(fd);
        return THINKPAD_LEDS_READ_ERROR;
    }

    close(fd);

    (*max_brightness) = atoi(read_buffer);

    return THINKPAD_LEDS_OK;
}

thinkpad_leds_status_t thinkpad_leds_keyboard_init(void) {
    keyboard_leds.fd = open(TPACPI_KBD_BACKLIGHT_PATH "/brightness", O_RDWR);
    if (keyboard_leds.fd <= 0) {
        return THINKPAD_LEDS_FILE_OPEN_ERROR;
    }

    thinkpad_leds_status_t tp_leds_stat = _keyboard_get_max_brightness(&keyboard_leds.max_brightness);
    if (THINKPAD_LEDS_OK != tp_leds_stat) {
        close(keyboard_leds.fd);
        return tp_leds_stat;
    }

    return THINKPAD_LEDS_OK;
}

thinkpad_leds_status_t thinkpad_leds_keyboard_set_brightness(unsigned level) {
    if (level > keyboard_leds.max_brightness) {
        return THINKPAD_LEDS_ARGUMENT_ERROR;
    }

    char write_buffer[RW_BUFFER_SIZE];
    int n_placed = snprintf(write_buffer, sizeof(write_buffer), "%d", level);
    if (n_placed <= 0) {
        return THINKPAD_LEDS_WRITE_ERROR;
    }
    int n_write = write(keyboard_leds.fd, write_buffer, n_placed);
    if (n_write != n_placed) {
        return THINKPAD_LEDS_WRITE_ERROR;
    }

    return THINKPAD_LEDS_OK;
}

thinkpad_leds_status_t thinkpad_leds_keyboard_deinit(void) {
    assert(keyboard_leds.fd >= 0);

    assert(close(keyboard_leds.fd));

    return THINKPAD_LEDS_OK;
}
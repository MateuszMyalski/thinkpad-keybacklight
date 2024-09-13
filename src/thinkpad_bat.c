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
#include "thinkpad_bat.h"

#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static unsigned bat_energy_full = 0;
static unsigned battery_threshold = 0;

#define SYS_CLASS_POWER_SUPPLY_BAT_PATH "/sys/class/power_supply/BAT0"
#define RW_BUFFER_SIZE 16

static thinkpad_bat_status_t _read_value_from_file(const char *file_path, unsigned *value) {
    assert(value != NULL);

    int fd = open(file_path, O_RDONLY);
    if (fd <= 0) {
        return THINKPAD_BAT_READ_ERROR;
    }

    char read_buffer[RW_BUFFER_SIZE];

    ssize_t n_read = read(fd, read_buffer, sizeof(read_buffer));
    if (n_read <= 0) {
        close(fd);
        return THINKPAD_BAT_READ_ERROR;
    }

    close(fd);

    (*value) = atoi(read_buffer);

    return THINKPAD_BAT_OK;
}

void thinkpad_bat_set_threshold(unsigned level_threshold) {
    assert(level_threshold <= 100);
    battery_threshold = level_threshold;
}

thinkpad_bat_status_t thinkpad_bat_is_threshold_reached(bool *is_threshold_reached) {
    assert(is_threshold_reached != NULL);

    if (0 == battery_threshold) {
        (*is_threshold_reached) = false;
        return THINKPAD_BAT_OK;
    }

    thinkpad_bat_status_t thinkpad_bat_status;

    if (0 == bat_energy_full) {
        thinkpad_bat_status = _read_value_from_file(SYS_CLASS_POWER_SUPPLY_BAT_PATH "/energy_full", &bat_energy_full);
        if (THINKPAD_BAT_OK != thinkpad_bat_status) {
            return thinkpad_bat_status;
        }

        assert(bat_energy_full > 0);
    }

    unsigned bat_energy_now;
    thinkpad_bat_status = _read_value_from_file(SYS_CLASS_POWER_SUPPLY_BAT_PATH "/energy_now", &bat_energy_now);
    if (THINKPAD_BAT_OK != thinkpad_bat_status) {
        return thinkpad_bat_status;
    }

    unsigned current_level = 100 * ((float)bat_energy_now / (float)bat_energy_full);

    (*is_threshold_reached) = current_level <= battery_threshold;

    return THINKPAD_BAT_OK;
}

thinkpad_bat_status_t thinkpad_bat_is_charging(bool *is_charging) {
    assert(is_charging != NULL);

    int fd = open(SYS_CLASS_POWER_SUPPLY_BAT_PATH "/status", O_RDONLY);
    if (fd <= 0) {
        return THINKPAD_BAT_READ_ERROR;
    }

    char read_buffer[RW_BUFFER_SIZE];

    ssize_t n_read = read(fd, read_buffer, sizeof(read_buffer));
    if (n_read <= 0) {
        close(fd);
        return THINKPAD_BAT_READ_ERROR;
    }

    read_buffer[n_read - 1] = '\0';

    close(fd);

    (*is_charging) = strncmp(read_buffer, "Charging", sizeof(read_buffer)) == 0;

    return THINKPAD_BAT_OK;
}

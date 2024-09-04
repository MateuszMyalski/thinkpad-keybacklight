/*
 * Thinkpad Keyboard Backlight Controller
 * Copyright (C) 2024  Mateusz Myalski
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

#include "events.h"

#include <assert.h>
#include <fcntl.h>
#include <linux/input.h>
#include <poll.h>
#include <unistd.h>

int events_fd[EVENT_TYPE_COUNT];

events_status_t events_init_keyboard(const char *file_path) {
    assert(file_path != NULL);

    events_fd[EVENT_TYPE_KEYBOARD] = open(file_path, O_RDONLY);

    if (events_fd[EVENT_TYPE_KEYBOARD] <= 0) {
        return EVENTS_STATUS_FILE_OPEN_ERROR;
    }

    return EVENTS_STATUS_OK;
}

events_status_t events_init_mouse(const char *file_path) {
    assert(file_path != NULL);

    events_fd[EVENT_TYPE_MOUSE] = open(file_path, O_RDONLY);

    if (events_fd[EVENT_TYPE_MOUSE] <= 0) {
        return EVENTS_STATUS_FILE_OPEN_ERROR;
    }

    return EVENTS_STATUS_OK;
}

void events_deinit_keyboard(void) {
    assert(events_fd[EVENT_TYPE_KEYBOARD] != -1);

    assert(close(events_fd[EVENT_TYPE_KEYBOARD]));

    events_fd[EVENT_TYPE_KEYBOARD] = -1;
}

void events_deinit_mouse(void) {
    assert(events_fd[EVENT_TYPE_MOUSE] != -1);

    assert(close(events_fd[EVENT_TYPE_MOUSE]));

    events_fd[EVENT_TYPE_MOUSE] = -1;
}

events_status_t events_pool_for_event(int timeout, event_type_t *event_type) {
    assert(event_type != NULL);

    struct pollfd pfds[EVENT_TYPE_COUNT] = {};
    event_type_t events_lut[EVENT_TYPE_COUNT] = {};
    nfds_t nfds = 0;

    for (size_t index = 0; index < EVENT_TYPE_COUNT; index++) {
        if (events_fd[index] > 0) {
            pfds[nfds].fd = events_fd[index];
            pfds[nfds].events = POLLIN;
            events_lut[nfds] = index;

            nfds += 1;
        } else {
            pfds[nfds].fd = -1;
            pfds[nfds].events = -1;
        }
    }

    assert(nfds > 0);

    int ready = poll(pfds, nfds, timeout);
    assert(ready != -1);

    if (ready == 0) {
        *event_type = EVENT_TYPE_TIMEOUT;
        return EVENTS_STATUS_OK;
    }

    for (nfds_t j = 0; j < nfds; j++) {
        if (pfds[j].revents != 0) {
            if (pfds[j].revents & POLLIN) {
                *event_type = events_lut[j];
            }

            // Consume the event
            struct input_event dummy_buffer;
            ssize_t n_reads = read(pfds[j].fd, &dummy_buffer, sizeof(struct input_event));

            if (n_reads != sizeof(sizeof(struct input_event))) {
                return EVENTS_STATUS_READ_ERROR;
            }
        }
    }

    return EVENTS_STATUS_OK;
}
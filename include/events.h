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

#ifndef EVENTS_H
#define EVENTS_H

typedef enum {
    EVENTS_STATUS_OK = 0,
    EVENTS_STATUS_FILE_OPEN_ERROR = -1,
    EVENTS_STATUS_CLOSE_ERROR = -2,
    EVENTS_STATUS_READ_ERROR = -3,

} events_status_t;

typedef enum {
    EVENT_TYPE_TIMEOUT = -1,
    EVENT_TYPE_MOUSE = 0,
    EVENT_TYPE_KEYBOARD = 1,

    EVENT_TYPE_COUNT
} event_type_t;

/**
 * @brief Initialize the keyboard event system.
 *
 * This function initializes the keyboard event system by specifying the path to the device file.
 * It sets up the necessary resources to begin capturing keyboard events.
 *
 * @param[in] file_path The file path to the keyboard device (e.g., "/dev/input/event0").
 * @return A status code indicating the result of the initialization.
 * @retval EVENTS_STATUS_OK Initialization was successful.
 * @retval EVENTS_STATUS_ERROR Failed to initialize the keyboard event system.
 */
events_status_t events_init_keyboard(const char *file_path);

/**
 * @brief Initialize the mouse event system.
 *
 * This function initializes the mouse event system by specifying the path to the device file.
 * It sets up the necessary resources to begin capturing mouse events.
 *
 * @param[in] file_path The file path to the mouse device (e.g., "/dev/input/event1").
 * @return A status code indicating the result of the initialization.
 * @retval EVENTS_STATUS_OK Initialization was successful.
 */
events_status_t events_init_mouse(const char *file_path);

/**
 * @brief Poll for an input event.
 *
 * This function waits for an input event (keyboard or mouse) to occur within the specified timeout period.
 * If an event occurs, the type of event is stored in the provided event_type parameter.
 *
 * @param[in] timeout The maximum time in milliseconds to wait for an event.
 *                    A timeout of 0 means no waiting, and a negative timeout means an infinite wait.
 * @param[out] event_type Pointer to the variable where the event type will be stored if an event occurs.
 * @return A status code indicating the result of the polling operation.
 * @retval EVENTS_STATUS_OK An event was successfully captured.
 * @retval EVENTS_STATUS_TIMEOUT No event occurred within the specified timeout.
 */
events_status_t events_pool_for_event(int timeout, event_type_t *event_type);

/**
 * @brief Deinitialize the keyboard event system.
 *
 * This function releases any resources allocated for the keyboard event system and stops capturing keyboard events.
 */
void events_deinit_keyboard(void);

/**
 * @brief Deinitialize the mouse event system.
 *
 * This function releases any resources allocated for the mouse event system and stops capturing mouse events.
 */
void events_deinit_mouse(void);

#endif
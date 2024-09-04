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

#ifndef CONFIG_H
#define CONFIG_H

/**
 * @brief Default file path for the keyboard input event.
 *
 * This macro defines the default file path used to capture keyboard input events.
 */
#define CONFIG_DEFAULT_KEYBOARD_INPUT_EVENT "/dev/input/event0"

/**
 * @brief Default file path for the mouse input event.
 *
 * This macro defines the default file path used to capture mouse input events.
 */
#define CONFIG_DEFAULT_MOUSE_INPUT_EVENT "/dev/input/mouse0"

/**
 * @brief Default timeout in milliseconds.
 *
 * This macro defines the default timeout value in milliseconds for event polling or similar operations.
 * The default is set to 2000 milliseconds (2 seconds).
 */
#define CONFIG_DEFAULT_TIMEOUT_MS (2 * 1000)

/**
 * @brief Default schedule on time (hour).
 *
 * This macro defines the default hour (24-hour format) when the schedule should activate.
 * The default is set to 15:00 (3:00 PM).
 */
#define CONFIG_DEFAULT_SCHEDULE_ON_HOUR 15

/**
 * @brief Default schedule on time (minute).
 *
 * This macro defines the default minutes when the schedule should activate.
 * The default is set to 00 minutes.
 */
#define CONFIG_DEFAULT_SCHEDULE_ON_MINUTE 00

/**
 * @brief Default schedule off time (hour).
 *
 * This macro defines the default hour (24-hour format) when the schedule should deactivate.
 * The default is set to 07:00 (7:00 AM).
 */
#define CONFIG_DEFAULT_SCHEDULE_OFF_HOUR 7

/**
 * @brief Default schedule off time (minute).
 *
 * This macro defines the default minutes when the schedule should deactivate.
 * The default is set to 00 minutes.
 */
#define CONFIG_DEFAULT_SCHEDULE_OFF_MINUTE 00

/**
 * @brief Enable mouse event handling.
 *
 * This macro enables the handling of mouse events within the system.
 * It should be defined if mouse event handling is required.
 */
#define CONFIG_ENABLE_MOUSE_EVENT

/**
 * @brief Enable keyboard event handling.
 *
 * This macro enables the handling of keyboard events within the system.
 * It should be defined if keyboard event handling is required.
 */
#define CONFIG_ENABLE_KEYBOARD_EVENT

/**
 * @brief Enable automatic lowering of brightness on mouse events.
 *
 * This macro enables the feature that automatically lowers the screen brightness when a mouse event is detected.
 */
#define CONFIG_ENABLE_MOUSE_LOWER_BRIGHTNESS

/**
 * @brief Enable scheduling feature.
 *
 * This macro enables the scheduling feature within the system, allowing operations to be performed based on predefined
 * times.
 */
#define CONFIG_ENABLE_SCHEDULE

/**
 * @brief Disable verbose logging.
 *
 * This macro disables verbose logging in the system. When defined, detailed log output is suppressed.
 */
#define CONFIG_DISABLE_VERBOSE

#endif
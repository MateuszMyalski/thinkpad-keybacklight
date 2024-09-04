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
#ifndef THINKPAD_LEDS_H
#define THINKPAD_LEDS_H

typedef enum {
    THINKPAD_LEDS_OK = 0,
    THINKPAD_LEDS_FILE_OPEN_ERROR = -1,
    THINKPAD_LEDS_CLOSE_ERROR = -2,
    THINKPAD_LEDS_ARGUMENT_ERROR = -3,
    THINKPAD_LEDS_READ_ERROR = -4,
    THINKPAD_LEDS_WRITE_ERROR = -5
} thinkpad_leds_status_t;

/**
 * @brief Initialize the ThinkPad keyboard LED system.
 *
 * This function initializes the keyboard LED system on a ThinkPad device. It sets up the necessary resources
 * to control the keyboard backlight brightness.
 *
 * @return A status code indicating the result of the initialization.
 * @retval THINKPAD_LEDS_STATUS_OK Initialization was successful.
 * @retval THINKPAD_LEDS_STATUS_ERROR Failed to initialize the keyboard LED system.
 */
thinkpad_leds_status_t thinkpad_leds_keyboard_init(void);

/**
 * @brief Set the brightness level of the ThinkPad keyboard LED.
 *
 * This function sets the brightness level of the keyboard backlight on a ThinkPad device. The brightness level
 * is specified as an unsigned integer, where the value represents the intensity of the backlight.
 *
 * @param[in] level The brightness level to set. The valid range depends on the hardware, typically between 0 (off) and
 * a maximum level (e.g., 2 for full brightness).
 * @return A status code indicating the result of the operation.
 * @retval THINKPAD_LEDS_STATUS_OK The brightness level was successfully set.
 */
thinkpad_leds_status_t thinkpad_leds_keyboard_set_brightness(unsigned level);

/**
 * @brief Deinitialize the ThinkPad keyboard LED system.
 *
 * This function releases any resources allocated for controlling the keyboard backlight on a ThinkPad device.
 * It should be called when LED control is no longer needed.
 *
 * @return A status code indicating the result of the deinitialization.
 * @retval THINKPAD_LEDS_STATUS_OK Deinitialization was successful.
 */
thinkpad_leds_status_t thinkpad_leds_keyboard_deinit(void);

#endif
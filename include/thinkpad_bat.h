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
#ifndef THINKPAD_BAT_H
#define THINKPAD_BAT_H

#include <stdbool.h>

typedef enum {
    THINKPAD_BAT_OK = 0,
    THINKPAD_BAT_FILE_OPEN_ERROR = -1,
    THINKPAD_BAT_CLOSE_ERROR = -2,
    THINKPAD_BAT_ARGUMENT_ERROR = -3,
    THINKPAD_BAT_READ_ERROR = -4,
    THINKPAD_BAT_WRITE_ERROR = -5
} thinkpad_bat_status_t;

/**
 * @brief Set the battery level threshold.
 *
 * This function sets a threshold level for the battery. The system will use this threshold to determine
 * specific actions or notifications when the battery level crosses the specified threshold.
 *
 * @param[in] level_threshold The battery level threshold to set, typically expressed as a percentage (0-100).
 */
void thinkpad_bat_set_threshold(unsigned level_threshold);

/**
 * @brief Check if the battery level threshold has been reached.
 *
 * This function checks whether the current battery level has reached or fallen below the set threshold.
 *
 * @param[out] is_threshold_reached Pointer to the variable where the status about reaching threshold will be stored
 * @return A status code indicating the status of threshold
 */
thinkpad_bat_status_t thinkpad_bat_is_threshold_reached(bool *is_threshold_reached);

/**
 * @brief Check if the ThinkPad is currently charging.
 *
 * This function determines whether the ThinkPad device is currently connected to a power source and charging the
 * battery.
 *
 * @param[out] is_charging Pointer to the variable where the charging status will be stored
 * @return A status code indicating if the battery is charging
 */
thinkpad_bat_status_t thinkpad_bat_is_charging(bool *is_charging);

#endif
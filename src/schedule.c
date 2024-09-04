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
#include "schedule.h"

#include <assert.h>
#include <stdio.h>
#include <time.h>

#define MINUTES_IN_HOUR 60

time_t scheduled_on_time_minutes = 0;
time_t scheduled_off_time_minutes = 0;

static time_t _time_to_minutes(unsigned hour, unsigned minutes) { return hour * MINUTES_IN_HOUR + minutes; }

void schedule_set_on_time(unsigned hour, unsigned minutes) {
    assert(hour <= 23);
    assert(minutes <= 59);

    scheduled_on_time_minutes = _time_to_minutes(hour, minutes);
}

void schedule_set_off_time(unsigned hour, unsigned minutes) {
    assert(hour <= 23);
    assert(minutes <= 59);

    scheduled_off_time_minutes = _time_to_minutes(hour, minutes);
}

bool schedule_is_in_time_range(void) {
    time_t current_epoch_time = time(NULL);
    struct tm *now = localtime(&current_epoch_time);
    time_t now_in_minutes = _time_to_minutes(now->tm_hour, now->tm_min);

    // Handle the case where the time range crosses midnight
    if (scheduled_off_time_minutes < scheduled_on_time_minutes) {
        // If the target time is greater than or equal to the start time, or less than or equal to the end time
        return (now_in_minutes >= scheduled_on_time_minutes || now_in_minutes <= scheduled_off_time_minutes);
    }

    // Standard case: check if the target time is between start and end
    return (now_in_minutes >= scheduled_on_time_minutes && now_in_minutes <= scheduled_off_time_minutes);
}

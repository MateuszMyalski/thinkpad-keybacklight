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
#include "config.h"
#include "events.h"
#include "schedule.h"
#include "thinkpad_bat.h"
#include "thinkpad_leds.h"

#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#ifdef CONFIG_DISABLE_VERBOSE
#define VERBOSE(...)
#else
#define VERBOSE(...) printf(__VA_ARGS__)
#endif

int main(int argc, char **argv) {

#ifdef CONFIG_ENABLE_SCHEDULE
    schedule_set_on_time(CONFIG_DEFAULT_SCHEDULE_ON_HOUR, CONFIG_DEFAULT_SCHEDULE_ON_MINUTE);
    schedule_set_off_time(CONFIG_DEFAULT_SCHEDULE_OFF_HOUR, CONFIG_DEFAULT_SCHEDULE_OFF_MINUTE);
#endif

#ifdef CONFIG_ENABLE_POWER_SAVING
    thinkpad_bat_set_threshold(CONFIG_DEFAULT_POWER_THRESHOLD);
#endif

    events_status_t events_status;

#ifdef CONFIG_ENABLE_KEYBOARD_EVENT
    events_status = events_init_keyboard(CONFIG_DEFAULT_KEYBOARD_INPUT_EVENT);
    if (events_status != EVENTS_STATUS_OK) {
        assert(0);
    }
#endif

#ifdef CONFIG_ENABLE_MOUSE_EVENT
    events_status = events_init_mouse(CONFIG_DEFAULT_MOUSE_INPUT_EVENT);

    if (events_status != EVENTS_STATUS_OK) {
#ifdef CONFIG_ENABLE_KEYBOARD_EVENT
        events_deinit_keyboard();
#endif
        assert(0);
    }
#endif

    thinkpad_leds_status_t thinkpad_leds_status = thinkpad_leds_keyboard_init();
    if (thinkpad_leds_status != THINKPAD_LEDS_OK) {
        assert(0);
    }

    thinkpad_leds_keyboard_set_brightness(0);

    while (1) {

#ifdef CONFIG_ENABLE_POWER_SAVING
        bool is_bat_threshold_reached;
        bool is_bat_charging;

        thinkpad_bat_set_threshold(CONFIG_DEFAULT_POWER_THRESHOLD);

        thinkpad_bat_status_t thinkpad_bat_status;
        thinkpad_bat_status = thinkpad_bat_is_threshold_reached(&is_bat_threshold_reached);
        if (THINKPAD_BAT_OK != thinkpad_bat_status) {
            assert(0);
        }

        thinkpad_bat_status = thinkpad_bat_is_charging(&is_bat_charging);
        if (THINKPAD_BAT_OK != thinkpad_bat_status) {
            assert(0);
        }

        if (is_bat_threshold_reached && !is_bat_charging) {
            VERBOSE("Battery level too low!\n");
            sleep(1);
            continue;
        }
#endif

#ifdef CONFIG_ENABLE_SCHEDULE
        if (!schedule_is_in_time_range()) {
            VERBOSE("Not in schedule\n");
            sleep(1);
            continue;
        }
#endif
        event_type_t event_type = EVENT_TYPE_TIMEOUT;
        events_pool_for_event(CONFIG_DEFAULT_TIMEOUT_MS, &event_type);

        switch (event_type) {
        case EVENT_TYPE_TIMEOUT:
            VERBOSE("T");
            thinkpad_leds_keyboard_set_brightness(0);
            break;
        case EVENT_TYPE_MOUSE:
            VERBOSE("M");
#ifdef CONFIG_ENABLE_MOUSE_LOWER_BRIGHTNESS
            thinkpad_leds_keyboard_set_brightness(1);
#else
            thinkpad_leds_keyboard_set_brightness(2);
#endif
            break;
        case EVENT_TYPE_KEYBOARD:
            VERBOSE("K");
            thinkpad_leds_keyboard_set_brightness(2);
            break;
        default:
            VERBOSE("?");
            break;
        }

#ifndef CONFIG_DISABLE_VERBOSE
        fflush(stdout);
#endif
    }

    events_deinit_keyboard();
    events_deinit_mouse();

    return 0;
}
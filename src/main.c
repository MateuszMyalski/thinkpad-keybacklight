#include "config.h"
#include "events.h"
#include "thinkpad_leds.h"

#include <assert.h>
#include <stdio.h>

#ifdef CONFIG_DISABLE_VERBOSE
#define VERBOSE(...)
#else
#define VERBOSE(...) printf(__VA_ARGS__)
#endif

int main(int argc, char **argv) {

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
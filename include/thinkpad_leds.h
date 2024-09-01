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


thinkpad_leds_status_t thinkpad_leds_keyboard_init(void);

thinkpad_leds_status_t thinkpad_leds_keyboard_set_brightness(unsigned level);

thinkpad_leds_status_t thinkpad_leds_keyboard_deinit(void);




#endif
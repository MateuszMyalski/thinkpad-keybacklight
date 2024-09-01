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

events_status_t events_init_keyboard(const char *file_path);

events_status_t events_init_mouse(const char *file_path);

events_status_t events_pool_for_event(int timeout, event_type_t *event_type);

void events_deinit_keyboard(void);

void events_deinit_mouse(void);

#endif
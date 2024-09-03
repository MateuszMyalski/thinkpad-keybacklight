#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <stdbool.h>

void schedule_set_on_time(unsigned hour, unsigned minutes);

void schedule_set_off_time(unsigned hour, unsigned minutes);

bool schedule_is_in_time_range(void);

#endif
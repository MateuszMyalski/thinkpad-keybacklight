#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <stdbool.h>

/**
 * @brief Set the on time for the schedule.
 *
 * This function sets the time when the schedule should activate. The specified hour and minutes will be used
 * as the starting time for the schedule.
 *
 * @param[in] hour The hour when the schedule should activate (0-23).
 * @param[in] minutes The minutes when the schedule should activate (0-59).
 */
void schedule_set_on_time(unsigned hour, unsigned minutes);

/**
 * @brief Set the off time for the schedule.
 *
 * This function sets the time when the schedule should deactivate. The specified hour and minutes will be used
 * as the ending time for the schedule.
 *
 * @param[in] hour The hour when the schedule should deactivate (0-23).
 * @param[in] minutes The minutes when the schedule should deactivate (0-59).
 */
void schedule_set_off_time(unsigned hour, unsigned minutes);

/**
 * @brief Check if the current time is within the scheduled time range.
 *
 * This function checks whether the current time falls within the range defined by the on time and off time.
 * It returns `true` if the current time is within the range, otherwise `false`.
 *
 * @return `true` if the current time is within the scheduled time range, `false` otherwise.
 */
bool schedule_is_in_time_range(void);

#endif
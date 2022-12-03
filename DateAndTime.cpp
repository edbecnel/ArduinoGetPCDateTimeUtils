#include "DateAndTime.h"
#include "ArduinoGetPCDateTimeUtils.h"
#include <string.h>

const char compile_date[] = __DATE__;
const char compile_time[] = __TIME__;

DateAndTime::DateAndTime()
{
    month = 0;
    day = 0;
    year = 0;
    hours = 0;
    minutes = 0;
    seconds = 0;
}

bool DateAndTime::getCompileDateAndTime()
{
    int dateSize = sizeof(compile_date) / sizeof(char);
    if (dateSize < 11)
        return false;
    char monthChar[3];
    strncpy(monthChar, compile_date, 3);
    month = Utils::convertMonthToInt(monthChar);
    char dayChar[2];
    strncpy(dayChar, &compile_date[4], 2);
    day = Utils::convertCharToInt(dayChar, 2);
    char yearChar[4];
    strncpy(yearChar, &compile_date[7], 4);
    year = Utils::convertCharToInt(yearChar, 4);

    int timeSize = sizeof(compile_time) / sizeof(char);
    if (timeSize < 9)
        return false;
    char hour[2];
    strncpy(hour, compile_time, 2);
    hours = Utils::convertCharToInt(hour, 2);
    char min[2];
    strncpy(min, &compile_time[3], 2);
    minutes = Utils::convertCharToInt(min, 2);
    char sec[2];
    strncpy(sec, &compile_time[6], 2);
    seconds = Utils::convertCharToInt(sec, 2);
    return true;
}

DateAndTimeBytes::DateAndTimeBytes()
{
    month = 0;
    day = 0;
    year = 0;
    hours = 0;
    minutes = 0;
    seconds = 0;
}

bool DateAndTimeBytes::getCompileDateAndTime()
{
    DateAndTime dateAndTime;
    if (!dateAndTime.getCompileDateAndTime())
        return false;
    convertDateAndTimeToBytes(dateAndTime);
    return true;
}


void DateAndTimeBytes::convertDateAndTimeToBytes(const DateAndTime& dateAndTime)
{
    day = (byte)dateAndTime.day;
    month = (byte)dateAndTime.month;
    year = (byte)(dateAndTime.year - 2000);
    hours = (byte)dateAndTime.hours;
    minutes = (byte)dateAndTime.minutes;
    seconds = (byte)dateAndTime.seconds;
}

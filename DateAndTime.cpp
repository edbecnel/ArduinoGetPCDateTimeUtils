#include "DateAndTime.h"
#include "ArduinoGetPCDateTimeUtils.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

const char compile_date[] = __DATE__;
const char compile_time[] = __TIME__;

using namespace ArduinoGetPCDateTimeUtils;

#pragma region ConvertTimeLocalHelperFunctions
void convertDateAndTimeToTime_t(const DateAndTime& dateAndTime, time_t& timeT)
{
    struct tm tmDateTime;
    tmDateTime.tm_year = dateAndTime.year - 1900;
    tmDateTime.tm_mon = dateAndTime.month - 1;
    tmDateTime.tm_mday = dateAndTime.day;
    tmDateTime.tm_hour = dateAndTime.hours;
    tmDateTime.tm_min = dateAndTime.minutes;
    tmDateTime.tm_sec = dateAndTime.seconds;
    tmDateTime.tm_isdst = -1;
    timeT = mktime(&tmDateTime);
}

void convertTime_tToDateAndTime(const time_t dateAndTimeT, DateAndTime& dateAndTime)
{
    struct tm* newTimeTm = localtime(&dateAndTimeT);
    dateAndTime.hours = newTimeTm->tm_hour;
    dateAndTime.minutes = newTimeTm->tm_min;
    dateAndTime.seconds = newTimeTm->tm_sec;
    dateAndTime.month = newTimeTm->tm_mon + 1;
    dateAndTime.day = newTimeTm->tm_mday;
    dateAndTime.year = 1900 + newTimeTm->tm_year;
}
#pragma endregion ConvertTimeLocalHelperFunctions

#pragma region DateAndTime
DateAndTime::DateAndTime() : month(0), day(0), year(0), hours(0), minutes(0), seconds(0)
{
}

DateAndTime::DateAndTime(int monthVal, int dayVal, int yearVal, int hoursVal, int minutesVal, int secondsVal) :
    month(monthVal), day(dayVal), year(yearVal), hours(hoursVal), minutes(minutesVal), seconds(secondsVal)
{
}

DateAndTime::DateAndTime(const DateAndTime& dateAndTime) :
    month(dateAndTime.month), day(dateAndTime.day), year(dateAndTime.year), hours(dateAndTime.hours), minutes(dateAndTime.minutes), seconds(dateAndTime.seconds)
{
}

long DateAndTime::secondsTo(DateAndTime& otherDateTime)
{
    time_t time1;
    convertDateAndTimeToTime_t(otherDateTime, time1);
    time_t time2;
    convertDateAndTimeToTime_t(*this, time2);
    double dDiffInSeconds = difftime(time1, time2);
    long lDiffInSeconds = floor(dDiffInSeconds);
    return lDiffInSeconds;
}

void DateAndTime::getDaysHoursMinutesSecondsTo(DateAndTime& otherDateTime, long& days, long& hours, long& minutes, long& seconds)
{
    long secondsTo = this->secondsTo(otherDateTime);
    minutes = secondsTo / 60;
    seconds = secondsTo % 60;
    hours = minutes / 60;
    days = hours / 24;
    hours = hours % 24;
    minutes = minutes % 60;
}

bool DateAndTime::getCompileDateAndTime()
{
    char monthChar[4] = "";
    strncpy(monthChar, compile_date, 3);
    month = Utils::convertMonthToInt(monthChar);
    char dayChar[3] = "";
    strncpy(dayChar, &compile_date[4], 2);
    day = Utils::convertCharToInt(dayChar, 2);
    char yearChar[5] = "";
    strncpy(yearChar, &compile_date[7], 4);
    year = Utils::convertCharToInt(yearChar, 4);
    char hour[3] = "";
    strncpy(hour, compile_time, 2);
    hours = Utils::convertCharToInt(hour, 2);
    char min[3] = "";
    strncpy(min, &compile_time[3], 2);
    minutes = Utils::convertCharToInt(min, 2);
    char sec[3] = "";
    strncpy(sec, &compile_time[6], 2);
    seconds = Utils::convertCharToInt(sec, 2);
    return true;
}

void DateAndTime::addSeconds(int secondsToAdd)
{
    time_t timeT = 0;
    convertDateAndTimeToTime_t(*this, timeT);
    time_t newDateAndTime = timeT + secondsToAdd;
    convertTime_tToDateAndTime(newDateAndTime, *this);
}

void DateAndTime::addMinutes(int minutesToAdd)
{
    addSeconds(60 * minutesToAdd);
}

void DateAndTime::addHours(int hoursToAdd)
{
    addMinutes(60 * hoursToAdd);
}

void DateAndTime::addDays(int daysToAdd)
{
    addHours(24 * daysToAdd);
}

void DateAndTime::addMonths(int monthsToAdd)
{
    double yearsDouble = monthsToAdd / 12.0;
    int yearsInt = (int)floor(yearsDouble);
    if (yearsInt > 0)
    {
        addYears(yearsInt);
        double monthsDouble = yearsDouble - (double)yearsInt;
        monthsDouble = monthsDouble * 12.0;
        monthsToAdd = (int)monthsDouble;
    }
    month += monthsToAdd;
    if (month > 12)
    {
        month = month - 12;
    }
}

void DateAndTime::addYears(int yearsToAdd)
{
    year += yearsToAdd;
}

void DateAndTime::addTime(int years, int months, int days, int hours, int minutes, int seconds)
{
    addYears(years);
    addMonths(months);
    addDays(days);
    addHours(hours);
    addMinutes(minutes);
    addSeconds(seconds);
}
#pragma endregion DateAndTime

#pragma region DateAndTimeBytes
DateAndTimeBytes::DateAndTimeBytes() : month(0), day(0), year(0), hours(0), minutes(0), seconds(0)
{
}

DateAndTimeBytes::DateAndTimeBytes(byte monthVal, byte dayVal, byte yearVal, byte hoursVal, byte minutesVal, byte secondsVal) :
    month(monthVal), day(dayVal), year(yearVal), hours(hoursVal), minutes(minutesVal), seconds(secondsVal)
{
}

DateAndTimeBytes::DateAndTimeBytes(const DateAndTime& dateAndTime) :
    month(dateAndTime.month), day(dateAndTime.day), year(dateAndTime.year), hours(dateAndTime.hours), minutes(dateAndTime.minutes), seconds(dateAndTime.seconds)
{
}

long DateAndTimeBytes::secondsTo(DateAndTimeBytes& otherDateTimeBytes)
{
    DateAndTime dateAndTime;
    convertToDateAndTime(dateAndTime);
    DateAndTime otherDateTime;
    otherDateTimeBytes.convertToDateAndTime(otherDateTime);
    return dateAndTime.secondsTo(otherDateTime);
}

void DateAndTimeBytes::getDaysHoursMinutesSecondsTo(DateAndTimeBytes& otherDateTimeBytes, long& days, long& hours, long& minutes, long& seconds)
{
    DateAndTime dateAndTime;
    convertToDateAndTime(dateAndTime);
    DateAndTime otherDateTime;
    otherDateTimeBytes.convertToDateAndTime(otherDateTime);
    dateAndTime.getDaysHoursMinutesSecondsTo(otherDateTime, days, hours, minutes, seconds);
}

bool DateAndTimeBytes::getCompileDateAndTime()
{
    DateAndTime dateAndTime;
    if (!dateAndTime.getCompileDateAndTime())
        return false;
    convertDateAndTimeToBytes(dateAndTime);
    return true;
}

void DateAndTimeBytes::addSeconds(byte secondsToAdd)
{
    DateAndTime dateAndTime;
    convertToDateAndTime(dateAndTime);
    dateAndTime.addSeconds((int)secondsToAdd);
    convertDateAndTimeToBytes(dateAndTime);
}


void DateAndTimeBytes::addMinutes(byte minutesToAdd)
{
    DateAndTime dateAndTime;
    convertToDateAndTime(dateAndTime);
    dateAndTime.addMinutes((int)minutesToAdd);
    convertDateAndTimeToBytes(dateAndTime);
}

void DateAndTimeBytes::addHours(byte hoursToAdd)
{
    DateAndTime dateAndTime;
    convertToDateAndTime(dateAndTime);
    dateAndTime.addHours((int)hoursToAdd);
    convertDateAndTimeToBytes(dateAndTime);
}

void DateAndTimeBytes::addDays(byte daysToAdd)
{
    DateAndTime dateAndTime;
    convertToDateAndTime(dateAndTime);
    dateAndTime.addDays((int)daysToAdd);
    convertDateAndTimeToBytes(dateAndTime);
}

void DateAndTimeBytes::addMonths(byte monthsToAdd)
{
    DateAndTime dateAndTime;
    convertToDateAndTime(dateAndTime);
    dateAndTime.addMonths((int)monthsToAdd);
    convertDateAndTimeToBytes(dateAndTime);
}

void DateAndTimeBytes::addYears(byte yearsToAdd)
{
    DateAndTime dateAndTime;
    convertToDateAndTime(dateAndTime);
    dateAndTime.addYears((int)yearsToAdd);
    convertDateAndTimeToBytes(dateAndTime);
}

void DateAndTimeBytes::addTime(byte years, byte months, byte days, byte hours, byte minutes, byte seconds)
{
    DateAndTime dateAndTime;
    convertToDateAndTime(dateAndTime);
    dateAndTime.addTime((int)years, (int)months, (int)days, (int)hours, (int)minutes, (int)seconds);
    convertDateAndTimeToBytes(dateAndTime);
}

void DateAndTimeBytes::convertToDateAndTime(DateAndTime& dateAndTime)
{
    dateAndTime.day = (int)day;
    dateAndTime.month = (int)month;
    dateAndTime.year = (int)year + 2000;
    dateAndTime.hours = (int)hours;
    dateAndTime.minutes = (int)minutes;
    dateAndTime.seconds = (int)seconds;
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
#pragma endregion DateAndTimeBytes